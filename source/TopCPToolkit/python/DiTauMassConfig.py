from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class DiTauMassConfig(ConfigBlock):
  """ConfigBlock for the di-tau Missing Mass Calculator algorithm"""

  def __init__(self):
    super(DiTauMassConfig, self).__init__()
    self.addOption('electrons', '', type=str)
    self.addOption('muons', '', type=str)
    self.addOption('jets', '', type=str)
    self.addOption('taus', '', type=str)
    self.addOption('met', '', type=str)
    self.addOption('eventSelection', '', type=str)
    self.addOption('saveExtraVariables', False, type=bool)
    self.addOption('floatStopCriterion', True, type=bool)
    self.addOption('calibration', '2019', type=str)
    self.addOption('nSigmaMet', -1, type=int)
    self.addOption('useTailCleanup', -1, type=int)
    self.addOption('niterFit2', -1, type=int)
    self.addOption('niterFit3', -1, type=int)
    self.addOption('useTauProbability', 1, type=int)
    self.addOption('useMnuProbability', False, type=bool)
    self.addOption('useDefaultSettings', -1, type=int)
    self.addOption('useEfficiencyRecovery', -1, type=int)
    self.addOption('useMETdphiLL', False, type=bool)
    self.addOption('paramFilePath', 'MMC_params_v1_fixed.root', type=str)
    self.addOption('nJetsMinPt', 30000., type=float)

  def makeAlgs(self, config):
    alg = config.createAlgorithm('DiTauMassCalculatorAlg', 'DiTauMMCAlg')
    alg.electrons, alg.electronSelection = config.readNameAndSelection(self.electrons)
    alg.muons, alg.muonSelection = config.readNameAndSelection(self.muons)
    alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
    alg.taus, alg.tauSelection = config.readNameAndSelection(self.taus)
    alg.met = config.readName(self.met)
    alg.eventSelection = self.eventSelection
    alg.floatStopCrit = self.floatStopCriterion
    alg.calibSet = self.calibration
    alg.nSigmaMet = self.nSigmaMet
    alg.useTailCleanup = self.useTailCleanup
    alg.niterFit2 = self.niterFit2
    alg.niterFit3 = self.niterFit3
    alg.useTauProb = self.useTauProbability
    alg.useMnuProb = self.useMnuProbability
    alg.useDefaults = self.useDefaultSettings
    alg.useEfficiencyRecovery = self.useEfficiencyRecovery
    alg.useMETdphiLL = self.useMETdphiLL
    alg.paramFilePath = self.paramFilePath
    alg.nJetsMinPt = self.nJetsMinPt

    config.addOutputVar('EventInfo', 'mmc_fit_status_%SYS%', 'mmc_fit_status')
    config.addOutputVar('EventInfo', 'mmc_maxw_mass_%SYS%', 'mmc_maxw_mass')
    config.addOutputVar('EventInfo', 'mmc_mlm_mass_%SYS%', 'mmc_mlm_mass')
    config.addOutputVar('EventInfo', 'mmc_mlnu3p_mass_%SYS%', 'mmc_mlnu3p_mass')

    if self.saveExtraVariables:
      config.addOutputVar('EventInfo', 'mmc_mlnu3p_res_4vect_%SYS%', 'mmc_mlnu3p_res_4vect')
      config.addOutputVar('EventInfo', 'mmc_mlnu3p_nu1_4vect_%SYS%', 'mmc_mlnu3p_nu1_4vect')
      config.addOutputVar('EventInfo', 'mmc_mlnu3p_nu2_4vect_%SYS%', 'mmc_mlnu3p_nu2_4vect')
      config.addOutputVar('EventInfo', 'mmc_mlnu3p_tau1_4vect_%SYS%', 'mmc_mlnu3p_tau1_4vect')
      config.addOutputVar('EventInfo', 'mmc_mlnu3p_tau2_4vect_%SYS%', 'mmc_mlnu3p_tau2_4vect')
      config.addOutputVar('EventInfo', 'mmc_maxw_res_4vect_%SYS%', 'mmc_maxw_res_4vect')
      config.addOutputVar('EventInfo', 'mmc_maxw_nu1_4vect_%SYS%', 'mmc_maxw_nu1_4vect')
      config.addOutputVar('EventInfo', 'mmc_maxw_nu2_4vect_%SYS%', 'mmc_maxw_nu2_4vect')
      config.addOutputVar('EventInfo', 'mmc_maxw_tau1_4vect_%SYS%', 'mmc_maxw_tau1_4vect')
      config.addOutputVar('EventInfo', 'mmc_maxw_tau2_4vect_%SYS%', 'mmc_maxw_tau2_4vect')
