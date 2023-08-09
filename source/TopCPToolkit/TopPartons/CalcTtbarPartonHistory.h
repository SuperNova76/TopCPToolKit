#ifndef TOPPARTONS_CALCTTBARPARTONHISTORY_H
#define TOPPARTONS_CALCTTBARPARTONHISTORY_H

// Framework include(s):
#include "TopPartons/CalcTopPartonHistory.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"

namespace top {
  class CalcTtbarPartonHistory: public CalcTopPartonHistory {
  public:
    explicit CalcTtbarPartonHistory(const std::string& name);
    virtual ~CalcTtbarPartonHistory() {}

    //Storing parton history for ttbar resonance analysis
    CalcTtbarPartonHistory(const CalcTtbarPartonHistory& rhs) = delete;
    CalcTtbarPartonHistory(CalcTtbarPartonHistory&& rhs) = delete;
    CalcTtbarPartonHistory& operator = (const CalcTtbarPartonHistory& rhs) = delete;

    void ttbarHistorySaver(const xAOD::TruthParticleContainer* truthParticles, xAOD::PartonHistory* ttbarPartonHistory);

    virtual StatusCode execute();
  };
}

#endif
