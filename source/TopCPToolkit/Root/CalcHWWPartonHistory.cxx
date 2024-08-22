#include "PartonHistory/CalcHWWPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  CalcHWWPartonHistory::CalcHWWPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
  {}

  StatusCode CalcHWWPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
						   xAOD::PartonHistory* hwwPartonHistory) {
    hwwPartonHistory->IniVarHWW();
    CalcPartonHistory::TraceParticles(truthParticles);
    CalcPartonHistory::FillHiggsPartonHistory(hwwPartonHistory);

    return StatusCode::SUCCESS;
  }

} // namespace top
