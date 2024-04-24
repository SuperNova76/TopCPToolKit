from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class ExtraPhotonDecorationConfig(ConfigBlock):
    def __init__(self):
        super(ExtraPhotonDecorationConfig, self).__init__()
        self.addOption('photons', None, type=str)
    
    def makeAlgs(self, config):
        photons = config.readName(self.photons)

        alg = config.createAlgorithm('top::ExtraPhotonDecorationAlg', 'ExtraPhotonDecorationAlg')
        alg.photons = photons

        config.addOutputVar(self.photons, 'conversionType_%SYS%', 'conversionType')
        config.addOutputVar(self.photons, 'caloEta_%SYS%', 'caloEta')

