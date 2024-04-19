#include "TopCPToolkit/LeptonSFCalculatorAlg.h"

namespace top {
  LeptonSFCalculatorAlg::LeptonSFCalculatorAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
  }

  StatusCode LeptonSFCalculatorAlg::initialize() {

    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList, SG::AllowEmpty));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList, SG::AllowEmpty));
    ANA_CHECK(m_photonsHandle.initialize(m_systematicsList, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));
    ANA_CHECK(m_photonSelection.initialize(m_systematicsList, m_photonsHandle, SG::AllowEmpty));

    ANA_CHECK(m_electronRecoSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_electronIDSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_electronIsolSF.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_muonRecoSF.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_muonIsolSF.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_muonTTVASF.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_photonIDSF.initialize(m_systematicsList, m_photonsHandle));
    ANA_CHECK(m_photonIsolSF.initialize(m_systematicsList, m_photonsHandle));

    ANA_CHECK(m_event_leptonSF.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode LeptonSFCalculatorAlg::execute() {
    for (const auto& syst : m_systematicsList.systematicsVector()) {
      const xAOD::EventInfo *evtInfo {nullptr};
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, syst));

      const xAOD::ElectronContainer *electrons {nullptr};
      if (m_electronsHandle) ANA_CHECK(m_electronsHandle.retrieve(electrons, syst));

      const xAOD::MuonContainer *muons {nullptr};
      if (m_muonsHandle) ANA_CHECK(m_muonsHandle.retrieve(muons, syst));

      const xAOD::PhotonContainer *photons {nullptr};
      if (m_photonsHandle) ANA_CHECK(m_photonsHandle.retrieve(photons, syst));

      double leptonSF {1.};
      if (m_electronsHandle){
	for (const xAOD::Electron *el : *electrons) {
	  if (m_electronSelection.getBool(*el, syst)) {
	    leptonSF *= m_electronRecoSF.get(*el, syst);
	    leptonSF *= m_electronIDSF.get(*el, syst);
	    leptonSF *= m_electronIsolSF.get(*el, syst);
	  }
	}
      }
      if (m_muonsHandle){
	for (const xAOD::Muon *mu : *muons) {
	  if (m_muonSelection.getBool(*mu, syst)) {
	    leptonSF *= m_muonRecoSF.get(*mu, syst);
	    leptonSF *= m_muonIsolSF.get(*mu, syst);
          leptonSF *= m_muonTTVASF.get(*mu, syst);
	  }
	}
      }
      if (m_photonsHandle){
	for (const xAOD::Photon *ph : *photons) {
	  if (m_photonSelection.getBool(*ph, syst)) {
	    leptonSF *= m_photonIDSF.get(*ph, syst);
	    leptonSF *= m_photonIsolSF.get(*ph, syst);
	  }
	}
      }

      m_event_leptonSF.set(*evtInfo, leptonSF, syst);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode LeptonSFCalculatorAlg::finalize() {
    return StatusCode::SUCCESS;
  }
}
