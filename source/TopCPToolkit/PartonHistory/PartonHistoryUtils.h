#ifndef ANALYSISTOP_TOPPARTONS_TOPPARTONUTILS_H
#define ANALYSISTOP_TOPPARTONS_TOPPARTONUTILS_H

#include "xAODTruth/TruthParticleContainer.h"

#include "TLorentzVector.h"
#include <string>

namespace top {
  class PartonHistory;

  namespace PartonHistoryUtils {
    ///Return particle after FSR (before the decay vertex)
    const xAOD::TruthParticle* findAfterFSR(const xAOD::TruthParticle* particle);

    ///Looking for tops without children -> must be broken
    bool isBrokenTop(const xAOD::TruthParticle* particle);

    ///Determine whether particle is afterFSR
    bool isAfterFSR(const xAOD::TruthParticle* particle);

    ///Return true when particle is a top before FSR
    bool hasParticleIdenticalParent(const xAOD::TruthParticle* particle);

    /// Perform decoration M, Pt, Phi of the history from a TLorentzVector
    void decorateWithMPtPhi(xAOD::PartonHistory* pHistory, const std::string & prefix, const TLorentzVector & vec );

    void fillEtaBranch(xAOD::PartonHistory* partonHistory, std:: string branchName, TLorentzVector& tlv);
  } // namespace PartonHistoryUtils
} // namespace top

#endif
