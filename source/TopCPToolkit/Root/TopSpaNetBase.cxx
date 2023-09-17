#include "TopSpaNet/TopologyBase.h"

namespace top {

  TopSpaNetTopology::TopSpaNetTopology(const std::string& name, std::string model_even, std::string model_odd) :
    ONNXWrapper(name, {model_even, model_odd})
  {
  }

  unsigned TopSpaNetTopology::getSessionIndex(unsigned long long eventNumber) {
    // m_sessions = {model_trained_on_even, model_trained_on_odd}
    return (eventNumber+1) % 2;
  }

} // namespace top
