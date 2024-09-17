#include "PartonHistory/CalcTzqPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTzqPartonHistory::CalcTzqPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

  void CalcTzqPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeBottomDecorators();
    CalcPartonHistory::InitializeZDecorators();
  }

  StatusCode CalcTzqPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* tzqPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();
    CalcPartonHistory::EnsurebbbarKeysExist();
    CalcPartonHistory::EnsureZKeysExist();

    // Fill top parton history (flavour agnostic)
    CalcPartonHistory::FillTopPartonHistory(tzqPartonHistory, 2, m_t_dec);
    // Fill b (spectator b) parton history (flavour agnostic)
    CalcPartonHistory::FillBottomPartonHistory(tzqPartonHistory, "", 2, m_b_dec);
    // Fill Z parton history
    CalcPartonHistory::FillZPartonHistory(tzqPartonHistory, "", m_Z_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
