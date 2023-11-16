#include "TopCPToolkit/DiTauMassCalculatorAlg.h"

DiTauMassCalculatorAlg::DiTauMassCalculatorAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_njets_min_pt(30000.)
    , m_float_stop(true)
    , m_calib_set("2019")
    , m_n_sigma_met(-1)
    , m_use_tail_cleanup(-1)
    , m_niter_fit_2(-1)
    , m_niter_fit_3(-1)
    , m_use_tau_prob(1)
    , m_use_mnu_prob(false)
    , m_use_defaults(-1)
    , m_use_eff_recovery(-1)
    , m_use_met_dphill(false)
    , m_param_file_path("MMC_params_v1_fixed.root")
{
  declareProperty("nJetsMinPt", m_njets_min_pt, "Jet pT threshold (in MeV)");
  declareProperty("floatStopCrit", m_float_stop, "Activate floating stopping criterion");
  declareProperty("calibSet", m_calib_set, "Calibration set");
  declareProperty("nSigmaMet", m_n_sigma_met, "Number of sigmas for MET resolution scan");
  declareProperty("useTailCleanup", m_use_tail_cleanup, "Activate tail cleanup feature");
  declareProperty("niterFit2", m_niter_fit_2, "Number of iterations for each MET scan loop");
  declareProperty("niterFit3", m_niter_fit_3, "Number of iterations for each Mnu loop");
  declareProperty("useTauProb", m_use_tau_prob, "Apply tau probability");
  declareProperty("useMnuProb", m_use_mnu_prob, "Apply Mnu probability");
  declareProperty("useDefaults", m_use_defaults, "Take all default options from the tool itself");
  declareProperty("useEfficiencyRecovery", m_use_eff_recovery, "Enable refit of failed events to improve efficiency");
  declareProperty("useMETdphiLL", m_use_met_dphill, "MET resolution parameterised using sumET and dphiLL (only for lep-lep)");
  declareProperty("paramFilePath", m_param_file_path, "");
}

StatusCode DiTauMassCalculatorAlg::initialize()
{
  ANA_MSG_INFO("Initializing DiTauMassCalculatorAlg " << name());

  // the Missing Mass Calculator tool
  m_mmc = std::make_unique<DiTauMassTools::MissingMassToolV2>("MMCtool");
  ANA_CHECK(m_mmc->setProperty("Decorate", false)); // this sets decorations on EventInfo that are not compatible with systematics
  ANA_CHECK(m_mmc->setProperty("FloatStoppingCrit", m_float_stop));
  ANA_CHECK(m_mmc->setProperty("CalibSet", m_calib_set));
  ANA_CHECK(m_mmc->setProperty("NsigmaMET", m_n_sigma_met));
  ANA_CHECK(m_mmc->setProperty("UseTailCleanup", m_use_tail_cleanup));
  ANA_CHECK(m_mmc->setProperty("NiterFit2", m_niter_fit_2));
  ANA_CHECK(m_mmc->setProperty("NiterFit3", m_niter_fit_3));
  ANA_CHECK(m_mmc->setProperty("UseTauProbability", m_use_tau_prob));
  ANA_CHECK(m_mmc->setProperty("UseMnuProbability", m_use_mnu_prob));
  ANA_CHECK(m_mmc->setProperty("UseDefaults", m_use_defaults));
  ANA_CHECK(m_mmc->setProperty("UseEfficiencyRecovery", m_use_eff_recovery));
  ANA_CHECK(m_mmc->setProperty("UseMETDphiLL", m_use_met_dphill));
  ANA_CHECK(m_mmc->setProperty("ParamFilePath", m_param_file_path));
  if (this->msg().level()==MSG::DEBUG || this->msg().level()==MSG::VERBOSE) {
    ANA_CHECK(m_mmc->setProperty("UseVerbose", 1));
    ANA_CHECK(m_mmc->setProperty("OutputLevel", MSG::VERBOSE));
  }
  ANA_CHECK(m_mmc->initialize());

  // input handles
  ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
  ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));

  ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
  ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));

  ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
  ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));

  ANA_CHECK(m_tausHandle.initialize(m_systematicsList));
  ANA_CHECK(m_tauSelection.initialize(m_systematicsList, m_tausHandle, SG::AllowEmpty));

  ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
  ANA_CHECK(m_metHandle.initialize(m_systematicsList));
  ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

  // output handles
  ANA_CHECK(m_fitStatus_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_mass_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlm_mass_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_mass_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_res_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_nu1_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_nu2_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_tau1_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_mlnu3p_tau2_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_res_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_nu1_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_nu2_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_tau1_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_maxw_tau2_4vect_decor.initialize(m_systematicsList, m_eventInfoHandle));

  ANA_CHECK(m_systematicsList.initialize());

  return StatusCode::SUCCESS;
}

StatusCode DiTauMassCalculatorAlg::execute()
{
  for (const auto &sys : m_systematicsList.systematicsVector())
  {
    // retrieve the EventInfo
    const xAOD::EventInfo *evtInfo = nullptr;
    ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

    // check the preselection
    if (m_preselection && !m_preselection.getBool(*evtInfo, sys))
      continue;

    // retrieve objects
    const xAOD::ElectronContainer *electrons = nullptr;
    ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
    const xAOD::MuonContainer *muons = nullptr;
    ANA_CHECK(m_muonsHandle.retrieve(muons, sys));
    const xAOD::TauJetContainer *taus = nullptr;
    ANA_CHECK(m_tausHandle.retrieve(taus, sys));
    const xAOD::JetContainer *jets = nullptr;
    ANA_CHECK(m_jetsHandle.retrieve(jets, sys));
    const xAOD::MissingETContainer *met = nullptr;
    ANA_CHECK(m_metHandle.retrieve(met, sys));

    // apply object-wise selection
    ConstDataVector<xAOD::ElectronContainer> selected_electrons(SG::VIEW_ELEMENTS);
    ConstDataVector<xAOD::MuonContainer> selected_muons(SG::VIEW_ELEMENTS);
    ConstDataVector<xAOD::TauJetContainer> selected_taus(SG::VIEW_ELEMENTS);
    ConstDataVector<xAOD::JetContainer> selected_jets(SG::VIEW_ELEMENTS);

    for (const xAOD::Electron *el : *electrons)
    {
      if (m_electronSelection.getBool(*el, sys))
        selected_electrons.push_back(el);
    }

    for (const xAOD::Muon *mu : *muons)
    {
      if (m_muonSelection.getBool(*mu, sys))
        selected_muons.push_back(mu);
    }

    for (const xAOD::TauJet *tau : *taus)
    {
      if (m_tauSelection.getBool(*tau, sys))
        selected_taus.push_back(tau);
    }

    for (const xAOD::Jet *jet : *jets)
    {
      if (m_jetSelection.getBool(*jet, sys))
        selected_jets.push_back(jet);
    }

    // count the number of jets with pT above threshold
    auto count = [&](const xAOD::Jet *jet)
    {
      return jet->pt() > m_njets_min_pt;
    };
    int nJets = std::count_if(selected_jets.begin(), selected_jets.end(), count);

    const xAOD::IParticle *vis1 = 0, *vis2 = 0;
    // to assign the visible particles on which to run the MMC, we assume that the user would prefer
    // 1) tau_had + tau_had
    // 2) tau_had + e
    // 3) tau_had + mu
    // 4) e + mu
    // 5) mu + mu
    // 6) e + e
    // To force a custom ordering, simply decorate your desired selection onto the particles before running this algorithm.
    // e.g. you could "book" an OSSF pair of light leptons as originating from a Z boson, and remove them from consideration here.

    if (selected_taus.size() >= 2)
    {
      vis1 = selected_taus.at(0);
      vis2 = selected_taus.at(1);
    }
    else if (selected_taus.size() == 1 && selected_electrons.size() >= 1)
    {
      vis1 = selected_taus.at(0);
      vis2 = selected_electrons.at(0);
    }
    else if (selected_taus.size() == 1 && selected_muons.size() >= 1)
    {
      vis1 = selected_taus.at(0);
      vis2 = selected_muons.at(0);
    }
    else if (selected_electrons.size() >= 1 && selected_muons.size() >= 1)
    {
      vis1 = selected_electrons.at(0);
      vis2 = selected_muons.at(0);
    }
    else if (selected_muons.size() >= 2)
    {
      vis1 = selected_muons.at(0);
      vis2 = selected_muons.at(1);
    }
    else if (selected_electrons.size() >= 2)
    {
      vis1 = selected_electrons.at(0);
      vis2 = selected_electrons.at(1);
    }
    else
    {
      ANA_MSG_WARNING("Not enough charged leptons in the event to run the MMC!");
    }

    ANA_CHECK(m_mmc->apply(*evtInfo, vis1, vis2, (*met)["Final"], nJets));

    // retrieve the output variables
    TLorentzVector null4V(-1, -1, -1, -1);
    int fitStatus = m_mmc->GetFitStatus(0);
    double maxw_mass = fitStatus == 1 ? m_mmc->GetFittedMass(DiTauMassTools::MMCFitMethodV2::MAXW) : -1;
    double mlm_mass = fitStatus == 1 ? m_mmc->GetFittedMass(DiTauMassTools::MMCFitMethodV2::MLM) : -1;
    double mlnu3p_mass = fitStatus == 1 ? m_mmc->GetFittedMass(DiTauMassTools::MMCFitMethodV2::MLNU3P) : -1;
    TLorentzVector mlnu3p_res_4vect = fitStatus == 1 ? m_mmc->GetResonanceVec(DiTauMassTools::MMCFitMethodV2::MLNU3P) : null4V;
    TLorentzVector mlnu3p_nu1_4vect = fitStatus == 1 ? m_mmc->GetNeutrino4vec(DiTauMassTools::MMCFitMethodV2::MLNU3P, 0) : null4V;
    TLorentzVector mlnu3p_nu2_4vect = fitStatus == 1 ? m_mmc->GetNeutrino4vec(DiTauMassTools::MMCFitMethodV2::MLNU3P, 1) : null4V;
    TLorentzVector mlnu3p_tau1_4vect = fitStatus == 1 ? m_mmc->GetTau4vec(DiTauMassTools::MMCFitMethodV2::MLNU3P, 0) : null4V;
    TLorentzVector mlnu3p_tau2_4vect = fitStatus == 1 ? m_mmc->GetTau4vec(DiTauMassTools::MMCFitMethodV2::MLNU3P, 1) : null4V;
    TLorentzVector maxw_res_4vect = fitStatus == 1 ? m_mmc->GetResonanceVec(DiTauMassTools::MMCFitMethodV2::MAXW) : null4V;
    TLorentzVector maxw_nu1_4vect = fitStatus == 1 ? m_mmc->GetNeutrino4vec(DiTauMassTools::MMCFitMethodV2::MAXW, 0) : null4V;
    TLorentzVector maxw_nu2_4vect = fitStatus == 1 ? m_mmc->GetNeutrino4vec(DiTauMassTools::MMCFitMethodV2::MAXW, 1) : null4V;
    TLorentzVector maxw_tau1_4vect = fitStatus == 1 ? m_mmc->GetTau4vec(DiTauMassTools::MMCFitMethodV2::MAXW, 0) : null4V;
    TLorentzVector maxw_tau2_4vect = fitStatus == 1 ? m_mmc->GetTau4vec(DiTauMassTools::MMCFitMethodV2::MAXW, 1) : null4V;

    // and decorate them
    m_fitStatus_decor.set(*evtInfo, fitStatus, sys);
    m_maxw_mass_decor.set(*evtInfo, maxw_mass, sys);
    m_mlm_mass_decor.set(*evtInfo, mlm_mass, sys);
    m_mlnu3p_mass_decor.set(*evtInfo, mlnu3p_mass, sys);
    m_mlnu3p_res_4vect_decor.set(*evtInfo, mlnu3p_res_4vect, sys);
    m_mlnu3p_nu1_4vect_decor.set(*evtInfo, mlnu3p_nu1_4vect, sys);
    m_mlnu3p_nu2_4vect_decor.set(*evtInfo, mlnu3p_nu2_4vect, sys);
    m_mlnu3p_tau1_4vect_decor.set(*evtInfo, mlnu3p_tau1_4vect, sys);
    m_mlnu3p_tau2_4vect_decor.set(*evtInfo, mlnu3p_tau2_4vect, sys);
    m_maxw_res_4vect_decor.set(*evtInfo, maxw_res_4vect, sys);
    m_maxw_nu1_4vect_decor.set(*evtInfo, maxw_nu1_4vect, sys);
    m_maxw_nu2_4vect_decor.set(*evtInfo, maxw_nu2_4vect, sys);
    m_maxw_tau1_4vect_decor.set(*evtInfo, maxw_tau1_4vect, sys);
    m_maxw_tau2_4vect_decor.set(*evtInfo, maxw_tau2_4vect, sys);
  }

  return StatusCode::SUCCESS;
}

StatusCode DiTauMassCalculatorAlg::finalize()
{
  ANA_CHECK(m_mmc->finalize());

  return StatusCode::SUCCESS;
}
