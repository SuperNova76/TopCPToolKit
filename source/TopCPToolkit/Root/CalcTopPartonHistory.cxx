#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillTopPartonHistory(xAOD::PartonHistory* PartonHistory, const int& mode) {
    if (mode == 0 || mode == 2) { // 0 == t, 2 == flavour agnostic
      // Filling the parton history for a top quark.
      // Fill the W+ parton history and assign the "t" as parent
      FillWPartonHistory(PartonHistory, "t", mode);
      // Fill the b parton history and assign the "t" as parent
      FillBottomPartonHistory(PartonHistory, "t", mode);
      // Decorators for top (t)
      static const SG::AuxElement::Decorator<float> dec_t_beforeFSR_m("MC_t_beforeFSR_m");
      static const SG::AuxElement::Decorator<float> dec_t_beforeFSR_pt("MC_t_beforeFSR_pt");
      static const SG::AuxElement::Decorator<float> dec_t_beforeFSR_eta("MC_t_beforeFSR_eta");
      static const SG::AuxElement::Decorator<float> dec_t_beforeFSR_phi("MC_t_beforeFSR_phi");

      static const SG::AuxElement::Decorator<float> dec_t_afterFSR_m("MC_t_afterFSR_m");
      static const SG::AuxElement::Decorator<float> dec_t_afterFSR_pt("MC_t_afterFSR_pt");
      static const SG::AuxElement::Decorator<float> dec_t_afterFSR_eta("MC_t_afterFSR_eta");
      static const SG::AuxElement::Decorator<float> dec_t_afterFSR_phi("MC_t_afterFSR_phi");
      
      static const SG::AuxElement::Decorator<int> dec_t_pdgId("MC_t_pdgId");

      PtEtaPhiMVector t_beforeFSR;
      PtEtaPhiMVector t_afterFSR;
      int t_pdgId = -1;

      // Decorate with defaults for top
      FillDefaultParticleInfo(dec_t_beforeFSR_m, dec_t_beforeFSR_pt, dec_t_beforeFSR_eta, dec_t_beforeFSR_phi, PartonHistory);
      FillDefaultParticleInfo(dec_t_afterFSR_m, dec_t_afterFSR_pt, dec_t_afterFSR_eta, dec_t_afterFSR_phi, PartonHistory);

      // Note because we could be flavour agnostic we also save the pdgId
      if (RetrieveParticleInfo("MC_t_beforeFSR", t_beforeFSR, t_pdgId)) {
	FillParticleInfo(dec_t_beforeFSR_m, dec_t_beforeFSR_pt, dec_t_beforeFSR_eta, dec_t_beforeFSR_phi, dec_t_pdgId, t_beforeFSR, t_pdgId, PartonHistory);
      }
      else if (mode == 2 && RetrieveParticleInfo("MC_tbar_beforeFSR", t_beforeFSR, t_pdgId)) {
	// Note that we save tbar into t because we are flavour agnostic!
	FillParticleInfo(dec_t_beforeFSR_m, dec_t_beforeFSR_pt, dec_t_beforeFSR_eta, dec_t_beforeFSR_phi, dec_t_pdgId, t_beforeFSR, t_pdgId, PartonHistory);
      }
      // We don't need to fill the pdgId again here
      if (Retrievep4("MC_t_afterFSR", t_afterFSR)) {
	FillParticleInfo(dec_t_afterFSR_m, dec_t_afterFSR_pt, dec_t_afterFSR_eta, dec_t_afterFSR_phi, t_afterFSR, PartonHistory);
      }
      // Unless we are flavour agnostic, then we need to fill it
      else if (mode == 2 && RetrieveParticleInfo("MC_tbar_afterFSR", t_afterFSR, t_pdgId)) {
	// Note that we save tbar into t because we are flavour agnostic!
	FillParticleInfo(dec_t_afterFSR_m, dec_t_afterFSR_pt, dec_t_afterFSR_eta, dec_t_afterFSR_phi, dec_t_pdgId, t_afterFSR, t_pdgId, PartonHistory);
      }
    }
    if (mode == 1) { // 1 == tbar
      // Filling the parton history for an anti-top quark.
      // Fill the W- parton history and assign the "tbar" as parent
      FillWPartonHistory(PartonHistory, "tbar", mode);
      // Fill the bbar parton history and assign the "tbar" as parent
      FillBottomPartonHistory(PartonHistory, "tbar", mode);
      // Decorators for anti-top (tbar)
      static const SG::AuxElement::Decorator<float> dec_tbar_beforeFSR_m("MC_tbar_beforeFSR_m");
      static const SG::AuxElement::Decorator<float> dec_tbar_beforeFSR_pt("MC_tbar_beforeFSR_pt");
      static const SG::AuxElement::Decorator<float> dec_tbar_beforeFSR_eta("MC_tbar_beforeFSR_eta");
      static const SG::AuxElement::Decorator<float> dec_tbar_beforeFSR_phi("MC_tbar_beforeFSR_phi");

      static const SG::AuxElement::Decorator<float> dec_tbar_afterFSR_m("MC_tbar_afterFSR_m");
      static const SG::AuxElement::Decorator<float> dec_tbar_afterFSR_pt("MC_tbar_afterFSR_pt");
      static const SG::AuxElement::Decorator<float> dec_tbar_afterFSR_eta("MC_tbar_afterFSR_eta");
      static const SG::AuxElement::Decorator<float> dec_tbar_afterFSR_phi("MC_tbar_afterFSR_phi");

      static const SG::AuxElement::Decorator<int> dec_tbar_pdgId("MC_tbar_pdgId");

      PtEtaPhiMVector tbar_beforeFSR;
      PtEtaPhiMVector tbar_afterFSR;
      int tbar_pdgId = -1;

      // Decorate with defaults for anti-top
      FillDefaultParticleInfo(dec_tbar_beforeFSR_m, dec_tbar_beforeFSR_pt, dec_tbar_beforeFSR_eta, dec_tbar_beforeFSR_phi, PartonHistory);
      FillDefaultParticleInfo(dec_tbar_afterFSR_m, dec_tbar_afterFSR_pt, dec_tbar_afterFSR_eta, dec_tbar_afterFSR_phi, PartonHistory);

      if (RetrieveParticleInfo("MC_tbar_beforeFSR", tbar_beforeFSR, tbar_pdgId)) {
	FillParticleInfo(dec_tbar_beforeFSR_m, dec_tbar_beforeFSR_pt, dec_tbar_beforeFSR_eta, dec_tbar_beforeFSR_phi, dec_tbar_pdgId, tbar_beforeFSR, tbar_pdgId, PartonHistory);
      }
      // We don't need to fill the pdgId again
      if (Retrievep4("MC_tbar_afterFSR", tbar_afterFSR)) {
	FillParticleInfo(dec_tbar_afterFSR_m, dec_tbar_afterFSR_pt, dec_tbar_afterFSR_eta, dec_tbar_afterFSR_phi, tbar_afterFSR, PartonHistory);
      }
    }
  }

  void CalcPartonHistory::FillTtbarPartonHistory(xAOD::PartonHistory* PartonHistory) {
    // assuming t and tbar partonhistory ran already
    PtEtaPhiMVector ttbar;

    PtEtaPhiMVector t_beforeFSR;
    PtEtaPhiMVector tbar_beforeFSR;
    PtEtaPhiMVector t_afterFSR;
    PtEtaPhiMVector tbar_afterFSR;

    PtEtaPhiMVector WpDecay1, WpDecay2;
    PtEtaPhiMVector WmDecay1, WmDecay2;

    int WpDecay1_pdgId, WpDecay2_pdgId, WmDecay1_pdgId, WmDecay2_pdgId;

    PtEtaPhiMVector b, bbar;

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_m("MC_ttbar_beforeFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_pt("MC_ttbar_beforeFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_eta("MC_ttbar_beforeFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_beforeFSR_phi("MC_ttbar_beforeFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_m("MC_ttbar_afterFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_pt("MC_ttbar_afterFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_eta("MC_ttbar_afterFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_afterFSR_phi("MC_ttbar_afterFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_beforeFSR_m("MC_ttbar_fromDecay_beforeFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_beforeFSR_pt("MC_ttbar_fromDecay_beforeFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_beforeFSR_eta("MC_ttbar_fromDecay_beforeFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_beforeFSR_phi("MC_ttbar_fromDecay_beforeFSR_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_afterFSR_m("MC_ttbar_fromDecay_afterFSR_m");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_afterFSR_pt("MC_ttbar_fromDecay_afterFSR_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_afterFSR_eta("MC_ttbar_fromDecay_afterFSR_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_ttbar_fromDecay_afterFSR_phi("MC_ttbar_fromDecay_afterFSR_phi");

    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_ttbar_beforeFSR_m, dec_MC_ttbar_beforeFSR_pt, dec_MC_ttbar_beforeFSR_eta, dec_MC_ttbar_beforeFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_ttbar_afterFSR_m, dec_MC_ttbar_afterFSR_pt, dec_MC_ttbar_afterFSR_eta, dec_MC_ttbar_afterFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_ttbar_fromDecay_beforeFSR_m, dec_MC_ttbar_fromDecay_beforeFSR_pt, dec_MC_ttbar_fromDecay_beforeFSR_eta, dec_MC_ttbar_fromDecay_beforeFSR_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_ttbar_fromDecay_afterFSR_m, dec_MC_ttbar_fromDecay_afterFSR_pt, dec_MC_ttbar_fromDecay_afterFSR_eta, dec_MC_ttbar_fromDecay_afterFSR_phi, PartonHistory);

    if (Retrievep4("MC_t_beforeFSR", t_beforeFSR)
	&& Retrievep4("MC_tbar_beforeFSR", tbar_beforeFSR)) {
      ttbar = t_beforeFSR + tbar_beforeFSR;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_beforeFSR_m, dec_MC_ttbar_beforeFSR_pt, dec_MC_ttbar_beforeFSR_eta, dec_MC_ttbar_beforeFSR_phi, ttbar, PartonHistory);
    }

    if (Retrievep4("MC_t_afterFSR", t_afterFSR)
	&& Retrievep4("MC_tbar_afterFSR", tbar_afterFSR)) {
      ttbar = t_afterFSR + tbar_afterFSR;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_afterFSR_m, dec_MC_ttbar_afterFSR_pt, dec_MC_ttbar_afterFSR_eta, dec_MC_ttbar_afterFSR_phi, ttbar, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_t_WpDecay1", WpDecay1, WpDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WpDecay2", WpDecay2, WpDecay2_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay1", WmDecay1, WmDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay2", WmDecay2, WmDecay2_pdgId)
	&& Retrievep4("MC_t_b_beforeFSR", b)
	&& Retrievep4("MC_tbar_bbar_beforeFSR", bbar)) {
      ttbar = WpDecay1 + WpDecay2 + WmDecay1 + WmDecay2 + b + bbar;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_fromDecay_beforeFSR_m, dec_MC_ttbar_fromDecay_beforeFSR_pt, dec_MC_ttbar_fromDecay_beforeFSR_eta, dec_MC_ttbar_fromDecay_beforeFSR_phi, ttbar, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_t_WpDecay1", WpDecay1, WpDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WpDecay2", WpDecay2, WpDecay2_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay1", WmDecay1, WmDecay1_pdgId)
	&& RetrieveParticleInfo("MC_t_WmDecay2", WmDecay2, WmDecay2_pdgId)
	&& Retrievep4("MC_t_b_afterFSR", b)
	&& Retrievep4("MC_tbar_bbar_afterFSR", bbar)) {
      ttbar = WpDecay1 + WpDecay2 + WmDecay1 + WmDecay2 + b + bbar;
      // Since this is ttbar we don't set a pdgId
      FillParticleInfo(dec_MC_ttbar_fromDecay_afterFSR_m, dec_MC_ttbar_fromDecay_afterFSR_pt, dec_MC_ttbar_fromDecay_afterFSR_eta, dec_MC_ttbar_fromDecay_afterFSR_phi, ttbar, PartonHistory);
    }
  }
} // namespace top
