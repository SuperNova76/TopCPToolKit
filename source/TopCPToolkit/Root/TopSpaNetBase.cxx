#include "TopSpaNet/TopologyBase.h"

namespace top {

  TopSpaNetTopology::TopSpaNetTopology(const std::string& name, std::string model_even, std::string model_odd) :
    ONNXWrapper(name, {model_even, model_odd})
  {
    m_MAX_JETS = m_input_shapes[0][1]; // TODO: Fix this when we fix the batching thing
    m_NUM_FEATURES = m_input_shapes[0][2];
  }

  unsigned TopSpaNetTopology::getSessionIndex(unsigned long long eventNumber) {
    // m_sessions = {model_trained_on_even, model_trained_on_odd}
    return (eventNumber+1) % 2;
  }

} // namespace top
