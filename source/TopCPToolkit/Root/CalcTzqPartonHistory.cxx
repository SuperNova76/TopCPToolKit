#include "PartonHistory/CalcTzqPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTzqPartonHistory::CalcTzqPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTzqPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* tzqPartonHistory) {
    // Initialising truth variables with dummy values
    tzqPartonHistory->IniVarTzq();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist(); // this will fail on ttbar but that is ok.
    CalcPartonHistory::EnsureKeyExists("MC_Z_afterFSR", "MC_Z");
    CalcPartonHistory::EnsureKeyExists("MC_Z_beforeFSR", "MC_Z_afterFSR");

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(tzqPartonHistory);
    // Fill anti top parton history
    CalcPartonHistory::FillAntiTopPartonHistory(tzqPartonHistory);
    // Fill b parton history
    CalcPartonHistory::FillBottomPartonHistory(tzqPartonHistory, "");
    // Fill bbar parton history
    CalcPartonHistory::FillAntiBottomPartonHistory(tzqPartonHistory, "");
    // Fill Z parton history
    CalcPartonHistory::FillZPartonHistory(tzqPartonHistory, "");

    return StatusCode::SUCCESS;
  }

} // namespace top
