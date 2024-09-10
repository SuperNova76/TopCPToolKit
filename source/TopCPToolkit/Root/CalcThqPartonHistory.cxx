#include "PartonHistory/CalcThqPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcThqPartonHistory::CalcThqPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

   void CalcThqPartonHistory::initializeDecorators() {
     CalcPartonHistory::InitializeTopDecorators();
     CalcPartonHistory::InitializeBottomDecorators();
     CalcPartonHistory::InitializeHiggsDecorators();
  }

  StatusCode CalcThqPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* thqPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist(); // this will fail on ttbar but that is ok.

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(thqPartonHistory, 2, m_t_dec); // flavour agnostic mode
    // Fill b parton history
    CalcPartonHistory::FillBottomPartonHistory(thqPartonHistory, "", 2, m_b_dec); // flavour agnostic mode
    // Fill H parton history
    CalcPartonHistory::FillHiggsPartonHistory(thqPartonHistory, m_H_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
