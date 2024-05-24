#include "TopCPToolkit/IOStatsAlg.h"

#include "xAODCore/tools/IOStats.h"
#include "xAODCore/tools/ReadStats.h"

namespace top {


  StatusCode IOStatsAlg::finalize() {

    xAOD::IOStats::instance().stats().printSmartSlimmingBranchList(m_autoIncludeLinks);

    return StatusCode::SUCCESS;
  }

} // namespace top