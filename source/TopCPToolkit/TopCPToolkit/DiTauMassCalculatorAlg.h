#ifndef DITAU_MASS_CALCULATOR_ALG_H
#define DITAU_MASS_CALCULATOR_ALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>
#include <xAODTau/TauJetContainer.h>
#include <xAODMissingET/MissingETContainer.h>
#include <xAODBase/IParticleContainer.h>
#include <xAODEventInfo/EventInfo.h>

#include <DiTauMassTools/MissingMassToolV2.h>
#include <TLorentzVector.h>

class DiTauMassCalculatorAlg final : public EL::AnaAlgorithm
{

public:
  DiTauMassCalculatorAlg(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;
  virtual StatusCode finalize() override;

private:
  // configurable properties
  float m_njets_min_pt;
  bool m_float_stop;
  std::string m_calib_set;
  double m_n_sigma_met;
  int m_use_tail_cleanup;
  int m_niter_fit_2;
  int m_niter_fit_3;
  int m_use_tau_prob;
  bool m_use_mnu_prob;
  int m_use_defaults;
  int m_use_eff_recovery;
  int m_use_met_dphill;
  std::string m_param_file_path;

  // the MMC tool
  std::unique_ptr<DiTauMassTools::MissingMassToolV2> m_mmc;

  // systematics
  CP::SysListHandle m_systematicsList{this};

  // inputs needed for reconstruction
  CP::SysReadHandle<xAOD::ElectronContainer> m_electronsHandle{
      this, "electrons", "", "the electron container to use"};
  CP::SysReadSelectionHandle m_electronSelection{
      this, "electronSelection", "", "the selection on the input electrons"};

  CP::SysReadHandle<xAOD::MuonContainer> m_muonsHandle{
      this, "muons", "", "the muon container to use"};
  CP::SysReadSelectionHandle m_muonSelection{
      this, "muonSelection", "", "the selection on the input muons"};

  CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle{
      this, "jets", "", "the jet container to use"};
  CP::SysReadSelectionHandle m_jetSelection{
      this, "jetSelection", "", "the selection on the input jets"};

  CP::SysReadHandle<xAOD::TauJetContainer> m_tausHandle{
      this, "taus", "", "the tau jet container to use"};
  CP::SysReadSelectionHandle m_tauSelection{
      this, "tauSelection", "", "the selection on the input tau jets"};

  CP::SysReadHandle<xAOD::MissingETContainer> m_metHandle{
      this, "met", "", "the MET container to use"};

  CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle{
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"};

  CP::SysReadSelectionHandle m_preselection{
      this, "eventSelection", "", "Name of the selection on which this MMC instance is allowed to run"};

  // output decorations
  CP::SysWriteDecorHandle<int> m_fitStatus_decor {
    this, "fitStatus", "mmc_fit_status_%SYS%", "Status of the MMC fit"
      };
  CP::SysWriteDecorHandle<double> m_maxw_mass_decor {
    this, "maxw_mass", "mmc_maxw_mass_%SYS%", "Mass of the resonance estimated by the MMC MaxW method"
      };
  CP::SysWriteDecorHandle<double> m_mlm_mass_decor {
    this, "mlm_mass", "mmc_mlm_mass_%SYS%", "Mass of the resonance estimated by the MMC MLM method"
      };
  CP::SysWriteDecorHandle<double> m_mlnu3p_mass_decor {
    this, "mlnu3p_mass", "mmc_mlnu3p_mass_%SYS%", "Mass of the resonance estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_mlnu3p_res_4vect_decor {
    this, "mlnu3p_res_4vect", "mmc_mlnu3p_res_4vect_%SYS%", "Four-momentum of the resonance estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_mlnu3p_nu1_4vect_decor {
    this, "mlnu3p_nu1_4vect", "mmc_mlnu3p_nu1_4vect_%SYS%", "Four-momentum of the leading pt neutrino estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_mlnu3p_nu2_4vect_decor {
    this, "mlnu3p_nu2_4vect", "mmc_mlnu3p_nu2_4vect_%SYS%", "Four-momentum of the subleading pt neutrino estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_mlnu3p_tau1_4vect_decor {
    this, "mlnu3p_tau1_4vect", "mmc_mlnu3p_tau1_4vect_%SYS%", "Four-momentum of the leading lepton estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_mlnu3p_tau2_4vect_decor {
    this, "mlnu3p_tau2_4vect", "mmc_mlnu3p_tau2_4vect_%SYS%", "Four-momentum of the subleading lepton estimated by the MMC MLNU3P method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_maxw_res_4vect_decor {
    this, "maxw_res_4vect", "mmc_maxw_res_4vect_%SYS%", "Mass of the resonance estimated by the MMC MaxW method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_maxw_nu1_4vect_decor {
    this, "maxw_nu1_4vect", "mmc_maxw_nu1_4vect_%SYS%", "Four-momentum of the leading pt neutrino estimated by the MMC MaxW method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_maxw_nu2_4vect_decor {
    this, "maxw_nu2_4vect", "mmc_maxw_nu2_4vect_%SYS%", "Four-momentum of the subleading pt neutrino estimated by the MMC MaxW method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_maxw_tau1_4vect_decor {
    this, "maxw_tau1_4vect", "mmc_maxw_tau1_4vect_%SYS%", "Four-momentum of the leading lepton estimated by the MMC MaxW method"
      };
  CP::SysWriteDecorHandle<TLorentzVector> m_maxw_tau2_4vect_decor {
    this, "maxw_tau2_4vect", "mmc_maxw_tau2_4vect_%SYS%", "Four-momentum of the subleading lepton estimated by the MMC MaxW method"
      };
};

#endif
