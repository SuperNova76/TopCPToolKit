#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;
  
  void CalcPartonHistory::FillGammaPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent) {
    std::string parentstring = "";
    if (parent != "") parentstring = "_from_"+parent;

    PtEtaPhiMVector gamma;

    static const SG::AuxElement::Decorator<float> dec_MC_gamma_m("MC_gamma" + parentstring + "_m");
    static const SG::AuxElement::Decorator<float> dec_MC_gamma_pt("MC_gamma" + parentstring + "_pt");
    static const SG::AuxElement::Decorator<float> dec_MC_gamma_eta("MC_gamma" + parentstring + "_eta");
    static const SG::AuxElement::Decorator<float> dec_MC_gamma_phi("MC_gamma" + parentstring + "_phi");
    
    std::string prefix = "MC_";
    if (parent != "") prefix += parent + "_gamma";
    else prefix += "gamma";

    if (Retrievep4(prefix, gamma)) {
      FillParticleInfo(dec_MC_gamma_m, dec_MC_gamma_pt, dec_MC_gamma_eta, dec_MC_gamma_phi, gamma, PartonHistory);
    }
  }
}
