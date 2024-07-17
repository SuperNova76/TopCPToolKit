#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  void CalcPartonHistory::FillWpPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    TLorentzVector Wp, WpDecay1, WpDecay2;
    int WpDecay1pdgId = -1, WpDecay2pdgId = -1;

    static const SG::AuxElement::Decorator<float> dec_MC_Wp_m("MC_W_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wp_pt("MC_W_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wp_eta("MC_W_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wp_phi("MC_W_" + parentstring + "_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_m("MC_Wdecay1_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_pt("MC_Wdecay1_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_eta("MC_Wdecay1_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay1_phi("MC_Wdecay1_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Wpdecay1_pdgId("MC_Wdecay1_" + parentstring + "_pdgId");
    
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_m("MC_Wdecay2_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_pt("MC_Wdecay2_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_eta("MC_Wdecay2_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wpdecay2_phi("MC_Wdecay2_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Wpdecay2_pdgId("MC_Wdecay2_" + parentstring + "_pdgId");
    
    std::string prefix = "MC_" + ((parent != "") ? parent + "_Wp" : "Wp");

    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_Wp_m, dec_MC_Wp_pt, dec_MC_Wp_eta, dec_MC_Wp_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Wpdecay1_m, dec_MC_Wpdecay1_pt, dec_MC_Wpdecay1_eta, dec_MC_Wpdecay1_phi, dec_MC_Wpdecay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Wpdecay2_m, dec_MC_Wpdecay2_pt, dec_MC_Wpdecay2_eta, dec_MC_Wpdecay2_phi, dec_MC_Wpdecay2_pdgId, PartonHistory);

    if (Retrievep4(prefix + "_beforeFSR", Wp)) {
      // As this is always a W+ we don't set the pdgId
      FillParticleInfo(dec_MC_Wp_m, dec_MC_Wp_pt, dec_MC_Wp_eta, dec_MC_Wp_phi, Wp, PartonHistory);
    }
    if (RetrieveParticleInfo(prefix + "Decay1", WpDecay1, WpDecay1pdgId)) {
      FillParticleInfo(dec_MC_Wpdecay1_m, dec_MC_Wpdecay1_pt, dec_MC_Wpdecay1_eta, dec_MC_Wpdecay1_phi, dec_MC_Wpdecay1_pdgId, WpDecay1, WpDecay1pdgId, PartonHistory);
    }
    if (RetrieveParticleInfo(prefix + "Decay2", WpDecay2, WpDecay2pdgId)) {
      FillParticleInfo(dec_MC_Wpdecay2_m, dec_MC_Wpdecay2_pt, dec_MC_Wpdecay2_eta, dec_MC_Wpdecay2_phi, dec_MC_Wpdecay2_pdgId, WpDecay2, WpDecay2pdgId, PartonHistory);
    }
  }

  void CalcPartonHistory::FillWmPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    TLorentzVector Wm, WmDecay1, WmDecay2;
    int WmDecay1pdgId = -1, WmDecay2pdgId = -1;

    static const SG::AuxElement::Decorator<float> dec_MC_Wm_m("MC_W_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wm_pt("MC_W_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wm_eta("MC_W_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wm_phi("MC_W_" + parentstring + "_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_m("MC_Wdecay1_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_pt("MC_Wdecay1_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_eta("MC_Wdecay1_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay1_phi("MC_Wdecay1_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Wmdecay1_pdgId("MC_Wdecay1_" + parentstring + "_pdgId");
    
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_m("MC_Wdecay2_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_pt("MC_Wdecay2_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_eta("MC_Wdecay2_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Wmdecay2_phi("MC_Wdecay2_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Wmdecay2_pdgId("MC_Wdecay2_" + parentstring + "_pdgId");
    
    std::string prefix = "MC_" + ((parent != "") ? parent + "_Wm" : "Wm");
    
    // Decorating with defaults in case the particle doesn't exist
    FillDefaultParticleInfo(dec_MC_Wm_m, dec_MC_Wm_pt, dec_MC_Wm_eta, dec_MC_Wm_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Wmdecay1_m, dec_MC_Wmdecay1_pt, dec_MC_Wmdecay1_eta, dec_MC_Wmdecay1_phi, dec_MC_Wmdecay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Wmdecay2_m, dec_MC_Wmdecay2_pt, dec_MC_Wmdecay2_eta, dec_MC_Wmdecay2_phi, dec_MC_Wmdecay2_pdgId, PartonHistory);
    
    if (Retrievep4(prefix + "_beforeFSR", Wm)) {
      // As this is always a W+ we don't set the pdgId
        FillParticleInfo(dec_MC_Wm_m, dec_MC_Wm_pt, dec_MC_Wm_eta, dec_MC_Wm_phi, Wm, PartonHistory);
    }
    if (RetrieveParticleInfo(prefix + "Decay1", WmDecay1, WmDecay1pdgId)) {
      FillParticleInfo(dec_MC_Wmdecay1_m, dec_MC_Wmdecay1_pt, dec_MC_Wmdecay1_eta, dec_MC_Wmdecay1_phi, dec_MC_Wmdecay1_pdgId, WmDecay1, WmDecay1pdgId, PartonHistory);
    }
    if (RetrieveParticleInfo(prefix + "Decay2", WmDecay2, WmDecay2pdgId)) {
      FillParticleInfo(dec_MC_Wmdecay2_m, dec_MC_Wmdecay2_pt, dec_MC_Wmdecay2_eta, dec_MC_Wmdecay2_phi, dec_MC_Wmdecay2_pdgId, WmDecay2, WmDecay2pdgId, PartonHistory);
    }
  }
}
