# File for configuration of common stuff
# includes event cleaning, GRL, PRW and MC weight
from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnaAlgorithm.DualUseConfig import createAlgorithm, createService
from TopCPToolkit import metaConfig


def makeRecoSequence(analysisName, metadata, debugHistograms=True, noSystematics=False, noFilter=False):
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
        analysisModule.makeRecoConfiguration(metadata, algSeq, configSeq, debugHistograms, noFilter)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeRecoConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'

    return algSeq


def add_event_cleaning(configSeq, metadata, runEventCleaning=True):
    # primary vertex ,event cleaning (jet clean loosebad) and GoodRunsList selection
    from AsgAnalysisAlgorithms.EventCleaningConfig import makeEventCleaningConfig
    is_data = (metaConfig.get_data_type(metadata) == 'data')
    if is_data:
        GRLFiles = [metaConfig.get_grl(metadata)]
    makeEventCleaningConfig(configSeq,
                            runPrimaryVertexSelection=True,
                            runEventCleaning=runEventCleaning,
                            userGRLFiles=(GRLFiles if is_data else None))


def add_mc_weights(configSeq, metadata, branches):
    # run PMG TruthWeightTool on MC only
    dataType = metaConfig.get_data_type(metadata)
    isRun3 = metaConfig.isRun3(metadata)
    if dataType != 'data':
        runNumber = metaConfig.get_run_number(metadata)
        from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeGeneratorAnalysisConfig
        makeGeneratorAnalysisConfig(configSeq,
                                    saveCutBookkeepers=True,
                                    runNumber=runNumber,
                                    cutBookkeepersSystematics=True)
        branches += [
            'EventInfo.generatorWeight_%SYS% -> weight_mc_%SYS%'
        ]
        if not isRun3:
            branches += [
                'EventInfo.beamSpotWeight -> weight_beamspot'
            ]


def add_PRW(configSeq, metadata, branches):
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makePileupReweightingConfig
    dataType = metaConfig.get_data_type(metadata)
    if dataType == 'data':
        return
    campaign = metaConfig.get_campaign(metadata)
    makePileupReweightingConfig(configSeq,
                                campaign=campaign,
                                useDefaultConfig=True)
    if dataType != 'data':
        branches += ['EventInfo.PileupWeight_%SYS% -> weight_pileup_%SYS%']

def makeTruthSequence(analysisName, metadata, debugHistograms=True, noSystematics=False):
    algSeq = AnaAlgSequence()

    if metaConfig.get_data_type(metadata) == 'data':
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
        analysisModule.makeTruthConfiguration(metadata, algSeq, debugHistograms)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeTruthConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'

    return algSeq

def makeParticleLevelSequence(analysisName, metadata, debugHistograms=True, noSystematics=False):
    algSeq = AnaAlgSequence()

    if metaConfig.get_data_type(metadata) == 'data':
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
        analysisModule.makeParticleLevelConfiguration(metadata, algSeq, debugHistograms)
    except AttributeError:
        raise Exception('The analysis you specified via --analysis does not have makeParticleLevelConfiguration method implemented.'
                        'This is needed to configure the CP algorithms')

    # Add an histogram to keep track of all the systematic names
    algSeq += createAlgorithm('CP::SysListDumperAlg', 'SystematicsPrinter')
    algSeq.SystematicsPrinter.histogramName = 'listOfSystematics'


    return algSeq
