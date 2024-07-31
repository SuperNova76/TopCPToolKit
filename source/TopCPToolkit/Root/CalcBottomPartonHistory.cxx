#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
  using PartonHistoryUtils::fillEtaBranch;

  void CalcPartonHistory::FillBottomPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    // Filling b parton history. To indicate where the b quark originates from we use a parent string.
    // Construct parent string
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    TLorentzVector b;

    static const SG::AuxElement::Decorator<float> dec_MC_b_m("MC_b" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_b_pt("MC_b" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_b_eta("MC_b" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_b_phi("MC_b" + parentstring + "_phi");

    std::string prefix = "MC_";
    if (parent != "") prefix += parent + "_b";
    else prefix += "b";

    if (Retrievep4(prefix + "_beforeFSR", b)) {
      FillParticleInfo(dec_MC_b_m, dec_MC_b_pt, dec_MC_b_eta, dec_MC_b_phi, b, PartonHistory);
    }
  }

  void CalcPartonHistory::FillAntiBottomPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    // Filling bbar parton history. To indicate where the bbar quark originates from we use a parent string.
    // Construct parent string
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    TLorentzVector bbar;

    static const SG::AuxElement::Decorator<float> dec_MC_bbar_m("MC_bbar" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_bbar_pt("MC_bbar" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_bbar_eta("MC_bbar" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_bbar_phi("MC_bbar" + parentstring + "_phi");

    std::string prefix = "MC_";
    if (parent != "") prefix += parent + "_bbar";
    else prefix += "bbar";

    if (Retrievep4(prefix + "_beforeFSR", bbar)) {
      FillParticleInfo(dec_MC_bbar_m, dec_MC_bbar_pt, dec_MC_bbar_eta, dec_MC_bbar_phi, bbar, PartonHistory);
    }
  }
}
