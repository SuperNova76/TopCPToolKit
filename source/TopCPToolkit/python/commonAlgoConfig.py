# File for configuration of common stuff
# includes event cleaning, GRL, PRW and MC weight
from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnalysisAlgorithmsConfig.ConfigAccumulator import ConfigAccumulator
from AnalysisAlgorithmsConfig.ConfigText import TextConfig, addDefaultAlgs
from AnaAlgorithm.DualUseConfig import createAlgorithm, createService
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
from TopCPToolkit import metaConfig
from PathResolver import PathResolver


def makeRecoSequence(analysisName, flags, noSystematics=False, noFilter=False):
    algSeq = AnaAlgSequence()

    configSeq = ConfigSequence()

    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeCommonServicesConfig
    makeCommonServicesConfig(configSeq)
    configSeq.setOptionValue('.runSystematics', not noSystematics)

    import importlib
    try:
        analysisModule = importlib.import_module(analysisName)
    except ModuleNotFoundError:
        raise Exception(f'The package and module for your --analysis could not be found: {analysisName}')
    try:
        analysisModule.makeRecoConfiguration(flags, algSeq, configSeq, noFilter)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeRecoConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'

    return algSeq


def add_event_cleaning(configSeq, flags, runEventCleaning=True):
    # primary vertex ,event cleaning (jet clean loosebad) and GoodRunsList selection
    from AsgAnalysisAlgorithms.EventCleaningConfig import makeEventCleaningConfig
    is_data = (flags.Input.DataType is DataType.Data)
    if is_data:
        GRLFiles = [metaConfig.get_grl(flags)]
    makeEventCleaningConfig(configSeq,
                            runPrimaryVertexSelection=True,
                            runEventCleaning=runEventCleaning,
                            userGRLFiles=(GRLFiles if is_data else None))


def add_mc_weights(configSeq, flags, branches):
    # run PMG TruthWeightTool on MC only
    print('RunNumber: ', flags.Input.RunNumberAsInt)
    if flags.Input.DataType is not DataType.Data:
        from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeGeneratorAnalysisConfig
        makeGeneratorAnalysisConfig(configSeq,
                                    saveCutBookkeepers=True,
                                    runNumber=flags.Input.RunNumberAsInt,
                                    cutBookkeepersSystematics=True)


def add_PRW(configSeq, flags, branches):
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makePileupReweightingConfig
    dataType = flags.Input.DataType
    if dataType is DataType.Data:
        branches += [
            'EventInfo.runNumber -> runNumber',
            'EventInfo.eventNumber -> eventNumber'
        ]
        return
    makePileupReweightingConfig(configSeq,
                                campaign=flags.Input.MCCampaign,
                                useDefaultConfig=True)


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

    yamlconfig = PathResolver.FindCalibFile(f'TopCPToolkit/configs/{analysisName}/{filename}.yaml')
    config = TextConfig(yamlconfig)

    print(">>> Configuration file read in:")
    config.printConfig()

    print(">>> Adding default algorithms")
    addDefaultAlgs(config, dataType=flags.Input.DataType,
                   isPhyslite=flags.Input.isPHYSLITE, noPhysliteBroken=True,
                   noSystematics=noSystematics)

    # ==============================
    # INSERT CUSTOM BLOCKS BELOW
    # it's a good idea to keep "pos='Output'" to make sure the custom block
    # is configured *before* the Output one, so custom containers are
    # treated properly.

    from TopCPToolkit.PerEventSFCalculatorConfig import PerEventSFCalculatorConfig
    config.addAlgConfigBlock(algName='PerEventBtagSF',
                             alg=PerEventSFCalculatorConfig, pos='Output')
    from TopCPToolkit.LeptonSFCalculatorConfig import LeptonSFCalculatorConfig
    config.addAlgConfigBlock(algName='LeptonSF',
                             alg=LeptonSFCalculatorConfig, pos='Output')
    from TopCPToolkit.ExtraParticleDecorationConfig import ExtraParticleDecorationConfig
    config.addAlgConfigBlock(algName='ExtraParticleDecoration',
                             alg=ExtraParticleDecorationConfig, pos='Output')
    from TopCPToolkit.KLFitterConfig import KLFitterConfig
    config.addAlgConfigBlock(algName='KLFitter',
                             alg=KLFitterConfig, pos='Output')
    from TopCPToolkit.TopSpaNetConfig import TopSpaNetConfig
    config.addAlgConfigBlock(algName='SpaNet',
                             alg=TopSpaNetConfig, pos='Output')
    from TopCPToolkit.particleLevelConfig import particleLevelConfig
    config.addAlgConfigBlock(algName='ParticleLevel',
                             alg=particleLevelConfig, pos='Output')
    from TopCPToolkit.truthConfig import truthConfig
    config.addAlgConfigBlock(algName='PartonHistory',
                             alg=truthConfig, pos='Output')
    from TopCPToolkit.TtbarNNLORecursiveRewConfig import TtbarNNLORecursiveRewConfig
    config.addAlgConfigBlock(algName='TtbarNNLO',
                             alg=TtbarNNLORecursiveRewConfig, pos='Output')

    # END OF CUSTOM BLOCKS
    # ===============================
    config.printAlgs(printOpts=True)

    print(">>> Configuring algorithms based on YAML file")
    configSeq = config.configure()

    print(">>> Configuration used:")
    config.printConfig()

    configAccumulator = ConfigAccumulator(dataType=flags.Input.DataType, campaign=flags.Input.MCCampaign,
                                          geometry=flags.Input.LHCPeriod, autoconfigFromFlags=flags,
                                          algSeq=algSeq, isPhyslite=flags.Input.isPHYSLITE)
    configSeq.fullConfigure(configAccumulator)

    return algSeq
