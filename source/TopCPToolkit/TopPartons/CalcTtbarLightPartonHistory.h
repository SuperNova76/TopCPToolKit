#ifndef TOPPARTONS_CALCTTBARLIGHTPARTONHISTORY_H
#define TOPPARTONS_CALCTTBARLIGHTPARTONHISTORY_H

// Framework include(s):
#include "TopPartons/CalcTopPartonHistory.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"

namespace top {
  class CalcTtbarLightPartonHistory: public CalcTopPartonHistory {
  public:
    explicit CalcTtbarLightPartonHistory(const std::string& name);
    virtual ~CalcTtbarLightPartonHistory() {}

    //Storing parton history for ttbar resonance analysis
    CalcTtbarLightPartonHistory(const CalcTtbarLightPartonHistory& rhs) = delete;
    CalcTtbarLightPartonHistory(CalcTtbarLightPartonHistory&& rhs) = delete;
    CalcTtbarLightPartonHistory& operator = (const CalcTtbarLightPartonHistory& rhs) = delete;

    void ttbarHistorySaver(const xAOD::TruthParticleContainer* truthParticles, xAOD::PartonHistory* ttbarPartonHistory);

    virtual StatusCode execute();
  };
}

#endif
