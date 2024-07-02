#include "PartonHistory/CalcTtbarPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
  CalcTtbarPartonHistory::CalcTtbarPartonHistory(const std::string& name,
                                                 const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcTtbarPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttbarPartonHistory) {
    // Initialising truth variables with dummy values
    ttbarPartonHistory->IniVarTtbar();
    // Tracing truth particles
    CalcPartonHistory::TraceParticles(truthParticles);
    CalcPartonHistory::EnsureKeyExists("MC_t_Wp_afterFSR", "MC_t_Wp");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_Wm_afterFSR", "MC_tbar_Wm");
    CalcPartonHistory::EnsureKeyExists("MC_t_Wp_beforeFSR", "MC_t_Wp_afterFSR");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_Wm_beforeFSR", "MC_tbar_Wm_afterFSR");
    CalcPartonHistory::EnsureKeyExists("MC_t_afterFSR", "MC_t");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_afterFSR", "MC_tbar");
    CalcPartonHistory::EnsureKeyExists("MC_t_beforeFSR", "MC_t_afterFSR");
    CalcPartonHistory::EnsureKeyExists("MC_tbar_beforeFSR", "MC_tbar_afterFSR");

    // Ensuring the necessary keys exist
    CalcPartonHistory::EnsureTtbarKeysExist();

    // Fill top parton history
    CalcPartonHistory::FillTopPartonHistory(ttbarPartonHistory);
    // Fill anti top parton history
    CalcPartonHistory::FillAntiTopPartonHistory(ttbarPartonHistory);
    // Fill ttbar parton history
    CalcPartonHistory::FillTtbarPartonHistory(ttbarPartonHistory);

    return StatusCode::SUCCESS;
  }

} // namespace top
