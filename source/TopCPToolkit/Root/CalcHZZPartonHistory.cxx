#include "PartonHistory/CalcHZZPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi;
  CalcHZZPartonHistory::CalcHZZPartonHistory(const std::string& name,
					     const std::vector<std::string>& truthCollections) :
    CalcPartonHistory(name, truthCollections)
    {}

  StatusCode CalcHZZPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
						   xAOD::PartonHistory* hzzPartonHistory) {
    hzzPartonHistory->IniVarHZZ();
    CalcPartonHistory::TraceParticles(truthParticles);
    CalcPartonHistory::FillHiggsPartonHistory(hzzPartonHistory);
    CalcPartonHistory::FillZPartonHistory(hzzPartonHistory, "H", 1);
    CalcPartonHistory::FillZPartonHistory(hzzPartonHistory, "H", 2);
    
    return StatusCode::SUCCESS;
  }

} // namespace top
