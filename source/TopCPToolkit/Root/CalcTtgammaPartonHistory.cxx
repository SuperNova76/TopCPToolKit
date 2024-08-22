#include "PartonHistory/CalcTtgammaPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtgammaPartonHistory::CalcTtgammaPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTtgammaPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttgammaPartonHistory) {
    // Initialising truth variables with dummy values
    ttgammaPartonHistory->IniVarTtGamma();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttgammaPartonHistory, 0); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttgammaPartonHistory, 1); // tbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttgammaPartonHistory);
    // Fill photon parton history
    CalcPartonHistory::FillGammaPartonHistory(ttgammaPartonHistory, "");

    return StatusCode::SUCCESS;
  }

} // namespace top
