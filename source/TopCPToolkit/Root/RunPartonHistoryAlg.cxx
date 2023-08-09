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
      m_topPartonHistory = std::unique_ptr<top::CalcTopPartonHistory> (new top::CalcTtbarPartonHistory("top::CalcTtbarPartonHistory"));
    }
    else if (m_topPartonScheme == "TtbarLight") {
      m_topPartonHistory = std::unique_ptr<top::CalcTopPartonHistory> (new top::CalcTtbarLightPartonHistory("top::CalcTtbarLightPartonHistory"));
    }
    else if (m_topPartonScheme == "TTZ") {
      m_topPartonHistory = std::unique_ptr<top::CalcTopPartonHistory> (new top::CalcTTZPartonHistory("top::CalcTTZPartonHistory"));
    }
    else {
      ANA_MSG_ERROR("  ==> topPartonScheme " << m_topPartonScheme << " is not recognised! aborting.");
      return StatusCode::FAILURE;
    }

    return StatusCode::SUCCESS;
  }

  StatusCode RunPartonHistoryAlg::execute() {

    ATH_CHECK(m_topPartonHistory->execute());

    return StatusCode::SUCCESS;
  }

  StatusCode RunPartonHistoryAlg::finalize() {
    ANA_MSG_INFO("Finalizing PartonHistory");

    return StatusCode::SUCCESS;
  }

} // namespace top
