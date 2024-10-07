#include "PartonHistory/CalcTtwPartonHistory.h"
#include "PartonHistory/CalcTtbarPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtwPartonHistory::CalcTtwPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

  void CalcTtwPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeAntiTopDecorators();
    CalcPartonHistory::InitializeTtbarDecorators();
    CalcPartonHistory::InitializeWDecorators();
  }

  StatusCode CalcTtwPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
						   xAOD::PartonHistory* ttwPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttwPartonHistory, 0, m_t_dec); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttwPartonHistory, 1, m_tbar_dec); // ttbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttwPartonHistory, m_ttbar_dec);
    // Fill Z parton history
    CalcPartonHistory::FillWPartonHistory(ttwPartonHistory, "", 2, m_W_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
