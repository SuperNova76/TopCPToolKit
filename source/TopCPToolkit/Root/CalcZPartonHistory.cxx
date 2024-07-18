#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  void CalcPartonHistory::FillZPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    // Filling Z parton history. To indicate where the Z originates from we use a parent string.
    // Construct parent string
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    TLorentzVector Z;
    TLorentzVector ZDecay1;
    TLorentzVector ZDecay2;
    int ZDecay1pdgId = -1;
    int ZDecay2pdgId = -1;

    static const SG::AuxElement::Decorator<float> dec_MC_Z_m("MC_Z_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_pt("MC_Z_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_eta("MC_Z_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Z_phi("MC_Z_" + parentstring + "_phi");

    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_m("MC_Zdecay1_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_pt("MC_Zdecay1_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_eta("MC_Zdecay1_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay1_phi("MC_Zdecay1_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Zdecay1_pdgId("MC_Zdecay1_" + parentstring + "_pdgId");

    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_m("MC_Zdecay2_" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_pt("MC_Zdecay2_" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_eta("MC_Zdecay2_" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_Zdecay2_phi("MC_Zdecay2_" + parentstring + "_phi");
    static const SG::AuxElement::Decorator<int> dec_MC_Zdecay2_pdgId("MC_Zdecay2_" + parentstring + "_pdgId");

    static const SG::AuxElement::Decorator<int> dec_MC_Z_IsOnShell("MC_Z_IsOnShell");

    std::string prefix = "MC_";

    if (parent != "") prefix += parent + "_Z";
    else prefix += "Z";

    FillDefaultParticleInfo(dec_MC_Z_m, dec_MC_Z_pt, dec_MC_Z_eta, dec_MC_Z_phi, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Zdecay1_m, dec_MC_Zdecay1_pt, dec_MC_Zdecay1_eta, dec_MC_Zdecay1_phi, dec_MC_Zdecay1_pdgId, PartonHistory);
    FillDefaultParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, PartonHistory);

    if (Retrievep4(prefix + "_afterFSR", Z)) {
      // As this is always a Z we don't set the pdgId
      FillParticleInfo(dec_MC_Z_m, dec_MC_Z_pt, dec_MC_Z_eta, dec_MC_Z_phi, Z, PartonHistory);
    }

    // off-shell treatment
    bool isonshell = true;
    if (!(RetrieveParticleInfo(prefix + "Decay1", ZDecay1, ZDecay1pdgId) && RetrieveParticleInfo(prefix + "Decay2", ZDecay2, ZDecay2pdgId))) {
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
      if (RetrieveParticleInfo(prefix + "Decay1", ZDecay1, ZDecay1pdgId)) {
	FillParticleInfo(dec_MC_Zdecay1_m, dec_MC_Zdecay1_pt, dec_MC_Zdecay1_eta, dec_MC_Zdecay1_phi, dec_MC_Zdecay1_pdgId, ZDecay1, ZDecay1pdgId, PartonHistory);
      }
    }
    if (!isonshell) {
      FillParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, ZDecay2, ZDecay2pdgId, PartonHistory);
    }
    else {
      // on-shell case
      if (RetrieveParticleInfo(prefix + "Decay2", ZDecay2, ZDecay2pdgId)) {
	FillParticleInfo(dec_MC_Zdecay2_m, dec_MC_Zdecay2_pt, dec_MC_Zdecay2_eta, dec_MC_Zdecay2_phi, dec_MC_Zdecay2_pdgId, ZDecay2, ZDecay2pdgId, PartonHistory);
      }
    }
    dec_MC_Z_IsOnShell(*PartonHistory) = (int)isonshell;
  }
}
