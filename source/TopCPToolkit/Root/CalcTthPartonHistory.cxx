#include "PartonHistory/CalcTthPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcTthPartonHistory::CalcTthPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTthPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* tthPartonHistory) {
    // Initialising truth variables with dummy values
    tthPartonHistory->IniVarTth();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);
    CalcPartonHistory::EnsureKeyExists("MC_t_afterFSR", "MC_t");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_afterFSR", "MC_tbar");
    CalcPartonHistory::EnsureKeyExists("MC_t_beforeFSR", "MC_t_afterFSR");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_beforeFSR", "MC_tbar_afterFSR");

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(tthPartonHistory);
    // Fill anti top parton history
    CalcPartonHistory::FillAntiTopPartonHistory(tthPartonHistory);
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(tthPartonHistory);
    // Fill Higgs parton history
    CalcPartonHistory::FillHiggsPartonHistory(tthPartonHistory);

    return StatusCode::SUCCESS;
  }

} // namespace top
