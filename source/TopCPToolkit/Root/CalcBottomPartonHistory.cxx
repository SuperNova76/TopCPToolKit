#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillBottomPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent, const int& mode) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    if (mode == 0 || mode == 2) { // 0 == b, 2 == flavour agnostic
      PtEtaPhiMVector b;
      int b_pdgId = -1;

      static const SG::AuxElement::Decorator<float> dec_MC_b_m("MC_b" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_b_pt("MC_b" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_b_eta("MC_b" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_b_phi("MC_b" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_b_pdgId("MC_b" + parentstring + "_pdgId");

      std::string prefix = "MC_";
      if (parent != "") prefix += parent + "_b";
      else prefix += "b";

      if (RetrieveParticleInfo(prefix + "_beforeFSR", b, b_pdgId)) {
	FillParticleInfo(dec_MC_b_m, dec_MC_b_pt, dec_MC_b_eta, dec_MC_b_phi, dec_MC_b_pdgId, b, b_pdgId, PartonHistory);
      }
      else {
	// first we have to adapt the prefix! Currently the parent can only be a top so there we just need to add "bar"
	prefix = "MC_" + ((parent != "") ? parent + "bar_bbar" : "bbar");
	if (mode == 2 && RetrieveParticleInfo(prefix + "_beforeFSR", b, b_pdgId)) {
	  // Note that we save bbar into b because we are flavour agnostic!
	  FillParticleInfo(dec_MC_b_m, dec_MC_b_pt, dec_MC_b_eta, dec_MC_b_phi, dec_MC_b_pdgId, b, b_pdgId, PartonHistory);
	}
      }
    }
    if (mode == 1) { // 1 == bbar
      PtEtaPhiMVector bbar;
      int bbar_pdgId = -1;

      static const SG::AuxElement::Decorator<float> dec_MC_bbar_m("MC_bbar" + parentstring + "_m");
      static const SG::AuxElement::Decorator<float> dec_MC_bbar_pt("MC_bbar" + parentstring + "_pt");
      static const SG::AuxElement::Decorator<float> dec_MC_bbar_eta("MC_bbar" + parentstring + "_eta");
      static const SG::AuxElement::Decorator<float> dec_MC_bbar_phi("MC_bbar" + parentstring + "_phi");
      static const SG::AuxElement::Decorator<int> dec_MC_bbar_pdgId("MC_bbar" + parentstring + "_pdgId");

      std::string prefix = "MC_";
      if (parent != "") prefix += parent + "_bbar";
      else prefix += "bbar";

      if (RetrieveParticleInfo(prefix + "_beforeFSR", bbar, bbar_pdgId)) {
	FillParticleInfo(dec_MC_bbar_m, dec_MC_bbar_pt, dec_MC_bbar_eta, dec_MC_bbar_phi, dec_MC_bbar_pdgId, bbar, bbar_pdgId, PartonHistory);
      }
    }
  }
}
