#include "TopPartons/CalcTthPartonHistory.h"
#include "TopPartons/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
  CalcTthPartonHistory::CalcTthPartonHistory(const std::string& name) :
    CalcTopPartonHistory(name, {"TruthTop", "TruthBoson"})
    {}
  bool CalcTthPartonHistory::HiggsAndDecay(const xAOD::TruthParticleContainer* truthParticles) {

    for (const xAOD::TruthParticle* particle : *truthParticles) {
      if (particle->pdgId() != 25 || particle->nChildren() != 2) { // choose only H->xy
        continue;
      }
      ttH.Higgs_p4 = particle->p4();

      const top::PartonHistoryUtils::HiggsDecay& higgs = top::PartonHistoryUtils::AnalyzeHiggsDecay(particle);

      ttH.decay1_p4 = higgs.decay1_vector;
      ttH.decay2_p4 = higgs.decay2_vector;
      ttH.decay1_pdgId = higgs.decay1_pdgId;
      ttH.decay2_pdgId = higgs.decay2_pdgId;
      ttH.tau_decay1_isHadronic = higgs.tau_decay1_isHadronic;
      ttH.tau_decay2_isHadronic = higgs.tau_decay2_isHadronic;
      ttH.decay1_from_decay1_p4 = higgs.decay1_from_decay1_vector;
      ttH.decay2_from_decay1_p4 = higgs.decay2_from_decay1_vector;
      ttH.decay1_from_decay1_pdgId = higgs.decay1_from_decay1_pdgId;
      ttH.decay2_from_decay1_pdgId = higgs.decay2_from_decay1_pdgId;
      ttH.decay1_from_decay2_p4 = higgs.decay1_from_decay2_vector;
      ttH.decay2_from_decay2_p4 = higgs.decay2_from_decay2_vector;
      ttH.decay1_from_decay2_pdgId = higgs.decay1_from_decay2_pdgId;
      ttH.decay2_from_decay2_pdgId = higgs.decay2_from_decay2_pdgId;
      ttH.tau_decay1_from_decay1_isHadronic = higgs.tau_decay1_from_decay1_isHadronic;
      ttH.tau_decay2_from_decay1_isHadronic = higgs.tau_decay2_from_decay1_isHadronic;
      ttH.tau_decay1_from_decay2_isHadronic = higgs.tau_decay1_from_decay2_isHadronic;
      ttH.tau_decay2_from_decay2_isHadronic = higgs.tau_decay2_from_decay2_isHadronic;

      return true;
    }
    return false;
  }

  StatusCode CalcTthPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                   xAOD::PartonHistory* tthPartonHistory) {
    tthPartonHistory->IniVarTth();

    TLorentzVector t_before, t_after, t_after_SC;
    TLorentzVector Wp;
    TLorentzVector b;
    TLorentzVector WpDecay1;
    TLorentzVector WpDecay2;
    int WpDecay1_pdgId{};
    int WpDecay2_pdgId{};

    bool event_top = CalcTopPartonHistory::topWb(truthParticles, 6, t_before, t_after, Wp, b, WpDecay1, WpDecay1_pdgId,
                                                 WpDecay2, WpDecay2_pdgId);
    bool event_top_SC = CalcTopPartonHistory::topAfterFSR_SC(truthParticles, 6, t_after_SC);

    TLorentzVector tbar_before, tbar_after, tbar_after_SC;
    TLorentzVector Wm;
    TLorentzVector bbar;
    TLorentzVector WmDecay1;
    TLorentzVector WmDecay2;
    int WmDecay1_pdgId{};
    int WmDecay2_pdgId{};

    bool event_topbar = CalcTopPartonHistory::topWb(truthParticles, -6, tbar_before, tbar_after, Wm, bbar, WmDecay1,
                                                    WmDecay1_pdgId, WmDecay2, WmDecay2_pdgId);
    bool event_topbar_SC = CalcTopPartonHistory::topAfterFSR_SC(truthParticles, -6, tbar_after_SC);


    // coming from the tHq code
    const bool event_Higgs =  CalcTthPartonHistory::HiggsAndDecay(truthParticles);

    if(event_Higgs) {
      // if our event has a higgs

      //Higgs-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs", ttH.Higgs_p4);
      fillEtaBranch(tthPartonHistory, "MC_Higgs_eta", ttH.Higgs_p4);

      //Higgs-decay1-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay1", ttH.decay1_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay1_pdgId") = ttH.decay1_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay1_isHadronic") = ttH.tau_decay1_isHadronic;
      fillEtaBranch(tthPartonHistory, "MC_Higgs_decay1_eta", ttH.decay1_p4);

      //Higgs-decay2-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay2", ttH.decay2_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay2_pdgId") = ttH.decay2_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay2_isHadronic") = ttH.tau_decay2_isHadronic;
      fillEtaBranch(tthPartonHistory, "MC_Higgs_decay2_eta", ttH.decay2_p4);

      //Higgs-decay1- from decay1-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay1_from_decay1", ttH.decay1_from_decay1_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay1_from_decay1_pdgId") = ttH.decay1_from_decay1_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay1_from_decay1_isHadronic") = ttH.tau_decay1_from_decay1_isHadronic;
      fillEtaBranch(tthPartonHistory, "MC_Higgs_decay1_from_decay1_eta", ttH.decay1_from_decay1_p4);

      //Higgs-decay2- from decay1-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay2_from_decay1", ttH.decay2_from_decay1_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay2_from_decay1_pdgId") = ttH.decay2_from_decay1_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay2_from_decay1_isHadronic") = ttH.tau_decay2_from_decay1_isHadronic;
      fillEtaBranch(tthPartonHistory, "MC_Higgs_decay2_from_decay1_eta", ttH.decay2_from_decay1_p4);

      //Higgs-decay1- from decay2-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay1_from_decay2", ttH.decay1_from_decay2_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay1_from_decay2_pdgId") = ttH.decay1_from_decay2_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay1_from_decay2_isHadronic") = ttH.tau_decay1_from_decay2_isHadronic;
      fillEtaBranch(tthPartonHistory, "MC_Higgs_decay1_from_decay2_eta", ttH.decay1_from_decay2_p4);

      //Higgs-decay2- from decay2-Variables
      decorateWithMPtPhi(tthPartonHistory,"MC_Higgs_decay2_from_decay2", ttH.decay2_from_decay2_p4);
      tthPartonHistory->auxdecor< int >("MC_Higgs_decay2_from_decay2_pdgId") = ttH.decay2_from_decay2_pdgId;
      tthPartonHistory->auxdecor< int >("MC_Higgs_tau_decay2_from_decay2_isHadronic") = ttH.tau_decay2_from_decay2_isHadronic;
        fillEtaBranch(tthPartonHistory, "MC_Higgs_decay2_from_decay2_eta", ttH.decay2_from_decay2_p4);
    }

    if (event_top && event_topbar) {
      // and we have a top and anti-top
      TLorentzVector temp = t_before + tbar_before;
      decorateWithMPtPhi(tthPartonHistory, "MC_ttbar_beforeFSR", temp);
      fillEtaBranch(tthPartonHistory, "MC_ttbar_beforeFSR_eta", temp);

      temp = t_after + tbar_after;
      decorateWithMPtPhi(tthPartonHistory, "MC_ttbar_afterFSR_beforeDecay", temp);
      fillEtaBranch(tthPartonHistory, "MC_ttbar_afterFSR_beforeDecay_eta", temp);

      temp = WmDecay1 + WmDecay2 + b + WpDecay1 + WpDecay2 + bbar;
      decorateWithMPtPhi(tthPartonHistory, "MC_ttbar_afterFSR", temp);
      fillEtaBranch(tthPartonHistory, "MC_ttbar_afterFSR_eta", temp);
    }

    // top specific
    if (event_top) {
      decorateWithMPtPhi(tthPartonHistory, "MC_t_beforeFSR", t_before);
      fillEtaBranch(tthPartonHistory, "MC_t_beforeFSR_eta", t_before);

      decorateWithMPtPhi(tthPartonHistory, "MC_t_afterFSR", t_after);
      fillEtaBranch(tthPartonHistory, "MC_t_afterFSR_eta", t_after);
      // top from status-codes specific
      if (event_top_SC) {
	decorateWithMPtPhi(tthPartonHistory, "MC_t_afterFSR_SC", t_after_SC);
	fillEtaBranch(tthPartonHistory, "MC_t_afterFSR_SC_eta", t_after_SC);
      }

      decorateWithMPtPhi(tthPartonHistory, "MC_W_from_t", Wp);
      fillEtaBranch(tthPartonHistory, "MC_W_from_t_eta", Wp);

      decorateWithMPtPhi(tthPartonHistory, "MC_b_from_t", b);
      fillEtaBranch(tthPartonHistory, "MC_b_from_t_eta", b);

      decorateWithMPtPhi(tthPartonHistory, "MC_Wdecay1_from_t", WpDecay1);
      tthPartonHistory->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = WpDecay1_pdgId;
      fillEtaBranch(tthPartonHistory, "MC_Wdecay1_from_t_eta", WpDecay1);

      decorateWithMPtPhi(tthPartonHistory, "MC_Wdecay2_from_t", WpDecay2);
      tthPartonHistory->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = WpDecay2_pdgId;
      fillEtaBranch(tthPartonHistory, "MC_Wdecay2_from_t_eta", WpDecay2);
    }

    // anti-top specific
    if (event_topbar) {
      decorateWithMPtPhi(tthPartonHistory, "MC_tbar_beforeFSR", tbar_before);
      fillEtaBranch(tthPartonHistory, "MC_tbar_beforeFSR_eta", tbar_before);

      decorateWithMPtPhi(tthPartonHistory, "MC_tbar_afterFSR", tbar_after);
      fillEtaBranch(tthPartonHistory, "MC_tbar_afterFSR_eta", tbar_after);

      // anti-top from status-codes specific
      if (event_topbar_SC) {
	decorateWithMPtPhi(tthPartonHistory, "MC_tbar_afterFSR_SC", tbar_after_SC);
	fillEtaBranch(tthPartonHistory, "MC_tbar_afterFSR_SC_eta", tbar_after_SC);
      }
        
      decorateWithMPtPhi(tthPartonHistory, "MC_W_from_tbar", Wm);
      fillEtaBranch(tthPartonHistory, "MC_W_from_tbar_eta", Wm);
        
      decorateWithMPtPhi(tthPartonHistory, "MC_b_from_tbar", bbar);
      fillEtaBranch(tthPartonHistory, "MC_b_from_tbar_eta", bbar);
        
      decorateWithMPtPhi(tthPartonHistory, "MC_Wdecay1_from_tbar", WmDecay1);
      tthPartonHistory->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = WmDecay1_pdgId;
      fillEtaBranch(tthPartonHistory, "MC_Wdecay1_from_tbar_eta", WmDecay1);
        
      decorateWithMPtPhi(tthPartonHistory, "MC_Wdecay2_from_tbar", WmDecay2);
      tthPartonHistory->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = WmDecay2_pdgId;
      fillEtaBranch(tthPartonHistory, "MC_Wdecay2_from_tbar_eta", WmDecay2);
      }

    return StatusCode::SUCCESS;
  }

}
