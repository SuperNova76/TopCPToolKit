#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  void CalcPartonHistory::FillTopPartonHistory(xAOD::PartonHistory* PartonHistory) {
    // Filling the parton history for a top quark.
    // Fill the W+ parton history and assign the "t" as parent
    FillWpPartonHistory(PartonHistory, "t");
    // Fill the b parton history and assign the "t" as parent
    FillBottomPartonHistory(PartonHistory, "t");

    TLorentzVector t_beforeFSR, t_afterFSR;

    static const SG::AuxElement::Decorator<float> dec_MC_t_beforeFSR_m("MC_t_beforeFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_t_beforeFSR_pt("MC_t_beforeFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_t_beforeFSR_eta("MC_t_beforeFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_t_beforeFSR_phi("MC_t_beforeFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_t_afterFSR_m("MC_t_afterFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_t_afterFSR_pt("MC_t_afterFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_t_afterFSR_eta("MC_t_afterFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_t_afterFSR_phi("MC_t_afterFSR_phi");

    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_t_beforeFSR_m, dec_MC_t_beforeFSR_pt, dec_MC_t_beforeFSR_eta, dec_MC_t_beforeFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_t_afterFSR_m, dec_MC_t_afterFSR_pt, dec_MC_t_afterFSR_eta, dec_MC_t_afterFSR_phi, PartonHistory);

    if (Retrievep4("MC_t_beforeFSR", t_beforeFSR)) {
      // As this is a always a top we don't set the pdgId
      FillParticleInfo(dec_MC_t_beforeFSR_m, dec_MC_t_beforeFSR_pt, dec_MC_t_beforeFSR_eta, dec_MC_t_beforeFSR_phi, t_beforeFSR, PartonHistory);
    }
    if (Retrievep4("MC_t_afterFSR", t_afterFSR)) {
      // As this is a always a top we don't set the pdgId
      FillParticleInfo(dec_MC_t_afterFSR_m, dec_MC_t_afterFSR_pt, dec_MC_t_afterFSR_eta, dec_MC_t_afterFSR_phi, t_afterFSR, PartonHistory);
    }
  }

  void CalcPartonHistory::FillAntiTopPartonHistory(xAOD::PartonHistory* PartonHistory) {
    // Filling the parton history for an anti-top quark.
    // Fill the W- parton history and assign the "tbar" as parent
    FillWmPartonHistory(PartonHistory, "tbar");
    // Fill the bbar parton history and assign the "tbar" as parent
    FillAntiBottomPartonHistory(PartonHistory, "tbar");

    TLorentzVector tbar_beforeFSR, tbar_afterFSR;

    static const SG::AuxElement::Decorator<float> dec_MC_tbar_beforeFSR_m("MC_tbar_beforeFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_beforeFSR_pt("MC_tbar_beforeFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_beforeFSR_eta("MC_tbar_beforeFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_beforeFSR_phi("MC_tbar_beforeFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_tbar_afterFSR_m("MC_tbar_afterFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_afterFSR_pt("MC_tbar_afterFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_afterFSR_eta("MC_tbar_afterFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_tbar_afterFSR_phi("MC_tbar_afterFSR_phi");

    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_tbar_beforeFSR_m, dec_MC_tbar_beforeFSR_pt, dec_MC_tbar_beforeFSR_eta, dec_MC_tbar_beforeFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_tbar_afterFSR_m, dec_MC_tbar_afterFSR_pt, dec_MC_tbar_afterFSR_eta, dec_MC_tbar_afterFSR_phi, PartonHistory);

    if (Retrievep4("MC_t_beforeFSR", tbar_beforeFSR)) {
      // As this is a always an anti-top we don't set the pdgId
      FillParticleInfo(dec_MC_tbar_beforeFSR_m, dec_MC_tbar_beforeFSR_pt, dec_MC_tbar_beforeFSR_eta, dec_MC_tbar_beforeFSR_phi, tbar_beforeFSR, PartonHistory);
    }
    if (Retrievep4("MC_t_afterFSR", tbar_afterFSR)) {
      // As this is a always an anti-top we don't set the pdgId
      FillParticleInfo(dec_MC_tbar_afterFSR_m, dec_MC_tbar_afterFSR_pt, dec_MC_tbar_afterFSR_eta, dec_MC_tbar_afterFSR_phi, tbar_afterFSR, PartonHistory);
    }
  }

  void CalcPartonHistory::FillTtbarPartonHistory(xAOD::PartonHistory* PartonHistory) {
    // Filling the ttbar parton history
    TLorentzVector ttbar;

    TLorentzVector t_beforeFSR, tbar_beforeFSR;
    TLorentzVector t_afterFSR, tbar_afterFSR;

    TLorentzVector WpDecay1, WpDecay2;
    TLorentzVector WmDecay1, WmDecay2;

    int WpDecay1_pdgId, WpDecay2_pdgId;
    int WmDecay1_pdgId, WmDecay2_pdgId;

    TLorentzVector b, bbar;

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_m("MC_ttbar_beforeFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_pt("MC_ttbar_beforeFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_eta("MC_ttbar_beforeFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_phi("MC_ttbar_beforeFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_beforeDecay_m("MC_ttbar_afterFSR_beforeDecay_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_beforeDecay_pt("MC_ttbar_afterFSR_beforeDecay_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_beforeDecay_eta("MC_ttbar_afterFSR_beforeDecay_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_beforeDecay_phi("MC_ttbar_afterFSR_beforeDecay_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_m("MC_ttbar_afterFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_pt("MC_ttbar_afterFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_eta("MC_ttbar_afterFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_phi("MC_ttbar_afterFSR_phi");

    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_ttbar_beforeFSR_m, dec_MC_ttbar_beforeFSR_pt, dec_MC_ttbar_beforeFSR_eta, dec_MC_ttbar_beforeFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_ttbar_afterFSR_beforeDecay_m, dec_MC_ttbar_afterFSR_beforeDecay_pt, dec_MC_ttbar_afterFSR_beforeDecay_eta, dec_MC_ttbar_afterFSR_beforeDecay_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_ttbar_afterFSR_m, dec_MC_ttbar_afterFSR_pt, dec_MC_ttbar_afterFSR_eta, dec_MC_ttbar_afterFSR_phi, PartonHistory);

    if (Retrievep4("MC_t_beforeFSR", t_beforeFSR)
	&& Retrievep4("MC_tbar_beforeFSR", tbar_beforeFSR)) {
      ttbar = t_beforeFSR + tbar_beforeFSR;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_beforeFSR_m, dec_MC_ttbar_beforeFSR_pt, dec_MC_ttbar_beforeFSR_eta, dec_MC_ttbar_beforeFSR_phi, ttbar, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_t_WpDecay1", WpDecay1, WpDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WpDecay2", WpDecay2, WpDecay2_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay1", WmDecay1, WmDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay2", WmDecay2, WmDecay2_pdgId)
	&& Retrievep4("MC_t_b", b)
	&& Retrievep4("MC_t_bbar", bbar)) {
      ttbar = WpDecay1 + WpDecay2 + WmDecay1 + WmDecay2 + b + bbar;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_afterFSR_beforeDecay_m, dec_MC_ttbar_afterFSR_beforeDecay_pt, dec_MC_ttbar_afterFSR_beforeDecay_eta, dec_MC_ttbar_afterFSR_beforeDecay_phi, ttbar, PartonHistory);
    }

    if (Retrievep4("MC_t_afterFSR", t_afterFSR)
	&& Retrievep4("MC_tbar_afterFSR", tbar_afterFSR)) {
      ttbar = t_afterFSR + tbar_afterFSR;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_afterFSR_m, dec_MC_ttbar_afterFSR_pt, dec_MC_ttbar_afterFSR_eta, dec_MC_ttbar_afterFSR_phi, ttbar, PartonHistory);
    }
  }
} // namespace top
