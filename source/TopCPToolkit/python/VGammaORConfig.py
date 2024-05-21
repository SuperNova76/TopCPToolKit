from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType

class VGammaORConfig(ConfigBlock):

    def __init__(self):
        super(VGammaORConfig, self).__init__()
        self.addOption('dR_lepton_photon_cuts', None, type=list)
        self.addOption('photon_pT_cuts', None, type=list)
    
    def makeAlgs(self, config):
        if config.dataType() is DataType.Data: return
        alg = config.createAlgorithm('top::VGammaORAlg', 'VGammaORAlg')

        config.addPrivateTool('VGammaORTool', 'VGammaORTool')
        alg.VGammaORTool.dR_lepton_photon_cuts = self.dR_lepton_photon_cuts
        alg.VGammaORTool.photon_pT_cuts = self.photon_pT_cuts

        config.addOutputVar('EventInfo', 'in_vgamma_overlap_%SYS%', 'in_vgamma_overlap', noSys=True)