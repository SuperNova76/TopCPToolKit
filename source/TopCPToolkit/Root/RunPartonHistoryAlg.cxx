#include "TopCPToolkit/RunPartonHistoryAlg.h"

namespace top {
  RunPartonHistoryAlg::RunPartonHistoryAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator),
      m_topPartonScheme("Ttbar")
  {
    declareProperty("topPartonScheme", m_topPartonScheme, "the TopParton history to run");
  }

  StatusCode RunPartonHistoryAlg::initialize() {
    ANA_MSG_INFO("Initializing PartonHistory " << name() );
    ANA_MSG_INFO("  - topPartonScheme: " << m_topPartonScheme);

    if (m_topPartonScheme == "Ttbar") {
      m_topPartonHistory = std::make_unique<CalcTtbarPartonHistory>("top::CalcTtbarPartonHistory");
    }
    else if (m_topPartonScheme == "TtbarLight") {
      m_topPartonHistory = std::make_unique<CalcTtbarLightPartonHistory>("top::CalcTtbarLightPartonHistory");
    }
    else if (m_topPartonScheme == "TTZ") {
      m_topPartonHistory = std::make_unique<CalcTTZPartonHistory>("top::CalcTTZPartonHistory");
    }
    else {
      ANA_MSG_ERROR("  ==> topPartonScheme " << m_topPartonScheme << " is not recognised! aborting.");
      return StatusCode::FAILURE;
    }
    ANA_CHECK(m_topPartonHistory->setProperty("outputSGKey", "TopPartonHistory" + m_topPartonScheme + "_NOSYS"));

    return StatusCode::SUCCESS;
  }

  StatusCode RunPartonHistoryAlg::execute() {

    ANA_CHECK(m_topPartonHistory->execute());

    return StatusCode::SUCCESS;
  }

  StatusCode RunPartonHistoryAlg::finalize() {
    ANA_MSG_INFO("Finalizing PartonHistory");

    return StatusCode::SUCCESS;
  }

} // namespace top
