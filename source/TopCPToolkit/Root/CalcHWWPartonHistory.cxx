#include "PartonHistory/CalcHWWPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
  CalcHWWPartonHistory::CalcHWWPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcHWWPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
						   xAOD::PartonHistory* hwwPartonHistory) {
    hwwPartonHistory->IniVarHWW();
    CalcPartonHistory::TraceParticles(truthParticles);
    CalcPartonHistory::FillHiggsPartonHistory(hwwPartonHistory);
    CalcPartonHistory::FillWpPartonHistory(hwwPartonHistory, "H");
    CalcPartonHistory::FillWmPartonHistory(hwwPartonHistory, "H");
    
    return StatusCode::SUCCESS;
  }

} // namespace top
