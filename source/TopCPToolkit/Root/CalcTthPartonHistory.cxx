#include "PartonHistory/CalcTthPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
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
