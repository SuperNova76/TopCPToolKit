from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType


class LeptonSFCalculatorConfig(ConfigBlock):
    """ConfigBlock for our test analysis algorithm"""

    def __init__(self):
        super(LeptonSFCalculatorConfig, self).__init__()
        self.addOption('electrons', None, type=str)
        self.addOption('muons', None, type=str)
        self.addOption('photons', None, type=str)
        self.addOption('lepton_postfix', None, type=str)

    def makeAlgs(self, config):
        if config.dataType() is DataType.Data: return

        electrons, electronSelection = config.readNameAndSelection(self.electrons)
        muons, muonSelection         = config.readNameAndSelection(self.muons)
        photons, photonSelection     = config.readNameAndSelection(self.photons)

        alg = config.createAlgorithm('top::LeptonSFCalculatorAlg', 'leptonSFCalculator')
        alg.electrons = electrons
        alg.electronSelection = electronSelection
        alg.muons = muons
        alg.muonSelection = muonSelection
        alg.photons = photons
        alg.photonSelection = photonSelection
        alg.electronRecoSF = f'el_reco_effSF_{self.lepton_postfix}_%SYS%'
        alg.electronIDSF = f'el_id_effSF_{self.lepton_postfix}_%SYS%'
        alg.electronIsolSF = f'el_isol_effSF_{self.lepton_postfix}_%SYS%'
        alg.muonRecoSF = f'muon_reco_effSF_{self.lepton_postfix}_%SYS%'
        alg.muonIsolSF = f'muon_isol_effSF_{self.lepton_postfix}_%SYS%'
        alg.muonTTVASF = f'muon_TTVA_effSF_{self.lepton_postfix}_%SYS%'
        alg.photonIDSF = f'ph_id_effSF_{self.lepton_postfix}_%SYS%'
        alg.photonIsolSF = f'ph_isol_effSF_{self.lepton_postfix}_%SYS%'
        alg.event_leptonSF = f'leptonSF_{self.lepton_postfix}_%SYS%'

        config.addOutputVar('EventInfo', alg.event_leptonSF, f'weight_leptonSF_{self.lepton_postfix}')
