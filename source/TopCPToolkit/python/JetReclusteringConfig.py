from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class JetReclusteringConfig(ConfigBlock):
    """ConfigBlock for jet reclustering algorithm"""

    def __init__(self, containerName):
        super(JetReclusteringConfig, self).__init__()
        self.containerName = containerName
        self.addOption('jets', '', type=str)
        self.addOption('reclusteredJetsRadius', 1.0, type=float)
        self.addOption('minPt', 200000, type=float)

    def makeAlgs(self, config):

        alg = config.createAlgorithm('top::JetReclusteringAlg', 'JetReclusteringAlg')

        alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
        alg.reclusteredJets = config.writeName(self.containerName)
        alg.smallRjetIndices = 'smallRjetIndices_%SYS%'
        alg.rcJetEnergy = 'e_%SYS%'
        alg.reclusteredJetsRadius = self.reclusteredJetsRadius

        # prepare selection algorithm
        if self.minPt > 0:
            selAlg = config.createAlgorithm('CP::AsgSelectionAlg', 'RCJetsMinPtAlg')
            selAlg.selectionDecoration = 'passed_pt,as_bits'
            config.addPrivateTool('selectionTool', 'CP::AsgPtEtaSelectionTool')
            selAlg.selectionTool.minPt = self.minPt
            selAlg.particles = config.readName(self.containerName)
            selAlg.preselection = config.getPreselection(self.containerName, '')
            config.addSelection(self.containerName, 'passed_pt', selAlg.selectionDecoration)

        config.addOutputVar(self.containerName, 'pt', 'pt')
        config.addOutputVar(self.containerName, 'eta', 'eta')
        config.addOutputVar(self.containerName, 'phi', 'phi')
        config.addOutputVar(self.containerName, alg.rcJetEnergy, 'e')
        config.addOutputVar(self.containerName, alg.smallRjetIndices, 'small_r_jet_indices')
