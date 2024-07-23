#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  void CalcPartonHistory::FillHiggsPartonHistory(xAOD::PartonHistory* PartonHistory) {

    TLorentzVector H;
    TLorentzVector HDecay1, HDecay2;
    TLorentzVector HDecay1_Decay1, HDecay1_Decay2;
    TLorentzVector HDecay2_Decay1, HDecay2_Decay2;

    int HDecay1pdgId = 0;
    int HDecay2pdgId = 0;
    int HDecay1_Decay1pdgId = 0;
    int HDecay1_Decay2pdgId = 0;
    int HDecay2_Decay1pdgId = 0;
    int HDecay2_Decay2pdgId = 0;

    static const SG::AuxElement::Decorator<float> dec_MC_H_m("MC_H_m");
    static const SG::AuxElement::Decorator<float> dec_MC_H_pt("MC_H_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_H_eta("MC_H_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_H_phi("MC_H_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_m("MC_Hdecay1_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_pt("MC_Hdecay1_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_eta("MC_Hdecay1_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_phi("MC_Hdecay1_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay1_pdgId("MC_Hdecay1_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_m("MC_Hdecay2_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_pt("MC_Hdecay2_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_eta("MC_Hdecay2_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_phi("MC_Hdecay2_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay2_pdgId("MC_Hdecay2_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay1_m("MC_Hdecay1_decay1_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay1_pt("MC_Hdecay1_decay1_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay1_eta("MC_Hdecay1_decay1_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay1_phi("MC_Hdecay1_decay1_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay1_decay1_pdgId("MC_Hdecay1_decay1_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay2_m("MC_Hdecay1_decay2_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay2_pt("MC_Hdecay1_decay2_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay2_eta("MC_Hdecay1_decay2_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay1_decay2_phi("MC_Hdecay1_decay2_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay1_decay2_pdgId("MC_Hdecay1_decay2_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay1_m("MC_Hdecay2_decay1_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay1_pt("MC_Hdecay2_decay1_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay1_eta("MC_Hdecay2_decay1_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay1_phi("MC_Hdecay2_decay1_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay2_decay1_pdgId("MC_Hdecay2_decay1_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay2_m("MC_Hdecay2_decay2_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay2_pt("MC_Hdecay2_decay2_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay2_eta("MC_Hdecay2_decay2_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Hdecay2_decay2_phi("MC_Hdecay2_decay2_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Hdecay2_decay2_pdgId("MC_Hdecay2_decay2_pdgId");

    FillDefaultParticleInfo(dec_MC_H_m, dec_MC_H_pt, dec_MC_H_eta, dec_MC_H_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Hdecay1_m, dec_MC_Hdecay1_pt, dec_MC_Hdecay1_eta, dec_MC_Hdecay1_phi, dec_MC_Hdecay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Hdecay2_m, dec_MC_Hdecay2_pt, dec_MC_Hdecay2_eta, dec_MC_Hdecay2_phi, dec_MC_Hdecay2_pdgId, PartonHistory);

    FillDefaultParticleInfo(dec_MC_Hdecay1_decay1_m, dec_MC_Hdecay1_decay1_pt, dec_MC_Hdecay1_decay1_eta, dec_MC_Hdecay1_decay1_phi, dec_MC_Hdecay1_decay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Hdecay1_decay2_m, dec_MC_Hdecay1_decay2_pt, dec_MC_Hdecay1_decay2_eta, dec_MC_Hdecay1_decay2_phi, dec_MC_Hdecay1_decay2_pdgId, PartonHistory);

    FillDefaultParticleInfo(dec_MC_Hdecay2_decay1_m, dec_MC_Hdecay2_decay1_pt, dec_MC_Hdecay2_decay1_eta, dec_MC_Hdecay2_decay1_phi, dec_MC_Hdecay2_decay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Hdecay2_decay2_m, dec_MC_Hdecay2_decay2_pt, dec_MC_Hdecay2_decay2_eta, dec_MC_Hdecay2_decay2_phi, dec_MC_Hdecay2_decay2_pdgId, PartonHistory);


    if (Retrievep4("MC_H_afterFSR", H)) {
      // As this is always a Higgs we don't set the pdgId
      FillParticleInfo(dec_MC_H_m, dec_MC_H_pt, dec_MC_H_eta, dec_MC_H_phi, H, PartonHistory);
    }
    // Higgs decay:
    if (RetrieveParticleInfo("MC_HDecay1", HDecay1, HDecay1pdgId)) {
      FillParticleInfo(dec_MC_Hdecay1_m, dec_MC_Hdecay1_pt, dec_MC_Hdecay1_eta, dec_MC_Hdecay1_phi, dec_MC_Hdecay1_pdgId, HDecay1, HDecay1pdgId, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_HDecay2", HDecay2, HDecay2pdgId)) {
      FillParticleInfo(dec_MC_Hdecay2_m, dec_MC_Hdecay2_pt, dec_MC_Hdecay2_eta, dec_MC_Hdecay2_phi, dec_MC_Hdecay2_pdgId, HDecay2, HDecay2pdgId, PartonHistory);
    }
    // decays of higgs decay products:
    if (RetrieveParticleInfo("MC_HDecay1_Decay1", HDecay1_Decay1, HDecay1_Decay1pdgId)) {
      FillParticleInfo(dec_MC_Hdecay1_decay1_m, dec_MC_Hdecay1_decay1_pt, dec_MC_Hdecay1_decay1_eta, dec_MC_Hdecay1_decay1_phi, dec_MC_Hdecay1_decay1_pdgId, HDecay1_Decay1, HDecay1_Decay1pdgId, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_HDecay1_Decay2", HDecay1_Decay2, HDecay1_Decay2pdgId)) {
      FillParticleInfo(dec_MC_Hdecay1_decay2_m, dec_MC_Hdecay1_decay2_pt, dec_MC_Hdecay1_decay2_eta, dec_MC_Hdecay1_decay2_phi, dec_MC_Hdecay1_decay2_pdgId, HDecay1_Decay2, HDecay1_Decay2pdgId, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_HDecay2_Decay1", HDecay2_Decay1, HDecay2_Decay1pdgId)) {
      FillParticleInfo(dec_MC_Hdecay2_decay1_m, dec_MC_Hdecay2_decay1_pt, dec_MC_Hdecay2_decay1_eta, dec_MC_Hdecay2_decay1_phi, dec_MC_Hdecay2_decay1_pdgId, HDecay2_Decay1, HDecay2_Decay1pdgId, PartonHistory);
    }

    if (RetrieveParticleInfo("MC_HDecay2_Decay2", HDecay2_Decay2, HDecay2_Decay2pdgId)) {
      FillParticleInfo(dec_MC_Hdecay2_decay2_m, dec_MC_Hdecay2_decay2_pt, dec_MC_Hdecay2_decay2_eta, dec_MC_Hdecay2_decay2_phi, dec_MC_Hdecay2_decay2_pdgId, HDecay2_Decay2, HDecay2_Decay2pdgId, PartonHistory);
    }
  }
}
