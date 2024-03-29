from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class JetMatchingConfig(ConfigBlock):
    """ConfigBlock for jet matching algorithms"""

    def __init__(self):
        super(JetMatchingConfig, self).__init__()
        self.addOption('criticalDR', 0.3, type=float)
        self.addOption('jets', 'AnaJets', type=str)
        self.addOption('truthJets', 'AntiKt4TruthDressedWZJets', type=str)
        self.addOption('eventSelection', '', type=str)

    def makeAlgs(self, config):
        from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
        if config.dataType() is DataType.Data: 
            print(">>> Running on data. Will not run JetMatchingAlg.")
            return

        alg = config.createAlgorithm('top::JetMatchingAlg', 'JetMatchingAlg')
        alg.criticalDR = self.criticalDR
        alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
        alg.truthJets = self.truthJets
        alg.eventSelection = self.eventSelection
        
        alg.truth_jet_paired_index = 'truth_jet_paired_index_%SYS%'
        alg.reco_to_reco_jet_closest_dR = 'reco_to_reco_jet_closest_dR_%SYS%'
        alg.truth_to_truth_jet_closest_dR = 'truth_to_truth_jet_closest_dR_%SYS%'
        
        config.addOutputVar(self.jets.split('.')[0], alg.truth_jet_paired_index, 'truth_jet_paired_index', noSys=True)
        config.addOutputVar(self.jets.split('.')[0], alg.reco_to_reco_jet_closest_dR, 'reco_to_reco_jet_closest_dR')
        config.addOutputVar(self.jets.split('.')[0], alg.truth_to_truth_jet_closest_dR, 'truth_to_truth_jet_closest_dR', noSys=True)
