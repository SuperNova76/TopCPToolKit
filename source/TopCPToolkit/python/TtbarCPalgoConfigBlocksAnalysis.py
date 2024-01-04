from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnalysisAlgorithmsConfig.ConfigAccumulator import ConfigAccumulator
from AsgAnalysisAlgorithms.AsgAnalysisConfig import makePtEtaSelectionConfig
from TopCPToolkit.PerEventSFCalculatorConfig import PerEventSFCalculatorConfig
from TopCPToolkit import metaConfig, commonAlgoConfig


def makeRecoConfiguration(flags, algSeq, configSeq, noFilter=False):

    use_electrons = True
    use_muons = True
    use_jets = True
    use_photons = False
    use_taus = False
    use_MET = True
    use_track_jets = False
    use_largeR_jets = False

    outputContainers = {'': 'EventInfo'}  # for output NTuple config block
    reco_branches = []
    met_branches = []

    # primary vertex ,event cleaning (jet clean loosebad) and GoodRunsList selection
    commonAlgoConfig.add_event_cleaning(configSeq, flags)

    # run PMG TruthWeightTool on MC only
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeGeneratorAnalysisConfig
    makeGeneratorAnalysisConfig(configSeq)

    # PRW
    if not flags.Input.isPHYSLITE:
        from AsgAnalysisAlgorithms.AsgAnalysisConfig import makePileupReweightingConfig
        makePileupReweightingConfig(configSeq,
                                    campaign=flags.Input.MCCampaign,
                                    useDefaultConfig=True)

    # electrons
    if use_electrons:
        from EgammaAnalysisAlgorithms.ElectronAnalysisConfig import\
            makeElectronCalibrationConfig, makeElectronWorkingPointConfig
        WPLoose = 'TightLH.NonIso'  # no isolation
        WPTight = 'TightLH.Tight_VarRad'
        makeElectronCalibrationConfig(configSeq, 'AnaElectrons', crackVeto=True)
        makeElectronWorkingPointConfig(configSeq, 'AnaElectrons', WPLoose, chargeIDSelection=False, selectionName='loose')
        makeElectronWorkingPointConfig(configSeq, 'AnaElectrons', WPTight, chargeIDSelection=False, selectionName='tight')
        # TODO -- this probably not correct -- is it track or cluster eta ?
        makePtEtaSelectionConfig(configSeq, 'AnaElectrons', selectionDecoration='selectPtEta',
                                 selectionName='', minPt=25e3, maxEta=2.47)
        outputContainers['el_'] = 'OutElectrons'

    # muons
    if use_muons:
        from MuonAnalysisAlgorithms.MuonAnalysisConfig import\
            makeMuonCalibrationConfig, makeMuonWorkingPointConfig
        WPLoose = 'Medium.NonIso'
        WPTight = 'Medium.Tight_VarRad'
        makeMuonCalibrationConfig(configSeq, 'AnaMuons')
        makeMuonWorkingPointConfig(configSeq, 'AnaMuons', workingPoint=WPLoose, selectionName='loose')
        makeMuonWorkingPointConfig(configSeq, 'AnaMuons', workingPoint=WPTight, selectionName='tight', systematicBreakdown = True)
        # TODO -- eta cut probably wrong
        makePtEtaSelectionConfig(configSeq, 'AnaMuons', selectionDecoration='selectPtEta',
                                 selectionName='', minPt=25e3, maxEta=2.5)
        outputContainers['mu_'] = 'OutMuons'

    # small-R jets
    if use_jets:
        from JetAnalysisAlgorithms.JetAnalysisConfig import makeJetAnalysisConfig
        jetContainer = 'AntiKt4EMPFlowJets'
        makeJetAnalysisConfig(configSeq, 'AnaJets', jetContainer,
                              runGhostMuonAssociation=True, postfix='')
        configSeq.setOptionValue('.runNNJvtUpdate', True)
        configSeq.setOptionValue('.systematicsModelJER', 'Full')
        configSeq.setOptionValue('.systematicsModelJES', 'Category')
        from JetAnalysisAlgorithms.JetJvtAnalysisConfig import makeJetJvtAnalysisConfig
        makeJetJvtAnalysisConfig(configSeq, 'AnaJets', jetContainer, enableFJvt=False)

        makePtEtaSelectionConfig(configSeq, 'AnaJets', selectionDecoration='selectPtEta',
                                 selectionName='', minPt=25e3, maxEta=2.5)

        # b-tagging
        WPs = ['FixedCutBEff_85','FixedCutBEff_77','FixedCutBEff_70','FixedCutBEff_60','Continuous']
        btagger = 'DL1dv01'
        from FTagAnalysisAlgorithms.FTagAnalysisConfig import makeFTagAnalysisConfig
        for WP in WPs:
            # suppress CDI warnings due to missing SFs
            makeFTagAnalysisConfig(configSeq, 'AnaJets', btagWP=WP, noEffSF=False, minPt=25e3,
                                   generator="autoconfig",
                                   btagger=btagger, kinematicSelection=True, selectionName='')
            # calculate per-event b-tagging SF (alternative to storing per-jet SFs)
            cfg = PerEventSFCalculatorConfig(f'btagSFCalc_{btagger}_{WP}')
            cfg.particles = 'AnaJets.jvt'
            cfg.objectSF = f'ftag_effSF_{btagger}_{WP}_%SYS%'
            cfg.eventSF = f'btagSF_{btagger}_{WP}_%SYS%'
            configSeq.append(cfg)

        outputContainers['jet_'] = 'OutJets'

    # TODO VR track jets b-tagging -- not yet in CDI ?
    if use_track_jets:
        makeJetAnalysisConfig(configSeq, 'AnaTrackJets', 'AntiKtVR30Rmax4Rmin02PV0TrackJets',
                              postfix='track_jets')
        makePtEtaSelectionConfig(configSeq, 'AnaTrackJets',
                                 selectionDecoration='selectPtEta',
                                 selectionName='track_jets',
                                 minPt=10e3, maxEta=2.5)
        outputContainers['track_jet_'] = 'OutTrackJets'

    if use_largeR_jets:
        makeJetAnalysisConfig(configSeq, 'AnaLargeRJets', 'AntiKt10UFOCSSKSoftDropBeta100Zcut10Jets',
                              postfix='largeR_jets')
        makePtEtaSelectionConfig(configSeq, 'AnaLargeRJets',
                                 selectionDecoration='selectPtEta',
                                 selectionName='largeR_jets',
                                 minPt=350e3, maxEta=2.0)
        outputContainers['larger_jet_'] = 'OutLargeRJets'

    # photons
    if use_photons:
        from EgammaAnalysisAlgorithms.PhotonAnalysisConfig import\
            makePhotonCalibrationConfig, makePhotonWorkingPointConfig
        makePhotonCalibrationConfig(configSeq, 'AnaPhotons', recomputeIsEM=False)
        makePhotonWorkingPointConfig(configSeq, 'AnaPhotons', 'Tight.FixedCutTight',
                                     selectionName = 'tight', recomputeIsEM=False)
        makePhotonWorkingPointConfig(configSeq, 'AnaPhotons', 'Loose.Undefined',
                                     selectionName = 'loose', recomputeIsEM=False)
        makePtEtaSelectionConfig(configSeq, 'AnaPhotons', selectionDecoration='selectPtEta',
                                 selectionName='', minPt=25e3, maxEta=2.5)
        outputContainers['ph_'] = 'OutPhotons'

    # Taus
    if use_taus:
        from TauAnalysisAlgorithms.TauAnalysisConfig import\
            makeTauCalibrationConfig, makeTauWorkingPointConfig
        makeTauCalibrationConfig(configSeq, 'AnaTauJets')
        makeTauWorkingPointConfig(configSeq, 'AnaTauJets', workingPoint='Tight', selectionName='tight')
        makePtEtaSelectionConfig(configSeq, 'AnaTauJets',
                                 selectionDecoration='selectPtEta',
                                 selectionName='', minPt=25e3, maxEta=2.5)
        outputContainers['tau_'] = 'OutTauJets'

    # MET
    if use_MET:
        from MetAnalysisAlgorithms.MetAnalysisConfig import makeMetAnalysisConfig
        makeMetAnalysisConfig(configSeq, containerName='AnaMET',
                              electrons=('AnaElectrons.tight' if use_electrons else ''),
                              muons=('AnaMuons.tight' if use_muons else ''),
                              jets=('AnaJets' if use_jets else ''),  # use all jets for MET, it does it's own OR
                              photons=('AnaPhotons.tight&&selectPtEta' if use_photons else ''),
                              taus=('AnaTauJets.tight' if use_taus else ''))
        outputContainers['met_'] = 'AnaMET'

    # overlap removal
    from AsgAnalysisAlgorithms.OverlapAnalysisConfig import makeOverlapAnalysisConfig
    makeOverlapAnalysisConfig(configSeq,
                              electrons=('AnaElectrons.tight' if use_electrons else ''),
                              muons=('AnaMuons.tight' if use_muons else ''),
                              photons=('AnaPhotons.tight&&selectPtEta' if use_photons else ''),
                              jets=('AnaJets.jvt' if use_jets else ''),
                              taus=('AnaTauJets.tight' if use_taus else ''),
                              inputLabel='preselectOR',
                              outputLabel='passesOR')

    # global lepton trigger
    from TriggerAnalysisAlgorithms.TriggerAnalysisConfig import makeTriggerAnalysisConfig

    triggerChainsPerYear = {
        '2015': ['HLT_e24_lhmedium_L1EM20VH || HLT_e60_lhmedium || HLT_e120_lhloose', 'HLT_mu20_iloose_L1MU15 || HLT_mu50'],
        '2016': ['HLT_e26_lhtight_nod0_ivarloose || HLT_e60_lhmedium_nod0 || HLT_e140_lhloose_nod0', 'HLT_mu26_ivarmedium || HLT_mu50'],
        '2017': ['HLT_e26_lhtight_nod0_ivarloose || HLT_e60_lhmedium_nod0 || HLT_e140_lhloose_nod0', 'HLT_mu26_ivarmedium || HLT_mu50'],
        '2018': ['HLT_e26_lhtight_nod0_ivarloose || HLT_e60_lhmedium_nod0 || HLT_e140_lhloose_nod0', 'HLT_mu26_ivarmedium || HLT_mu50'],
        '2022': ['HLT_e26_lhtight_ivarloose_L1EM22VHI || HLT_e60_lhmedium_L1EM22VHI || HLT_e140_lhloose_L1EM22VHI', 'HLT_mu26_ivarmedium_L1MU14FCH || HLT_mu50_L1MU14FCH'],
    }
    individual_triggers = list(set(substring.strip() for chains_list in triggerChainsPerYear.values() for chain in chains_list for substring in chain.split('||')))

    makeTriggerAnalysisConfig(configSeq, triggerChainsPerYear=triggerChainsPerYear, noFilter=noFilter, electronWorkingPoint='Tight.Tight_VarRad', muonWorkingPoint='Tight.None',
                              electrons='AnaElectrons.tight', muons='AnaMuons.tight')

    # object-based cutflow
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeObjectCutFlowConfig
    if use_electrons:
        makeObjectCutFlowConfig(configSeq, 'AnaElectrons', selectionName='tight')
    if use_muons:
        makeObjectCutFlowConfig(configSeq, 'AnaMuons', selectionName='tight')
    if use_taus:
        makeObjectCutFlowConfig(configSeq, 'AnaTauJets', selectionName='tight')
    if use_photons:
        makeObjectCutFlowConfig(configSeq, 'AnaPhotons', selectionName='tight')
    if use_jets:
        makeObjectCutFlowConfig(configSeq, 'AnaJets', selectionName='jvt')
    if use_largeR_jets:
        makeObjectCutFlowConfig(configSeq, 'AnaLargeRJets', selectionName='')
    if use_track_jets:
        makeObjectCutFlowConfig(configSeq, 'AnaTrackJets', selectionName='')

    # a single lepton SF
    from TopCPToolkit.LeptonSFCalculatorConfig import LeptonSFCalculatorConfig
    cfg = LeptonSFCalculatorConfig()
    cfg.setOptionValue('electrons', 'AnaElectrons.tight')
    cfg.setOptionValue('muons', 'AnaMuons.tight')
    cfg.setOptionValue('lepton_postfix', 'tight')
    configSeq.append(cfg)

    from TopCPToolkit.ExtraParticleDecorationConfig import ExtraParticleDecorationConfig
    cfg = ExtraParticleDecorationConfig('El')
    cfg.setOptionValue('particles', 'AnaElectrons')
    configSeq.append(cfg)
    cfg = ExtraParticleDecorationConfig('Mu')
    cfg.setOptionValue('particles', 'AnaMuons')
    configSeq.append(cfg)
    cfg = ExtraParticleDecorationConfig('Jet')
    cfg.setOptionValue('particles', 'AnaJets')
    configSeq.append(cfg)

    # the IFF lepton classification
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import IFFLeptonDecorationBlock
    cfg = IFFLeptonDecorationBlock('AnaElectrons')
    configSeq.append(cfg)
    cfg = IFFLeptonDecorationBlock('AnaMuons')
    configSeq.append(cfg)

    # object thinning
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeOutputThinningConfig

    if use_electrons:
        # write out single electron container containg all leptons passing loose or tight and at the same time pass selectPtEta
        # i.e. there is a logical && between selection and selectionName
        makeOutputThinningConfig(configSeq, 'AnaElectrons',
                                 selectionName='tight||loose',
                                 outputName='OutElectrons')
    if use_muons:
        makeOutputThinningConfig(configSeq, 'AnaMuons',
                                 selectionName='tight||loose',
                                 outputName='OutMuons')
    if use_jets:
        makeOutputThinningConfig(configSeq, 'AnaJets',
                                 selectionName='jvt',
                                 outputName='OutJets')
    if use_photons:
        makeOutputThinningConfig(configSeq, 'AnaPhotons',
                                 selectionName='tight||loose',
                                 outputName='OutPhotons')
    if use_taus:
        makeOutputThinningConfig(configSeq, 'AnaTauJets',
                                 selectionName='tight',
                                 outputName='OutTauJets')
    if use_largeR_jets:
        makeOutputThinningConfig(configSeq, 'AnaLargeRJets',
                                 selectionName='largeR_jets',
                                 outputName='OutLargeRJets')
    if use_track_jets:
        makeOutputThinningConfig(configSeq, 'AnaTrackJets',
                                 selectionName='track_jets',
                                 outputName='OutTrackJets')

    from EventSelectionAlgorithms.EventSelectionConfig import makeMultipleEventSelectionConfigs
    mycuts = {
        'SUBcommon': """
JET_N_BTAG >= 2
JET_N_BTAG DL1dv01:FixedCutBEff_70 >= 1
JET_N 25000 >= 4
MET >= 20000
SAVE
""",
        'ejets': """
IMPORT SUBcommon
EL_N 25000 >= 1
EL_N tight 25000 == 1
MU_N 25000 == 0
MWT < 170000
MET+MWT > 40000
SAVE
""",
        'mujets': """
EL_N 25000 == 0
MU_N 25000 > 0
MU_N 25000 == 1
IMPORT SUBcommon
SAVE
""",
        'dilep': """
EL_N 25000 == 2
MU_N 25000 == 0
MLL >= 10000
OS
MLLWINDOW 100000 80000
SAVE
""",
        'supertight': """
JET_N 1000000 >= 1
SAVE
"""
    }
    makeMultipleEventSelectionConfigs(configSeq, electrons="AnaElectrons.loose", muons ="AnaMuons.tight", met="AnaMET",
                                      jets="AnaJets.jvt", btagDecoration=f'ftag_select_{btagger}_FixedCutBEff_85',
                                      preselection=None, selectionCutsDict = mycuts, noFilter=noFilter, cutFlowHistograms=True)

    from TopCPToolkit.KLFitterConfig import KLFitterConfig
    cfg = KLFitterConfig('KLFitterResult')
    cfg.setOptionValue('electrons', 'AnaElectrons.tight')
    cfg.setOptionValue('muons', 'AnaMuons.tight')
    cfg.setOptionValue('jets', 'AnaJets.jvt')
    cfg.setOptionValue('met', 'AnaMET')
    cfg.setOptionValue('likelihoodType', 'ttbar')
    cfg.setOptionValue('jetSelectionMode', 'kBtagPriorityFourJets')
    cfg.setOptionValue('btaggingMethod', 'kWorkingPoint')
    cfg.setOptionValue('btagger', btagger)
    cfg.setOptionValue('btagWP', 'FixedCutBEff_77')
    selectionRegionsConfig = 'selectionName:pass_ejets, leptonType: kElectron;'\
        'selectionName:pass_mujets, leptonType: kMuon'
    cfg.setOptionValue('selectionRegionsConfig', selectionRegionsConfig)
    configSeq.append(cfg)

    outputContainers['klfitter_'] = 'KLFitterResult'

    from TopCPToolkit.TopSpaNetConfig import TopSpaNetConfig
    for topology in ['TtbarLjets', 'TtbarLjetsNu']:
        cfg = TopSpaNetConfig()
        cfg.setOptionValue('electrons', 'AnaElectrons.tight')
        cfg.setOptionValue('muons', 'AnaMuons.tight')
        cfg.setOptionValue('jets', 'AnaJets.jvt')
        cfg.setOptionValue('met', 'AnaMET')
        cfg.setOptionValue('eventSelection', 'pass_ejets_%SYS%||pass_mujets_%SYS%')
        cfg.setOptionValue('topology', topology)
        configSeq.append(cfg)

    if use_taus:
        from TopCPToolkit.DiTauMassConfig import DiTauMassConfig
        cfg = DiTauMassConfig()
        cfg.setOptionValue('electrons', 'AnaElectrons.tight')
        cfg.setOptionValue('muons', 'AnaMuons.tight')
        cfg.setOptionValue('taus', 'AnaTauJets.tight')
        cfg.setOptionValue('jets', 'AnaJets.jvt')
        cfg.setOptionValue('met', 'AnaMET')
        cfg.setOptionValue('eventSelection', '')
        cfg.setOptionValue('saveExtraVariables', True)
        configSeq.append(cfg)

    from AsgAnalysisAlgorithms.BootstrapGeneratorConfig import makeBootstrapGeneratorConfig
    makeBootstrapGeneratorConfig(configSeq, nReplicas=2000, runOnMC=True)

    # add NTuple output config
    from AsgAnalysisAlgorithms.OutputAnalysisConfig import OutputAnalysisConfig
    cfg = OutputAnalysisConfig('reco')
    cfg.setOptionValue('treeName', 'reco')
    cfg.setOptionValue('vars', reco_branches)
    cfg.setOptionValue('metVars', met_branches)
    cfg.setOptionValue('containers', outputContainers)
    cfg.setOptionValue('commands',
                       ['disable jet_.*_eff.*',
                        'disable jet_jvtEfficiency.*',
                        'disable trigPassed_HLT.*',
                        'enable trigPassed_HLT_e.*']
                   )
    configSeq.append(cfg)

    # put everything together
    configAccumulator = ConfigAccumulator(algSeq, flags.Input.DataType,
                                          isPhyslite=flags.Input.isPHYSLITE,
                                          geometry=flags.Input.LHCPeriod,
                                          autoconfigFromFlags=flags)
    configSeq.fullConfigure(configAccumulator)


def makeTruthConfiguration(flags, algSeq):
    configSeq = ConfigSequence()

    truth_branches = []
    outputContainers = {'': 'EventInfo'}

    # PMG TruthWeightTool
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeGeneratorAnalysisConfig
    makeGeneratorAnalysisConfig(configSeq)

    # add all three Number variables by hand, since we don't run PRW
    truth_branches += [
        'EventInfo.runNumber       -> runNumber',
        'EventInfo.eventNumber     -> eventNumber',
        'EventInfo.mcChannelNumber -> mcChannelNumber',
    ]

    from TopCPToolkit.truthConfig import truthConfig
    cfg = truthConfig()
    cfg.setOptionValue('histories', 'Ttbar.TtbarLight')
    configSeq.append(cfg)
    outputContainers.update( cfg.getOutputContainers() )

    # NNLO reweighting
    from TopCPToolkit.TtbarNNLORecursiveRewConfig import TtbarNNLORecursiveRewConfig
    cfg = TtbarNNLORecursiveRewConfig()
    #cfg.setOptionValue('reweightType','3D')
    #cfg.setOptionValue('sampleID', 'aMCH7')
    configSeq.append(cfg)

    # add NTuple output config
    from AsgAnalysisAlgorithms.OutputAnalysisConfig import OutputAnalysisConfig
    cfg = OutputAnalysisConfig('truth')
    cfg.setOptionValue('treeName', 'truth')
    cfg.setOptionValue('vars', truth_branches)
    cfg.setOptionValue('containers', outputContainers)
    configSeq.append(cfg)

    # put everything together
    configAccumulator = ConfigAccumulator(algSeq, flags.Input.DataType,
                                          isPhyslite=flags.Input.isPHYSLITE,
                                          geometry=flags.Input.LHCPeriod,
                                          autoconfigFromFlags=flags)
    configSeq.fullConfigure(configAccumulator)


def makeParticleLevelConfiguration(flags, algSeq):
    configSeq = ConfigSequence()

    particleLevel_branches = []
    outputContainers = {'': 'EventInfo'}

    # PMG TruthWeightTool
    from AsgAnalysisAlgorithms.AsgAnalysisConfig import makeGeneratorAnalysisConfig
    makeGeneratorAnalysisConfig(configSeq)

    # add all three Number variables by hand, since we don't run PRW
    particleLevel_branches += [
        'EventInfo.runNumber       -> runNumber',
        'EventInfo.eventNumber     -> eventNumber',
        'EventInfo.mcChannelNumber -> mcChannelNumber',
    ]

    from TopCPToolkit.particleLevelConfig import particleLevelConfig
    cfg = particleLevelConfig()
    cfg.setOptionValue('useTruthLargeRJets', True)
    cfg.setOptionValue('useTruthPhotons', True)
    cfg.setOptionValue('useTruthTaus', True)
    configSeq.append(cfg)
    outputContainers.update( cfg.getOutputContainers() )

    # add NTuple output config
    from AsgAnalysisAlgorithms.OutputAnalysisConfig import OutputAnalysisConfig
    cfg = OutputAnalysisConfig('particleLevel')
    cfg.setOptionValue('treeName', 'particleLevel')
    cfg.setOptionValue('vars', particleLevel_branches)
    cfg.setOptionValue('containers', outputContainers)
    cfg.setOptionValue('metTermName', 'NonInt')
    configSeq.append(cfg)

    # put everything together
    configAccumulator = ConfigAccumulator(algSeq, flags.Input.DataType,
                                          isPhyslite=flags.Input.isPHYSLITE,
                                          geometry=flags.Input.LHCPeriod,
                                          autoconfigFromFlags=flags)
    configSeq.fullConfigure(configAccumulator)
