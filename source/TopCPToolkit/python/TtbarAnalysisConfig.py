from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class TtbarAnalysisConfig(ConfigBlock):
    """ConfigBlock for our test analysis algorithm"""

    def __init__(self):
        super(TtbarAnalysisConfig, self).__init__('TtbarAnalysis')
        self.addOption('electrons', None, type=str)
        self.addOption('muons', None, type=str)
        self.addOption('jets', None, type=str)
        self.addOption('lepton_postfix', None, type=str)

    def makeAlgs(self, config):
        electrons, electronSelection = config.readNameAndSelection(self.electrons)
        muons, muonSelection = config.readNameAndSelection(self.muons)
        jets, jetSelection = config.readNameAndSelection(self.jets)

        alg = config.createAlgorithm('top::TtbarCPalgoAnalysis', 'customTtbarDecorations')
        alg.electrons = electrons
        alg.muons = muons
        alg.jets = jets

        config.addOutputVar(electrons, 'e_%SYS%', 'e')
        config.addOutputVar(muons, 'e_%SYS%', 'e')
        config.addOutputVar(jets, 'e_%SYS%', 'e')

        alg = config.createAlgorithm('top::LeptonSFCalculator', 'leptonSFCalculator')
        alg.electrons = electrons
        alg.electronSelection = electronSelection
        alg.muons = muons
        alg.muonSelection = muonSelection
        alg.electronSF = f'el_reco_effSF_{self.lepton_postfix}_%SYS%'
        alg.muonSF = f'muon_reco_effSF_{self.lepton_postfix}_%SYS%'
        alg.event_leptonSF = f'leptonSF_{self.lepton_postfix}_%SYS%'

        config.addOutputVar('EventInfo', alg.event_leptonSF, alg.event_leptonSF.split("_%SYS")[0], isEventLevel=True)