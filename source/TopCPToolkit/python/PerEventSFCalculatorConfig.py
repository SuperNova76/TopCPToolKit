from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class PerEventSFCalculatorConfig(ConfigBlock):
    """
    ConfigBlock for PerEventSFCalculator algorithm,
    which decorates product of per-object SF onto EventInfo object.
    """

    def __init__(self, name):
        super(PerEventSFCalculatorConfig, self).__init__()
        self.algName = name
        self.addOption('particles', '', type=str)
        self.addOption('objectSF', '', type=str)
        self.addOption('eventSF', '', type=str)

    def makeAlgs(self, config):
        particles, selection = config.readNameAndSelection(self.particles)
        alg = config.createAlgorithm('CP::AsgEventScaleFactorAlg', self.algName)
        alg.particles = particles
        alg.preselection = selection
        alg.scaleFactorInputDecoration = self.objectSF
        alg.scaleFactorOutputDecoration = self.eventSF
