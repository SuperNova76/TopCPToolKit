#include "TopCPToolkit/VGammaORAlg.h"

namespace top {

  VGammaORAlg::VGammaORAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
  {
    declareProperty("VGammaORTool", m_vgammaORTool, "The VGammaORTool");
  }

  StatusCode VGammaORAlg::initialize() {
    ANA_MSG_INFO("Initialising the VGammaORAlg");

    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));
    ANA_CHECK(m_inOverlapHandle.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode VGammaORAlg::execute() {

    for (const auto &sys : m_systematicsList.systematicsVector()) {
      const xAOD::EventInfo *evtInfo = nullptr;
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

      bool in_vgamma_overlap;
      ANA_CHECK(m_vgammaORTool->inOverlap(in_vgamma_overlap));
      m_inOverlapHandle.set(*evtInfo, in_vgamma_overlap, sys);
    }

    return StatusCode::SUCCESS;
  }

} //namespace top