#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillZPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent, const int bosonID) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent+"_";
    else parentstring = "_";
    
    PtEtaPhiMVector Z;

    std::string decorator_prefix = "MC_";
    if (bosonID != -1) decorator_prefix += "Z" + std::to_string(bosonID);
    else decorator_prefix += "Z";
    
    PtEtaPhiMVector ZDecay1, ZDecay2;
    int ZDecay1pdgId = -1;
    int ZDecay2pdgId = -1;

    static const SG::AuxElement::Decorator<float> dec_MC_Z_m(decorator_prefix + parentstring + "m");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_pt(decorator_prefix + parentstring + "pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_eta(decorator_prefix + parentstring + "eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_phi(decorator_prefix + parentstring + "phi");

    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_m(decorator_prefix + "decay1" + parentstring + "m");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_pt(decorator_prefix + "decay1" + parentstring + "pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_eta(decorator_prefix + "decay1" + parentstring + "eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_phi(decorator_prefix + "decay1" + parentstring + "phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Zdecay1_pdgId(decorator_prefix + "decay1" + parentstring + "pdgId");
    
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_m(decorator_prefix + "decay2" + parentstring + "m");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_pt(decorator_prefix + "decay2" + parentstring + "pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_eta(decorator_prefix + "decay2" + parentstring + "eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_phi(decorator_prefix + "decay2" + parentstring + "phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Zdecay2_pdgId(decorator_prefix + "decay2" + parentstring + "pdgId");

    static const SG::AuxElement::Decorator<int> dec_MC_Z_IsOnShell("MC_Z_IsOnShell");

    std::string accessor_prefix = "MC_";
    if (parent != "") accessor_prefix += parent + "_Z";
    else accessor_prefix += "Z";
    if (bosonID != -1) accessor_prefix += std::to_string(bosonID);

    FillDefaultParticleInfo(dec_MC_Z_m, dec_MC_Z_pt, dec_MC_Z_eta, dec_MC_Z_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Zdecay1_m, dec_MC_Zdecay1_pt, dec_MC_Zdecay1_eta, dec_MC_Zdecay1_phi, dec_MC_Zdecay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, PartonHistory);

    if (Retrievep4(accessor_prefix + "_afterFSR", Z)) {
      // As this is always a Z we don't set the pdgId
      FillParticleInfo(dec_MC_Z_m, dec_MC_Z_pt, dec_MC_Z_eta, dec_MC_Z_phi, Z, PartonHistory);
    }

    // off-shell treatment
    bool isonshell = true;
    if (!(RetrieveParticleInfo(accessor_prefix + "Decay1", ZDecay1, ZDecay1pdgId) && RetrieveParticleInfo(accessor_prefix + "Decay2", ZDecay2, ZDecay2pdgId))) {
      // if We didn't find ZDecay1 and ZDecay2 yet it is probably because we have particles not directlry originating from a Z.
      // Instead we are now looking for light quarks/light leptons as first particles in the paths
      isonshell = false;
      bool has_ZDecay1 = (RetrieveParticleInfo("MC_l", ZDecay1, ZDecay1pdgId) ||
			  RetrieveParticleInfo("MC_q", ZDecay1, ZDecay1pdgId) ||
			  RetrieveParticleInfo("MC_nu", ZDecay1, ZDecay1pdgId));
      bool has_ZDecay2 = (RetrieveParticleInfo("MC_lbar", ZDecay2, ZDecay2pdgId) ||
			  RetrieveParticleInfo("MC_qbar", ZDecay2, ZDecay2pdgId) ||
			  RetrieveParticleInfo("MC_nubar", ZDecay2, ZDecay2pdgId));
      if (has_ZDecay1 && has_ZDecay2) {
	// If we find these two particles, we construct a Z from them
	Z = ZDecay1 + ZDecay2;
      }
      FillParticleInfo(dec_MC_Z_m, dec_MC_Z_pt, dec_MC_Z_eta, dec_MC_Z_phi, Z, PartonHistory);
    }

    if (!isonshell) {
      FillParticleInfo(dec_MC_Zdecay1_m, dec_MC_Zdecay1_pt, dec_MC_Zdecay1_eta, dec_MC_Zdecay1_phi, dec_MC_Zdecay1_pdgId, ZDecay1, ZDecay1pdgId, PartonHistory);
    }
    else {
      // on-shell case
      if (RetrieveParticleInfo(accessor_prefix + "Decay1", ZDecay1, ZDecay1pdgId)) {
	FillParticleInfo(dec_MC_Zdecay1_m, dec_MC_Zdecay1_pt, dec_MC_Zdecay1_eta, dec_MC_Zdecay1_phi, dec_MC_Zdecay1_pdgId, ZDecay1, ZDecay1pdgId, PartonHistory);
      }
    }
    if (!isonshell) {
      FillParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, ZDecay2, ZDecay2pdgId, PartonHistory);
    }
    else {
      // on-shell case
      if (RetrieveParticleInfo(accessor_prefix + "Decay2", ZDecay2, ZDecay2pdgId)) {
	FillParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, ZDecay2, ZDecay2pdgId, PartonHistory);
      }
    }
    dec_MC_Z_IsOnShell(*PartonHistory) = (int)isonshell;
  }
}
