#ifndef TOPPARTONS_CALCTTHPARTONHISTORY_H
#define TOPPARTONS_CALCTTHPARTONHISTORY_H

// Framework include(s):
#include "TopPartons/CalcTopPartonHistory.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"

namespace top {
  class CalcTthPartonHistory: public CalcTopPartonHistory {
  public:
    explicit CalcTthPartonHistory(const std::string &name,
				  std::vector<std::string> truthCollections = {"TruthTop","TruthBosonsWithDecayParticles"});
    virtual ~CalcTthPartonHistory() {}

    //Storing parton history for tth resonance analysis
    CalcTthPartonHistory(const CalcTthPartonHistory& rhs) = delete;
    CalcTthPartonHistory(CalcTthPartonHistory&& rhs) = delete;
    CalcTthPartonHistory& operator = (const CalcTthPartonHistory& rhs) = delete;

  protected:
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* tthPartonHistory) override;
  };
}

#endif
