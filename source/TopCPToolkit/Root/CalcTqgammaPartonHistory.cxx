#include "PartonHistory/CalcTqgammaPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTqgammaPartonHistory::CalcTqgammaPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTqgammaPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* tqgammaPartonHistory) {
    // Initialising truth variables with dummy values
    tqgammaPartonHistory->IniVarTqGamma();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist(); // this will fail on ttbar but that is ok.
    
    // Fill top parton history (flavour agnostic)
    CalcPartonHistory::FillTopPartonHistory(tqgammaPartonHistory, 2);
    // Fill b (spectator b) parton history (flavour agnostic)
    CalcPartonHistory::FillBottomPartonHistory(tqgammaPartonHistory, "", 2);
    // Fill Gamma parton history
    CalcPartonHistory::FillGammaPartonHistory(tqgammaPartonHistory, "");

    return StatusCode::SUCCESS;
  }

} // namespace top
