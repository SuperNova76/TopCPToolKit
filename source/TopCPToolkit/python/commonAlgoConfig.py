# File for configuration of common stuff
# includes event cleaning, GRL, PRW and MC weight
from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnalysisAlgorithmsConfig.ConfigAccumulator import ConfigAccumulator
from AnalysisAlgorithmsConfig.ConfigText import TextConfig
from AnalysisAlgorithmsConfig.ConfigFactory import ConfigFactory
from AnaAlgorithm.DualUseConfig import createAlgorithm, createService
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
from TopCPToolkit import metaConfig
from ROOT import PathResolver


def makeRecoSequence(analysisName, flags, noSystematics=False, noFilter=False):
    algSeq = AnaAlgSequence()

    configSeq = ConfigSequence()
    factory = ConfigFactory()

    configSeq += factory.makeConfig('CommonServices')
    configSeq.setOptionValue('.runSystematics', not noSystematics)
    configSeq.setOptionValue('.systematicsHistogram', 'listOfSystematics')

    import importlib
    try:
        analysisModule = importlib.import_module(analysisName)
    except ModuleNotFoundError:
        raise Exception(f'The package and module for your --analysis could not be found: {analysisName}')
    try:
        analysisModule.makeRecoConfiguration(flags, algSeq, configSeq, factory, noFilter)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeRecoConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    return algSeq


def add_event_cleaning(configSeq, factory, flags, runEventCleaning=True):
    # primary vertex ,event cleaning (jet clean loosebad) and GoodRunsList selection
    is_data = (flags.Input.DataType is DataType.Data)
    if is_data:
        GRLFiles = [metaConfig.get_grl(flags)]
    configSeq += factory.makeConfig ('EventCleaning')
    configSeq.setOptionValue ('.runEventCleaning', runEventCleaning)
    configSeq.setOptionValue ('.userGRLFiles', GRLFiles if is_data else [])


def makeTruthSequence(analysisName, flags, noSystematics=False):
    algSeq = AnaAlgSequence()

    if flags.Input.DataType is DataType.Data:
        return algSeq
    sysService = createService('CP::SystematicsSvc', 'SystematicsSvc', sequence=algSeq)
    # we always want systematics!
    sysService.sigmaRecommended = 1

    # filter-out events without primary vertex
    algSeq += createAlgorithm('CP::VertexSelectionAlg',
                              'TruthPrimaryVertexSelectorAlg')
    algSeq.TruthPrimaryVertexSelectorAlg.VertexContainer = 'PrimaryVertices'
    algSeq.TruthPrimaryVertexSelectorAlg.MinVertices = 1

    import importlib
    try:
        analysisModule = importlib.import_module(analysisName)
    except ModuleNotFoundError:
        raise Exception(f'The package and module for your --analysis could not be found: {analysisName}')
    try:
        analysisModule.makeTruthConfiguration(flags, algSeq)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeTruthConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematicsPartonLevel'

    return algSeq

def makeParticleLevelSequence(analysisName, flags, noSystematics=False):
    algSeq = AnaAlgSequence()

    if flags.Input.DataType is DataType.Data:
        return algSeq
    sysService = createService('CP::SystematicsSvc', 'SystematicsSvc', sequence=algSeq)
    # we always want systematics!
    sysService.sigmaRecommended = 1

    # filter-out events without primary vertex
    algSeq += createAlgorithm('CP::VertexSelectionAlg',
                              'ParticleLevelPrimaryVertexSelectorAlg')
    algSeq.ParticleLevelPrimaryVertexSelectorAlg.VertexContainer = 'PrimaryVertices'
    algSeq.ParticleLevelPrimaryVertexSelectorAlg.MinVertices = 1

    import importlib
    try:
        analysisModule = importlib.import_module(analysisName)
    except ModuleNotFoundError:
        raise Exception(f'The package and module for your --analysis could not be found: {analysisName}')
    try:
        analysisModule.makeParticleLevelConfiguration(flags, algSeq)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeParticleLevelConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematicsParticleLevel'


    return algSeq

def makeTextBasedSequence(analysisName, filename, flags, noSystematics=False):
    algSeq = AnaAlgSequence()

    if flags.Input.DataType is DataType.Data and filename in ['particle','parton']:
        return algSeq

    yamlconfig = PathResolver.find_file(f'{analysisName}/{filename}.yaml', "CALIBPATH", PathResolver.RecursiveSearch)
    if not yamlconfig:
        raise FileNotFoundError(f'PathResolver failed to locate \"{analysisName}/{filename}.yaml\" config file!'
                                'Check if you have a typo in -t/--text-config argument or missing file in the analysis configuration sub-directory.')
    print(">>> Setting up configuration based on YAML config:")
    print(yamlconfig + "\n")
    config = TextConfig(yamlconfig)

    # ==============================
    # INSERT CUSTOM BLOCKS BELOW
    # it's a good idea to keep "pos='Output'" to make sure the custom block
    # is configured *before* the Output one, so custom containers are
    # treated properly.

    # from TopCPToolkit.<module> import <config block>
    # config.addAlgConfigBlock(algName='<short name>',
    #                          alg=<config block>, pos='Output')
    # or use the "AddConfigBlocks:" block directly in YAML.
    

    # END OF CUSTOM BLOCKS
    # ===============================

    print(">>> Configuring algorithms based on YAML file")
    configSeq = config.configure()

    print(">>> Configuration used:")
    config.printConfig()

    configAccumulator = ConfigAccumulator(autoconfigFromFlags=flags,
                                          algSeq=algSeq,
                                          noSystematics=noSystematics)
    configSeq.fullConfigure(configAccumulator)

    return algSeq
