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
        if config.dataType() != 'data':
            particles, selection = config.readNameAndSelection(self.particles)
            alg = config.createAlgorithm('CP::AsgEventScaleFactorAlg', self.algName)
            alg.particles = particles
            alg.preselection = selection
            alg.scaleFactorInputDecoration = self.objectSF
            alg.scaleFactorOutputDecoration = self.eventSF

            config.addOutputVar('EventInfo', alg.scaleFactorOutputDecoration, 'weight_'+alg.scaleFactorOutputDecoration.split("_%SYS%")[0])
