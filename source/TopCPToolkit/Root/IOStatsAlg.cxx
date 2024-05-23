#include "TopCPToolkit/IOStatsAlg.h"

#include "xAODCore/tools/IOStats.h"
#include "xAODCore/tools/ReadStats.h"

namespace top {

  IOStatsAlg::IOStatsAlg(const std::string& name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    {
      declareProperty("autoIncludeLinks", m_autoIncludeLinks, "If or not add all ElementLink variables");
    }

  StatusCode IOStatsAlg::finalize() {

    xAOD::IOStats::instance().stats().printSmartSlimmingBranchList(m_autoIncludeLinks);

    return StatusCode::SUCCESS;
  }

} // namespace top