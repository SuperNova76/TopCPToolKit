from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class EventSelectionTestConfig(ConfigBlock):
    """ConfigBlock for testing very minimalistic lepton+jets ttbar event selection"""

    def __init__(self):
        super(EventSelectionTestConfig, self).__init__('TtbarEventSelectionTest')
        # these options are all mandatory
        self.addOption('electrons', None, type=str)
        self.addOption('muons', None, type=str)
        self.addOption('jets', None, type=str)
        self.addOption('btagDecoration', None, type=str)

    def makeAlgs(self, config):
        alg = config.createAlgorithm('top::EventSelectionTestAlg', 'LJetsSelection')
        alg.electrons, alg.electronSelection = config.readNameAndSelection(self.electrons)
        alg.muons, alg.muonSelection = config.readNameAndSelection(self.muons)
        alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
        alg.BTaggingDecoration = self.btagDecoration
        alg.elJetsDecisionFlag = 'ejets_%SYS%'
        alg.muJetsDecisionFlag = 'mujets_%SYS%'
        alg.eventDecisionOutputDecoration = 'eventFilterTtbar_%SYS%'

        config.addOutputVar('EventInfo', alg.eventDecisionOutputDecoration, 'event_pass')
        config.addOutputVar('EventInfo', alg.elJetsDecisionFlag, 'ejets_pass')
        config.addOutputVar('EventInfo', alg.muJetsDecisionFlag, 'mujets_pass')
