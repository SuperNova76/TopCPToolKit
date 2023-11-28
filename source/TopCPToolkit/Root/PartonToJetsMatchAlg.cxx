#include "TopCPToolkit/PartonToJetsMatchAlg.h"

#include "TopPartons/PartonHistory.h"

namespace top {

  PartonToJetsMatchAlg::PartonToJetsMatchAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
  {
    declareProperty("criticalDR", m_criticalDR, "Maximum delta R for matching");
    declareProperty("partonContainerName", m_partonContainerName, "Name of the parton container");
  }
  
  StatusCode PartonToJetsMatchAlg::initialize() {
    ANA_MSG_INFO("Initializing PartonToJetsMatchAlg " << name() );

    ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));
    ANA_CHECK(m_selection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    

    ANA_CHECK(m_lep_b_idx_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_had_b_idx_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_down_idx_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_up_idx_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_event_is_dilepton_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    
    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode PartonToJetsMatchAlg::execute() {
    for (const auto &sys : m_systematicsList.systematicsVector()) {
      ANA_CHECK(execute_syst(sys));
    }
    return StatusCode::SUCCESS;
  }

  StatusCode PartonToJetsMatchAlg::finalize() {
    ANA_MSG_INFO("Finalizing PartonToJetsMatchAlg");

    return StatusCode::SUCCESS;
  }
  
  StatusCode PartonToJetsMatchAlg::execute_syst(const CP::SystematicSet &sys) {
    const xAOD::EventInfo *evtInfo = nullptr;
    ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

    // default-decorate EventInfo
    m_lep_b_idx_decor.set(*evtInfo, -1, sys);
    m_had_b_idx_decor.set(*evtInfo, -1, sys);
    m_down_idx_decor.set(*evtInfo, -1, sys);
    m_up_idx_decor.set(*evtInfo, -1, sys);
    m_event_is_dilepton_decor.set(*evtInfo, 1, sys);
    
    if (m_selection && !m_selection.getBool(*evtInfo, sys))
      return StatusCode::SUCCESS;
    
    const xAOD::JetContainer *jets = nullptr;
    ANA_CHECK(m_jetsHandle.retrieve(jets, sys));

    ConstDataVector<xAOD::JetContainer> selected_jets(SG::VIEW_ELEMENTS);
    for (const xAOD::Jet *jet : *jets) {
      if (m_jetSelection.getBool(*jet, sys))
        selected_jets.push_back(jet);
    }
    
    const xAOD::PartonHistory* topParton = nullptr;
    ANA_CHECK(evtStore()->retrieve(topParton, m_partonContainerName));

    int b_had_index(-1);
    int b_lep_index(-1);
    int up_index(-1);
    int down_index(-1);
    bool isDilepton(false);

    float MC_Wdecay1_from_t_pt = 0;
    float MC_Wdecay1_from_t_eta = 0;
    float MC_Wdecay1_from_t_phi = 0;
    float MC_Wdecay1_from_t_m = 0;
    int   MC_Wdecay1_from_t_pdgId = 0;
    float MC_Wdecay2_from_t_pt = 0;
    float MC_Wdecay2_from_t_eta = 0;
    float MC_Wdecay2_from_t_phi = 0;
    float MC_Wdecay2_from_t_m = 0;
    int   MC_Wdecay2_from_t_pdgId = 0;
    float MC_Wdecay1_from_tbar_pt = 0;
    float MC_Wdecay1_from_tbar_eta = 0;
    float MC_Wdecay1_from_tbar_phi = 0;
    float MC_Wdecay1_from_tbar_m = 0;
    int   MC_Wdecay1_from_tbar_pdgId = 0;
    float MC_Wdecay2_from_tbar_pt = 0;
    float MC_Wdecay2_from_tbar_eta = 0;
    float MC_Wdecay2_from_tbar_phi = 0;
    float MC_Wdecay2_from_tbar_m = 0;
    int   MC_Wdecay2_from_tbar_pdgId = 0;
    float MC_b_from_t_pt = 0;
    float MC_b_from_t_eta = 0;
    float MC_b_from_t_phi = 0;
    float MC_b_from_t_m = 0;
    float MC_b_from_tbar_pt = 0;
    float MC_b_from_tbar_eta = 0;
    float MC_b_from_tbar_phi = 0;
    float MC_b_from_tbar_m = 0;
  
    if(topParton->auxdata<float>("MC_Wdecay1_from_t_pt") > 0) {
      MC_Wdecay1_from_t_pt    = topParton->auxdata<float>("MC_Wdecay1_from_t_pt");
      MC_Wdecay1_from_t_eta   = topParton->auxdata<float>("MC_Wdecay1_from_t_eta");
      MC_Wdecay1_from_t_phi   = topParton->auxdata<float>("MC_Wdecay1_from_t_phi");
      MC_Wdecay1_from_t_m     = topParton->auxdata<float>("MC_Wdecay1_from_t_m");
      MC_Wdecay1_from_t_pdgId = topParton->auxdata<int>("MC_Wdecay1_from_t_pdgId");
    } else {
      // something is wrong with the truth information
      return StatusCode::SUCCESS;
    }
  
    if(topParton->auxdata<float>("MC_Wdecay2_from_t_pt") > 0) {
      MC_Wdecay2_from_t_pt    = topParton->auxdata<float>("MC_Wdecay2_from_t_pt");
      MC_Wdecay2_from_t_eta   = topParton->auxdata<float>("MC_Wdecay2_from_t_eta");
      MC_Wdecay2_from_t_phi   = topParton->auxdata<float>("MC_Wdecay2_from_t_phi");
      MC_Wdecay2_from_t_m     = topParton->auxdata<float>("MC_Wdecay2_from_t_m");
      MC_Wdecay2_from_t_pdgId = topParton->auxdata<int>("MC_Wdecay2_from_t_pdgId");
    } else {
      // something is wrong with the truth information
      return StatusCode::SUCCESS;
    }
  
    if(topParton->auxdata<float>("MC_Wdecay1_from_tbar_pt") > 0) {
      MC_Wdecay1_from_tbar_pt    = topParton->auxdata<float>("MC_Wdecay1_from_tbar_pt");
      MC_Wdecay1_from_tbar_eta   = topParton->auxdata<float>("MC_Wdecay1_from_tbar_eta");
      MC_Wdecay1_from_tbar_phi   = topParton->auxdata<float>("MC_Wdecay1_from_tbar_phi");
      MC_Wdecay1_from_tbar_m     = topParton->auxdata<float>("MC_Wdecay1_from_tbar_m");
      MC_Wdecay1_from_tbar_pdgId = topParton->auxdata<int>("MC_Wdecay1_from_tbar_pdgId");
    } else {
      // something is wrong with the truth information
      return StatusCode::SUCCESS;
    }
  
    if(topParton->auxdata<float>("MC_Wdecay2_from_tbar_pt") > 0) {
      MC_Wdecay2_from_tbar_pt    = topParton->auxdata<float>("MC_Wdecay2_from_tbar_pt");
      MC_Wdecay2_from_tbar_eta   = topParton->auxdata<float>("MC_Wdecay2_from_tbar_eta");
      MC_Wdecay2_from_tbar_phi   = topParton->auxdata<float>("MC_Wdecay2_from_tbar_phi");
      MC_Wdecay2_from_tbar_m     = topParton->auxdata<float>("MC_Wdecay2_from_tbar_m");
      MC_Wdecay2_from_tbar_pdgId = topParton->auxdata<int>("MC_Wdecay2_from_tbar_pdgId");
    } else {
      // something is wrong with the truth information
      return StatusCode::SUCCESS;
    }
    if(topParton->auxdata<float>("MC_b_from_t_pt") > 0) {
      MC_b_from_t_pt    = topParton->auxdata<float>("MC_b_from_t_pt");
      MC_b_from_t_eta   = topParton->auxdata<float>("MC_b_from_t_eta");
      MC_b_from_t_phi   = topParton->auxdata<float>("MC_b_from_t_phi");
      MC_b_from_t_m     = topParton->auxdata<float>("MC_b_from_t_m");
    } else {
      return StatusCode::SUCCESS;
    }
  
    if(topParton->auxdata<float>("MC_b_from_t_pt") > 0) {
      MC_b_from_tbar_pt    = topParton->auxdata<float>("MC_b_from_tbar_pt");
      MC_b_from_tbar_eta   = topParton->auxdata<float>("MC_b_from_tbar_eta");
      MC_b_from_tbar_phi   = topParton->auxdata<float>("MC_b_from_tbar_phi");
      MC_b_from_tbar_m     = topParton->auxdata<float>("MC_b_from_tbar_m");
    } else {
      return StatusCode::SUCCESS;
    }
  
    // the parton truth information should be correct here
    bool t_isHadronic(false);
    bool tbar_isHadronic(false);
  
    // if top has a hadronic decay of W
    if (((std::abs(MC_Wdecay1_from_t_pdgId) > 0) && (std::abs(MC_Wdecay1_from_t_pdgId) < 6)) || ((std::abs(MC_Wdecay2_from_t_pdgId) > 0) && (std::abs(MC_Wdecay2_from_t_pdgId) < 6)) ) t_isHadronic = true;
    if (((std::abs(MC_Wdecay1_from_tbar_pdgId) > 0) && (std::abs(MC_Wdecay1_from_tbar_pdgId) < 6)) || ((std::abs(MC_Wdecay2_from_tbar_pdgId) > 0) && (std::abs(MC_Wdecay2_from_tbar_pdgId) < 6)) ) tbar_isHadronic = true;
  
    if (!t_isHadronic && !tbar_isHadronic) isDilepton = true;
    else isDilepton = false;
  
    if (isDilepton) {
      return StatusCode::SUCCESS;
    }

    TLorentzVector W_quark_up, W_quark_down, b_had, b_lep;
  
    if (t_isHadronic) {
      b_had.SetPtEtaPhiM(MC_b_from_t_pt, MC_b_from_t_eta, MC_b_from_t_phi, MC_b_from_t_m);
      b_lep.SetPtEtaPhiM(MC_b_from_tbar_pt, MC_b_from_tbar_eta, MC_b_from_tbar_phi, MC_b_from_tbar_m);
      if (std::abs(MC_Wdecay1_from_t_pdgId) == 2 || std::abs(MC_Wdecay1_from_t_pdgId) == 4) {
        W_quark_up  .SetPtEtaPhiM(MC_Wdecay1_from_t_pt, MC_Wdecay1_from_t_eta, MC_Wdecay1_from_t_phi, MC_Wdecay1_from_t_m);
        W_quark_down.SetPtEtaPhiM(MC_Wdecay2_from_t_pt, MC_Wdecay2_from_t_eta, MC_Wdecay2_from_t_phi, MC_Wdecay2_from_t_m);
      } else {
        W_quark_down.SetPtEtaPhiM(MC_Wdecay1_from_t_pt, MC_Wdecay1_from_t_eta, MC_Wdecay1_from_t_phi, MC_Wdecay1_from_t_m);
        W_quark_up  .SetPtEtaPhiM(MC_Wdecay2_from_t_pt, MC_Wdecay2_from_t_eta, MC_Wdecay2_from_t_phi, MC_Wdecay2_from_t_m);
      }
  
    } else {
      b_lep.SetPtEtaPhiM(MC_b_from_t_pt, MC_b_from_t_eta, MC_b_from_t_phi, MC_b_from_t_m);
      b_had.SetPtEtaPhiM(MC_b_from_tbar_pt, MC_b_from_tbar_eta, MC_b_from_tbar_phi, MC_b_from_tbar_m);
      if (std::abs(MC_Wdecay1_from_tbar_pdgId) == 2 || std::abs(MC_Wdecay1_from_tbar_pdgId) == 4) {
        W_quark_up  .SetPtEtaPhiM(MC_Wdecay1_from_tbar_pt, MC_Wdecay1_from_tbar_eta, MC_Wdecay1_from_tbar_phi, MC_Wdecay1_from_tbar_m);
        W_quark_down.SetPtEtaPhiM(MC_Wdecay2_from_tbar_pt, MC_Wdecay2_from_tbar_eta, MC_Wdecay2_from_tbar_phi, MC_Wdecay2_from_tbar_m);
      } else {
        W_quark_down.SetPtEtaPhiM(MC_Wdecay1_from_tbar_pt, MC_Wdecay1_from_tbar_eta, MC_Wdecay1_from_tbar_phi, MC_Wdecay1_from_tbar_m);
        W_quark_up  .SetPtEtaPhiM(MC_Wdecay2_from_tbar_pt, MC_Wdecay2_from_tbar_eta, MC_Wdecay2_from_tbar_phi, MC_Wdecay2_from_tbar_m);
      }
    }

    float minDR_up = 9999;
    float minDR_down = 9999;
    float minDR_bhad = 9999;
    float minDR_blep = 9999;
    // loop over truth jets and try to identify
    for (std::size_t ijet = 0; ijet < selected_jets.size(); ++ijet) {
      TLorentzVector truth_jet;
      truth_jet.SetPtEtaPhiE(selected_jets.at(ijet)->pt(), selected_jets.at(ijet)->eta(), selected_jets.at(ijet)->phi(), selected_jets.at(ijet)->e());
  
      if (truth_jet.DeltaR(W_quark_up) < minDR_up) {
        minDR_up = truth_jet.DeltaR(W_quark_up);
        up_index = ijet;
      }
      if (truth_jet.DeltaR(W_quark_down) < minDR_down) {
        minDR_down = truth_jet.DeltaR(W_quark_down);
        down_index = ijet;
      }
      if (truth_jet.DeltaR(b_had) < minDR_bhad) {
        minDR_bhad = truth_jet.DeltaR(b_had);
        b_had_index = ijet;
      }
      if (truth_jet.DeltaR(b_lep) < minDR_blep) {
        minDR_blep = truth_jet.DeltaR(b_lep);
        b_lep_index = ijet;
      }
    }
  
    if (up_index == down_index) {
      up_index = -1;
      down_index = -1;
    }
    if (up_index == b_had_index) {
      up_index = -1;
      b_had_index = -1;
    }
    if (up_index == b_lep_index) {
      up_index = -1;
      b_lep_index = -1;
    }
    if (down_index == b_lep_index) {
      down_index = -1;
      b_lep_index = -1;
    }
    if (down_index == b_had_index) {
      down_index = -1;
      b_had_index = -1;
    }
    if (b_lep_index == b_had_index) {
      b_lep_index = -1;
      b_had_index = -1;
    }
  
    // check the DR
    if (minDR_up   > m_criticalDR) up_index = -1;
    if (minDR_down > m_criticalDR) down_index = -1;
    if (minDR_bhad > m_criticalDR) b_had_index = -1;
    if (minDR_blep > m_criticalDR) b_lep_index = -1;

    m_lep_b_idx_decor.set(*evtInfo, b_lep_index, sys);
    m_had_b_idx_decor.set(*evtInfo, b_had_index, sys);
    m_down_idx_decor.set(*evtInfo, up_index, sys);
    m_up_idx_decor.set(*evtInfo, down_index, sys);
    m_event_is_dilepton_decor.set(*evtInfo, 0, sys);
    
    return StatusCode::SUCCESS;
  }
}
