#include "TopSpaNet/TopologyBase.h"

namespace top {

  TopSpaNetTopology::TopSpaNetTopology(const std::string& name, const std::string& model_even, const std::string& model_odd) :
    ONNXWrapper(name, {model_even, model_odd}),
    m_NUM_FEATURES(-1),
    m_MAX_JETS(-1),
    m_NUM_JET_FEATURES(-1),
    m_MAX_LEPTONS(-1),
    m_NUM_LEPTON_FEATURES(-1),
    m_MAX_GLOBALS(-1),
    m_NUM_GLOBAL_FEATURES(-1)
  {
  }

  unsigned TopSpaNetTopology::getSessionIndex(unsigned long long eventNumber) {
    // m_sessions = {model_trained_on_even, model_trained_on_odd}
    return (eventNumber+1) % 2;
  }

} // namespace top
