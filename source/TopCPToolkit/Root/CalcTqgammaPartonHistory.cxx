#include "PartonHistory/CalcTqgammaPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTqgammaPartonHistory::CalcTqgammaPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {
    initializeDecorators();
  }

  void CalcTqgammaPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeBottomDecorators();
    CalcPartonHistory::InitializePhotonDecorators();
  }

  StatusCode CalcTqgammaPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
						       xAOD::PartonHistory* tqgammaPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();
    CalcPartonHistory::EnsurebbbarKeysExist();

    // Fill top parton history (flavour agnostic)
    CalcPartonHistory::FillTopPartonHistory(tqgammaPartonHistory, 2, m_t_dec);
    // Fill b (spectator b) parton history (flavour agnostic)
    CalcPartonHistory::FillBottomPartonHistory(tqgammaPartonHistory, "", 2, m_b_dec);
    // Fill Gamma parton history
    CalcPartonHistory::FillGammaPartonHistory(tqgammaPartonHistory, "", m_gamma_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
