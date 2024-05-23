from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class IOStatsConfig(ConfigBlock):
    """Print what branches are used in analysis"""
    
    def __init__(self):
        super(IOStatsConfig, self).__init__()
        self.addOption('autoIncludeLinks', False, type=bool)

    def makeAlgs(self, config):
        alg = config.createAlgorithm('top::IOStatsAlg', 'IOStatsAlg')
        alg.autoIncludeLinks = self.autoIncludeLinks