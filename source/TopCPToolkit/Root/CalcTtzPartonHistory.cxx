#include "PartonHistory/CalcTtzPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTtzPartonHistory::CalcTtzPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTtzPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttZPartonHistory) {
    // Initialising truth variables with dummy values
    ttZPartonHistory->IniVarTtbar();
    ttZPartonHistory->IniVarZ();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();
    CalcPartonHistory::EnsureKeyExists("MC_Z_afterFSR", "MC_Z");
    CalcPartonHistory::EnsureKeyExists("MC_Z_beforeFSR", "MC_Z_afterFSR");

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttZPartonHistory, 0); // t mode
    // Fill anti top parton history
    CalcPartonHistory::FillTopPartonHistory(ttZPartonHistory, 1); // ttbar mode
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttZPartonHistory);
    // Fill Z parton history
    CalcPartonHistory::FillZPartonHistory(ttZPartonHistory, "");

    return StatusCode::SUCCESS;
  }

} // namespace top
