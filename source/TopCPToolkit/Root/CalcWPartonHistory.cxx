#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillWPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent, const int& mode) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    if (mode == 0 || mode == 2) { // 0 == W+, 2 == flavour agnostic
      PtEtaPhiMVector Wp;
      PtEtaPhiMVector WpDecay1, WpDecay2;
      int WpDecay1pdgId = -1;
      int WpDecay2pdgId = -1;
      int WppdgId = -1;

      std::string prefix = "MC_" + ((parent != "") ? parent + "_Wp" : "Wp");

      static const SG::AuxElement::Decorator<float> dec_MC_Wp_m("MC_W" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wp_pt("MC_W" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wp_eta("MC_W" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wp_phi("MC_W" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wp_pdgId("MC_W" + parentstring +"_pdgId");

      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_m("MC_Wdecay1" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_pt("MC_Wdecay1" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_eta("MC_Wdecay1" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_phi("MC_Wdecay1" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wpdecay1_pdgId("MC_Wdecay1" + parentstring + "_pdgId");

      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_m("MC_Wdecay2" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_pt("MC_Wdecay2" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_eta("MC_Wdecay2" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_phi("MC_Wdecay2" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wpdecay2_pdgId("MC_Wdecay2" + parentstring + "_pdgId");

      // Decorating with defaults in case the particle doesn't exist
      FillDefaultParticleInfo(dec_MC_Wp_m, dec_MC_Wp_pt, dec_MC_Wp_eta, dec_MC_Wp_phi, PartonHistory);
      FillDefaultParticleInfo(dec_MC_Wpdecay1_m, dec_MC_Wpdecay1_pt, dec_MC_Wpdecay1_eta, dec_MC_Wpdecay1_phi, dec_MC_Wpdecay1_pdgId, PartonHistory);
      FillDefaultParticleInfo(dec_MC_Wpdecay2_m, dec_MC_Wpdecay2_pt, dec_MC_Wpdecay2_eta, dec_MC_Wpdecay2_phi, dec_MC_Wpdecay2_pdgId, PartonHistory);

      if (RetrieveParticleInfo(prefix + "_beforeFSR", Wp, WppdgId)) {
	FillParticleInfo(dec_MC_Wp_m, dec_MC_Wp_pt, dec_MC_Wp_eta, dec_MC_Wp_phi, dec_MC_Wp_pdgId, Wp, WppdgId, PartonHistory);
      }
      else {
	// first we have to adapt the prefix! Currently the parent can only be a top so there we just need to add "bar"
	prefix = "MC_" + ((parent != "") ? parent + "bar_Wm" : "Wm");
	if (mode == 2 && RetrieveParticleInfo(prefix + "_beforeFSR", Wp, WppdgId)) {
	  // Note that we save Wm information from the particle map into the Wp PtEtaPhiMVector because we are flavour agnostic!
	  FillParticleInfo(dec_MC_Wp_m, dec_MC_Wp_pt, dec_MC_Wp_eta, dec_MC_Wp_phi, dec_MC_Wp_pdgId, Wp, WppdgId, PartonHistory);
	}
      }
      if (RetrieveParticleInfo(prefix + "Decay1", WpDecay1, WpDecay1pdgId)) {
	FillParticleInfo(dec_MC_Wpdecay1_m, dec_MC_Wpdecay1_pt, dec_MC_Wpdecay1_eta, dec_MC_Wpdecay1_phi, dec_MC_Wpdecay1_pdgId, WpDecay1, WpDecay1pdgId, PartonHistory);
      }
      else {
	// first we have to adapt the prefix! Currently the parent can only be a top so there we just need to add "bar"
	prefix = "MC_" + ((parent != "") ? parent + "bar_Wm" : "Wm");
	if (mode == 2 && RetrieveParticleInfo(prefix + "Decay1", WpDecay1, WpDecay1pdgId)) {
	  // Note that we save Wm information from the particle map into the Wp PtEtaPhiMVector because we are flavour agnostic!
	  FillParticleInfo(dec_MC_Wpdecay1_m, dec_MC_Wpdecay1_pt, dec_MC_Wpdecay1_eta, dec_MC_Wpdecay1_phi, dec_MC_Wpdecay1_pdgId, WpDecay1, WpDecay1pdgId, PartonHistory);
	}
      }
      if (RetrieveParticleInfo(prefix + "Decay2", WpDecay2, WpDecay2pdgId)) {
	FillParticleInfo(dec_MC_Wpdecay2_m, dec_MC_Wpdecay2_pt, dec_MC_Wpdecay2_eta, dec_MC_Wpdecay2_phi, dec_MC_Wpdecay2_pdgId, WpDecay2, WpDecay2pdgId, PartonHistory);
      }
      else {
	// first we have to adapt the prefix! Currently the parent can only be a top so there we just need to add "bar"
	prefix = "MC_" + ((parent != "") ? parent + "bar_Wm" : "Wm");
	if (mode == 2 && RetrieveParticleInfo(prefix + "Decay2", WpDecay2, WpDecay2pdgId)) {
	  // Note that we save Wm information from the particle map into the Wp PtEtaPhiMVector because we are flavour agnostic!
	  FillParticleInfo(dec_MC_Wpdecay2_m, dec_MC_Wpdecay2_pt, dec_MC_Wpdecay2_eta, dec_MC_Wpdecay2_phi, dec_MC_Wpdecay2_pdgId, WpDecay2, WpDecay2pdgId, PartonHistory);
	}
      }
    }
    if (mode == 1) { // 1 == W-
      PtEtaPhiMVector Wm;
      PtEtaPhiMVector WmDecay1, WmDecay2;
      int WmDecay1pdgId = -1;
      int WmDecay2pdgId = -1;
      int WmpdgId = -1;

      std::string prefix = "MC_" + ((parent != "") ? parent + "_Wm" : "Wm");

      static const SG::AuxElement::Decorator<float> dec_MC_Wm_m("MC_W" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wm_pt("MC_W" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wm_eta("MC_W" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wm_phi("MC_W" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wm_pdgId("MC_W" + parentstring +"_pdgId");

      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_m("MC_Wdecay1" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_pt("MC_Wdecay1" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_eta("MC_Wdecay1" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_phi("MC_Wdecay1" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wmdecay1_pdgId("MC_Wdecay1" + parentstring + "_pdgId");

      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_m("MC_Wdecay2" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_pt("MC_Wdecay2" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_eta("MC_Wdecay2" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_phi("MC_Wdecay2" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_Wmdecay2_pdgId("MC_Wdecay2" + parentstring + "_pdgId");

      // Decorating with defaults in case the particle doesn't exist
      FillDefaultParticleInfo(dec_MC_Wm_m, dec_MC_Wm_pt, dec_MC_Wm_eta, dec_MC_Wm_phi, PartonHistory);
      FillDefaultParticleInfo(dec_MC_Wmdecay1_m, dec_MC_Wmdecay1_pt, dec_MC_Wmdecay1_eta, dec_MC_Wmdecay1_phi, dec_MC_Wmdecay1_pdgId, PartonHistory);
      FillDefaultParticleInfo(dec_MC_Wmdecay2_m, dec_MC_Wmdecay2_pt, dec_MC_Wmdecay2_eta, dec_MC_Wmdecay2_phi, dec_MC_Wmdecay2_pdgId, PartonHistory);

      if (RetrieveParticleInfo(prefix + "beforeFSR", Wm, WmpdgId)) {
	FillParticleInfo(dec_MC_Wm_m, dec_MC_Wm_pt, dec_MC_Wm_eta, dec_MC_Wm_phi, dec_MC_Wm_pdgId, Wm, WmpdgId, PartonHistory);
      }
      if (RetrieveParticleInfo(prefix + "Decay1", WmDecay1, WmDecay1pdgId)) {
	FillParticleInfo(dec_MC_Wmdecay1_m, dec_MC_Wmdecay1_pt, dec_MC_Wmdecay1_eta, dec_MC_Wmdecay1_phi, dec_MC_Wmdecay1_pdgId, WmDecay1, WmDecay1pdgId, PartonHistory);
      }
      if (RetrieveParticleInfo(prefix + "Decay2", WmDecay2, WmDecay2pdgId)) {
	FillParticleInfo(dec_MC_Wmdecay2_m, dec_MC_Wmdecay2_pt, dec_MC_Wmdecay2_eta, dec_MC_Wmdecay2_phi, dec_MC_Wmdecay2_pdgId, WmDecay2, WmDecay2pdgId, PartonHistory);
      }
    }
  }
}
