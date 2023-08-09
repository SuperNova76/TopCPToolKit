#include "TopCPToolkit/EventSelectionTestAlg.h"
#include <SystematicsHandles/SysFilterReporter.h>
#include <SystematicsHandles/SysFilterReporterCombiner.h>

namespace top {
  EventSelectionTestAlg::EventSelectionTestAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
  }

  StatusCode EventSelectionTestAlg::initialize() {

    ANA_CHECK(m_filterParams.initialize(m_systematicsList));

    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));
    ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));

    ANA_CHECK(m_bTagDecision.initialize(m_systematicsList, m_jetsHandle));
    ANA_CHECK(m_eljetsDecision.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_mujetsDecision.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode EventSelectionTestAlg::execute() {

    CP::SysFilterReporterCombiner filterCombiner(m_filterParams, false);

    for (const auto& syst : m_systematicsList.systematicsVector()) {
      CP::SysFilterReporter filter(filterCombiner, syst);

      const xAOD::EventInfo *evtInfo {nullptr};
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, syst));
      m_eljetsDecision.set(*evtInfo, 0, syst);
      m_mujetsDecision.set(*evtInfo, 0, syst);

      // exactly one electron or muon, depending on the LeptonChannel property
      const xAOD::ElectronContainer *electrons {nullptr};
      ANA_CHECK(m_electronsHandle.retrieve(electrons, syst));
      size_t iel {0};
      for (const xAOD::Electron *el : *electrons) {
        if (m_electronSelection.getBool(*el, syst))
          ++iel;
      }
      const xAOD::MuonContainer *muons {nullptr};
      ANA_CHECK(m_muonsHandle.retrieve(muons, syst));
      size_t imu {0};
      for (const xAOD::Muon *mu : *muons) {
        if (m_muonSelection.getBool(*mu, syst))
          ++imu;
      }
      bool is_el {false}, is_mu {false};

      if (iel == 1 && imu == 0)
        is_el = true;
      else if (iel == 0 && imu == 1)
        is_mu = true;
      
      // at least 4 jets with pT > 25 GeV
      // at least two b-tags
      const xAOD::JetContainer *jets {nullptr};
      ANA_CHECK(m_jetsHandle.retrieve(jets, syst));
      size_t ijets {0}, ibjets {0};
      for (const xAOD::Jet *jet : *jets) {
        if (m_jetSelection.getBool(*jet, syst) && jet->pt() > 25e3) {
          ++ijets;
          if (m_bTagDecision.get(*jet, syst))
            ++ibjets;
        }
      }
      if (ijets < 4)
        continue;
      
      if (ibjets < 2)
        continue;

      m_eljetsDecision.set(*evtInfo, is_el, syst);
      m_mujetsDecision.set(*evtInfo, is_mu, syst);

      if (!is_el && !is_mu)
        continue;

      filter.setPassed();
    }
    return StatusCode::SUCCESS;
  }

  StatusCode EventSelectionTestAlg::finalize() {
    ANA_CHECK(m_filterParams.finalize());
    return StatusCode::SUCCESS;
  }

} // namespace top
