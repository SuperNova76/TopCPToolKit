#ifndef TOPPARTONS_CALCTTZPARTONHISTORY_H
#define TOPPARTONS_CALCTTZPARTONHISTORY_H

// Framework include(s):
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"
#include "TopPartons/CalcTtbarPartonHistory.h"

namespace top {
  class CalcTTZPartonHistory: public CalcTtbarPartonHistory {
  public:
    explicit CalcTTZPartonHistory(const std::string& name);
    virtual ~CalcTTZPartonHistory() {}

    //Storing parton history for TTZ analysis
    CalcTTZPartonHistory(const CalcTTZPartonHistory& rhs) = delete;
    CalcTTZPartonHistory(CalcTTZPartonHistory&& rhs) = delete;
    CalcTTZPartonHistory& operator = (const CalcTTZPartonHistory& rhs) = delete;
    
    //Store the four-momentum of the associated Z boson and its decay products
    bool getZ(const xAOD::TruthParticleContainer* truthParticles,
              TLorentzVector* Z_p4,
              TLorentzVector* ZDecay1,
              int* ZDecay1_pdgId,
              TLorentzVector* ZDecay2,
              int* ZDecay2_pdgId,
              bool* is_on_shell);

    //Return particle with same flavour and opposite sign from same vertex
    const xAOD::TruthParticle* getFlavourSibling(const xAOD::TruthParticle* particle);

  protected:
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* ttbarPartonHistory) override;

    // on top of ttbar stuff in runHistorySaver, run also the truth Z-finding
    StatusCode zHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                             xAOD::PartonHistory* ttbarPartonHistory);
    
  private:
    bool m_ancestry_corrupted;
  };
}

#endif
