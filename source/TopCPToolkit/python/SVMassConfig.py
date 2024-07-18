from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class SVMassConfig(ConfigBlock):

    def __init__ (self, containerName) :
        super (SVMassConfig, self).__init__()
        self.containerName = containerName
        self.addOption('eventSelection', '', type=str)

    def makeAlgs(self, config):
        alg = config.createAlgorithm('SVMassAlg', 'SVMassAlg'+self.containerName)
        alg.jets = config.readName (self.containerName)
        alg.eventSelection = self.eventSelection

        config.addOutputVar(self.containerName, 'SVMass_%SYS%', 'SVMass')
