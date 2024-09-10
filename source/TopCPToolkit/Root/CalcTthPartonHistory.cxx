#include "PartonHistory/CalcTthPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTthPartonHistory::CalcTthPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {
      initializeDecorators();
    }

  void CalcTthPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeAntiTopDecorators();
    CalcPartonHistory::InitializeTtbarDecorators();
    CalcPartonHistory::InitializeHiggsDecorators();
  }

  StatusCode CalcTthPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* tthPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(tthPartonHistory, 0, m_t_dec); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(tthPartonHistory, 1, m_tbar_dec); // ttbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(tthPartonHistory, m_ttbar_dec);
    // Fill Higgs parton history
    CalcPartonHistory::FillHiggsPartonHistory(tthPartonHistory, m_H_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
