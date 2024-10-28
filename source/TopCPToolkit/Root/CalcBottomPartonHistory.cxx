#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillBottomPartonHistory(xAOD::PartonHistory* PartonHistory,
						  const std::string& parent,
						  const int& mode,
						  PartonDecorator& dec) {
    std::string parentstring = parent.empty() ? "" : "_from_" + parent;
    std::string baseprefix = "MC_";
    std::string suffix;
    PtEtaPhiMVector v;
    int pdgId = 0;

    if (mode == 0 || mode == 2) { // 0 == b, 2 == flavour agnostic
      // Decorating with defaults in case the particle doesn't exist
      suffix = "b";
      dec.decorateDefault(baseprefix + suffix + "_beforeFSR" + parentstring, PartonHistory);
      dec.decorateDefault(baseprefix + suffix + "_afterFSR" + parentstring, PartonHistory);
      // Currently the parent can only be a top so there we just need to add "bar"
    }
    if ( mode == 1 ) {
      suffix = "bbar";
      dec.decorateDefault(baseprefix + suffix + "_beforeFSR" + parentstring, PartonHistory);
      dec.decorateDefault(baseprefix + suffix + "_afterFSR" + parentstring, PartonHistory);
    }

    std::string retrievalprefix = baseprefix + (parent.empty() ? "" : parent + "_") + suffix;
    std::string decorationprefix = baseprefix + suffix;

    // Note, the order of evaluation matters here. The prefix depends on the mode.
    // The flavour agnostic part is only triggered if mode == 2 AND the first retrieve function returns false
    if ( RetrieveParticleInfo(retrievalprefix + "_beforeFSR", v, pdgId) ||
	 (mode == 2 && (RetrieveParticleInfo(retrievalprefix + "_beforeFSR", v, pdgId) ||
			RetrieveParticleInfo(retrievalprefix + "bar" + "_beforeFSR", v, pdgId)))) {
      dec.decorateParticle(decorationprefix + "_beforeFSR" + parentstring, v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo(retrievalprefix + "_afterFSR", v, pdgId) ||
	 (mode == 2 && (RetrieveParticleInfo(retrievalprefix + "_afterFSR", v, pdgId) ||
			RetrieveParticleInfo(retrievalprefix + "bar" + "_afterFSR", v, pdgId)))) {
      dec.decorateParticle(decorationprefix + "_afterFSR" + parentstring, v, pdgId, PartonHistory);
    }
  }
}
