#include "PartonHistory/CalcTtgammaPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtgammaPartonHistory::CalcTtgammaPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {
      initializeDecorators();
    }

  void CalcTtgammaPartonHistory::initializeDecorators() {
    CalcPartonHistory::InitializeTopDecorators();
    CalcPartonHistory::InitializeAntiTopDecorators();
    CalcPartonHistory::InitializeTtbarDecorators();
    CalcPartonHistory::InitializePhotonDecorators();
  }

  StatusCode CalcTtgammaPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttgammaPartonHistory) {
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttgammaPartonHistory, 0, m_t_dec); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttgammaPartonHistory, 1, m_tbar_dec); // tbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttgammaPartonHistory, m_ttbar_dec);
    // Fill photon parton history
    CalcPartonHistory::FillGammaPartonHistory(ttgammaPartonHistory, "", m_gamma_dec);

    return StatusCode::SUCCESS;
  }

} // namespace top
