from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock
from AthenaConfiguration.Enums import LHCPeriod

class BTagScoresConfig(ConfigBlock):

    def __init__ (self, containerName) :
        super (BTagScoresConfig, self).__init__()
        self.containerName = containerName
        self.addOption('bTagCalibFile', None, type=str)
        self.addOption('eventSelection', '', type=str)
        self.addOption('minPt', 5000.0, type=float)
        self.addOption('taggerName', 'GN2v00LegacyWP', type=str)
        self.addOption('saveAllProbabilities', True, type=bool)

    def makeAlgs(self, config):
        alg = config.createAlgorithm('BTaggingScoresAlg', 'BTagScoringAlg')
        alg.jets = config.readName (self.containerName)
        alg.eventSelection = self.eventSelection
        alg.taggerName = self.taggerName
        jetCollection = config.originalName (self.containerName)
        # Configure the b-tagging selection tool
        # First get the correct calibration file
        if self.bTagCalibFile is not None :
            bTagCalibFile = self.bTagCalibFile
        else:
            if config.geometry() == LHCPeriod.Run2:
                bTagCalibFile = "xAODBTaggingEfficiency/13TeV/2023-22-13TeV-MC20-CDI-2023-09-13_v1.root"
            elif config.geometry() >= LHCPeriod.Run3:
                bTagCalibFile = "xAODBTaggingEfficiency/13p6TeV/2023-22-13TeV-MC21-CDI-2023-09-13_v1.root"

        config.addPrivateTool( 'selectionTool', 'BTaggingSelectionTool' )
        alg.selectionTool.TaggerName = self.taggerName
        alg.selectionTool.OperatingPoint = 'Continuous' # This is needed to get the jet probabilities
        alg.selectionTool.JetAuthor = jetCollection
        alg.selectionTool.FlvTagCutDefinitionsFileName = bTagCalibFile
        alg.selectionTool.MinPt = self.minPt
        
        config.addOutputVar('AnaJets', 'btagScore_%SYS%', 'btagScore_'+self.taggerName)
        if self.saveAllProbabilities:
            config.addOutputVar('AnaJets', 'prob_pb_%SYS%', 'prob_pb_'+self.taggerName)
            config.addOutputVar('AnaJets', 'prob_pc_%SYS%', 'prob_pc_'+self.taggerName)
            config.addOutputVar('AnaJets', 'prob_pl_%SYS%', 'prob_pl_'+self.taggerName)
    
