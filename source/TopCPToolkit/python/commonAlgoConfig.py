# File for configuration of common stuff
# includes event cleaning, GRL, PRW and MC weight
from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnaAlgorithm.DualUseConfig import createAlgorithm, createService
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
from TopCPToolkit import metaConfig


def makeRecoSequence(analysisName, flags, debugHistograms=True, noSystematics=False, noFilter=False):
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
        analysisModule.makeRecoConfiguration(flags, algSeq, configSeq, debugHistograms, noFilter)
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

def makeTruthSequence(analysisName, flags, debugHistograms=True, noSystematics=False):
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
        analysisModule.makeTruthConfiguration(flags, algSeq, debugHistograms)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeTruthConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'

    return algSeq

def makeParticleLevelSequence(analysisName, flags, debugHistograms=True, noSystematics=False):
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
        analysisModule.makeParticleLevelConfiguration(flags, algSeq, debugHistograms)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeParticleLevelConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'


    return algSeq
