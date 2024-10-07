#include "PartonHistory/CalcTtzPartonHistory.h"
#include "PartonHistory/CalcTtbarPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtzPartonHistory::CalcTtzPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

  void CalcTtzPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeAntiTopDecorators();
    CalcPartonHistory::InitializeTtbarDecorators();
    CalcPartonHistory::InitializeZDecorators();
  }

  StatusCode CalcTtzPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttZPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttZPartonHistory, 0, m_t_dec); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttZPartonHistory, 1, m_tbar_dec); // ttbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttZPartonHistory, m_ttbar_dec);
    // Fill Z parton history
    CalcPartonHistory::FillZPartonHistory(ttZPartonHistory, "", m_Z_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
