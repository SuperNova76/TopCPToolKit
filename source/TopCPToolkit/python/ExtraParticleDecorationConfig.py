from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class ExtraParticleDecorationConfig(ConfigBlock):
    """ConfigBlock to add generic particle decorations"""
    
    def __init__(self):
        super(ExtraParticleDecorationConfig, self).__init__('ExtraParticleDecoration')
        self.addOption('particles', None, type=str)
    
    def makeAlgs(self, config):
        particles = config.readName(self.particles)

        alg = config.createAlgorithm('top::ExtraParticleDecorationAlg', 'customDecorations')
        alg.particles = particles

        config.addOutputVar(self.particles, 'e_%SYS%', 'e')
