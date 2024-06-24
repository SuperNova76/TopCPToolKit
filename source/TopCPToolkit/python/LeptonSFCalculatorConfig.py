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

        alg = config.createAlgorithm('top::LeptonSFCalculatorAlg',
                                     f'leptonSFCalculator_{self.lepton_postfix}')

        if self.electrons:
            electrons, electronSelection = config.readNameAndSelection(self.electrons)
            alg.electrons                = electrons
            alg.electronSelection        = electronSelection
        if self.muons:
            muons, muonSelection         = config.readNameAndSelection(self.muons)
            alg.muons                    = muons
            alg.muonSelection            = muonSelection
        if self.photons:
            photons, photonSelection     = config.readNameAndSelection(self.photons)
            alg.photons                  = photons
            alg.photonSelection          = photonSelection

        alg.electronRecoSF = f'el_reco_effSF_{self.lepton_postfix}_%SYS%'
        alg.electronIDSF   = f'el_id_effSF_{self.lepton_postfix}_%SYS%'
        if self.electrons and 'isolated' in alg.electronSelection:
            alg.electronIsolSF = f'el_isol_effSF_{self.lepton_postfix}_%SYS%'
        else:
            alg.electronIsolSF = ''
        alg.muonRecoSF     = f'muon_reco_effSF_{self.lepton_postfix}_%SYS%'
        if self.muons and 'isolated' in alg.muonSelection:
            alg.muonIsolSF = f'muon_isol_effSF_{self.lepton_postfix}_%SYS%'
        else:
            alg.muonIsolSF = ''
        alg.muonTTVASF     = f'muon_TTVA_effSF_{self.lepton_postfix}_%SYS%'
        alg.photonIDSF     = f'ph_id_effSF_{self.lepton_postfix}_%SYS%'
        if self.photons and 'isolated' in alg.photonSelection:
            alg.photonIsolSF = f'ph_isol_effSF_{self.lepton_postfix}_%SYS%'
        else:
            alg.photonIsolSF = ''
        alg.event_leptonSF = f'leptonSF_{self.lepton_postfix}_%SYS%'

        config.addOutputVar('EventInfo', alg.event_leptonSF, f'weight_leptonSF_{self.lepton_postfix}')
