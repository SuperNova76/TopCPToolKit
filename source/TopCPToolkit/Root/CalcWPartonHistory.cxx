#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillWPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent, const int& mode, PartonDecorator& dec) {
    std::string parentstring = parent.empty() ? "" : "_from_" + parent;
    std::string basePrefix = "MC_" + (parent.empty() ? "" : parent + "_");
    std::string prefix, alt_prefix;
    PtEtaPhiMVector v;
    int pdgId = 0;

    // Decorating with defaults in case the particle doesn't exist
    dec.decorateDefault("MC_W_beforeFSR" + parentstring, PartonHistory);
    dec.decorateDefault("MC_W_afterFSR" + parentstring, PartonHistory);
    dec.decorateDefault("MC_Wdecay1_beforeFSR" + parentstring, PartonHistory);
    dec.decorateDefault("MC_Wdecay1_afterFSR" + parentstring, PartonHistory);
    dec.decorateDefault("MC_Wdecay2_beforeFSR" + parentstring, PartonHistory);
    dec.decorateDefault("MC_Wdecay2_afterFSR" + parentstring, PartonHistory);

    // Currently the parent can only be a top so there we just need to add "bar"
    alt_prefix = "MC_" + ((parent != "") ? parent + "bar_Wm" : "Wm");
    if (mode == 0 || mode == 2) prefix = basePrefix + "Wp"; // 0 == W+, 2 == flavour agnostic
    if (mode == 1 ) prefix = basePrefix + "Wm"; // 1 == W-

    // Note, the order of evaluation matters here. The prefix depends on the mode.
    // The flavour agnostic part is only triggered if mode == 2 AND the first retrieve function returns false
    if ( RetrieveParticleInfo(prefix + "_beforeFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "_beforeFSR", alt_prefix + "_beforeFSR", v, pdgId))) {
      dec.decorateParticle("MC_W_beforeFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(prefix + "_afterFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "_afterFSR", alt_prefix + "_afterFSR", v, pdgId))) {
      dec.decorateParticle("MC_W_afterFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(prefix + "Decay1_beforeFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "Decay1_beforeFSR", alt_prefix + "Decay1_beforeFSR", v, pdgId))) {
      dec.decorateParticle("MC_Wdecay1_beforeFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(prefix + "Decay1_afterFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "Decay1_afterFSR", alt_prefix + "Decay1_afterFSR", v, pdgId))) {
      dec.decorateParticle("MC_Wdecay1_afterFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(prefix + "Decay2_beforeFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "Decay2_beforeFSR", alt_prefix + "Decay2_beforeFSR", v, pdgId))) {
      dec.decorateParticle("MC_Wdecay2_beforeFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(prefix + "Decay2_afterFSR", v, pdgId) ||
	 (mode == 2 && RetrieveParticleInfo(prefix + "Decay2_afterFSR", alt_prefix + "Decay2_afterFSR", v, pdgId))) {
      dec.decorateParticle("MC_Wdecay2_afterFSR" + parentstring, v, pdgId, PartonHistory);
    }
  }
}
