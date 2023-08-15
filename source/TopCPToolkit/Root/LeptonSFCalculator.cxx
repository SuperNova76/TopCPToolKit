#include "TopCPToolkit/LeptonSFCalculator.h"

namespace top {
  LeptonSFCalculator::LeptonSFCalculator(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
  }

  StatusCode LeptonSFCalculator::initialize() {

    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle));

    ANA_CHECK(m_electronRecoSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_electronIDSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_electronIsolSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_muonRecoSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_muonIsolSF.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_muonTTVASF.initialize(m_systematicsList, m_muonsHandle));

    ANA_CHECK(m_event_leptonSF.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode LeptonSFCalculator::execute() {
    for (const auto& syst : m_systematicsList.systematicsVector()) {
      const xAOD::EventInfo *evtInfo {nullptr};
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, syst));

      const xAOD::ElectronContainer *electrons {nullptr};
      ANA_CHECK(m_electronsHandle.retrieve(electrons, syst));

      const xAOD::MuonContainer *muons {nullptr};
      ANA_CHECK(m_muonsHandle.retrieve(muons, syst));

      double leptonSF {1.};
      for (const xAOD::Electron *el : *electrons) {
        if (m_electronSelection.getBool(*el, syst)) {
          leptonSF *= m_electronRecoSF.get(*el, syst);
          leptonSF *= m_electronIDSF.get(*el, syst);
          leptonSF *= m_electronIsolSF.get(*el, syst);
        }
      }
      for (const xAOD::Muon *mu : *muons) {
        if (m_muonSelection.getBool(*mu, syst))
          leptonSF *= m_muonRecoSF.get(*mu, syst);
          leptonSF *= m_muonIsolSF.get(*mu, syst);
          leptonSF *= m_muonTTVASF.get(*mu, syst);
      }

      m_event_leptonSF.set(*evtInfo, leptonSF, syst);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode LeptonSFCalculator::finalize() {
    return StatusCode::SUCCESS;
  }
}
