#include "PartonHistory/CalcTtbarPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtbarPartonHistory::CalcTtbarPartonHistory(const std::string& name,
                                                 const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

  void CalcTtbarPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeAntiTopDecorators();
    CalcPartonHistory::InitializeTtbarDecorators();
  }

  StatusCode CalcTtbarPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttbarPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttbarPartonHistory, 0, m_t_dec); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttbarPartonHistory, 1, m_tbar_dec); // ttbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttbarPartonHistory, m_ttbar_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
