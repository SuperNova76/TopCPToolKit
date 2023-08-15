#include "TopCPToolkit/TtbarCPalgoAnalysis.h"

namespace top {
TtbarCPalgoAnalysis::TtbarCPalgoAnalysis(const std::string &name,
                                         ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
}

StatusCode TtbarCPalgoAnalysis::initialize() {
  ANA_MSG_INFO("Initializing");

  ANA_CHECK(m_electronsHandle.initialize (m_systematicsList));
  ANA_CHECK(m_muonsHandle.initialize (m_systematicsList));
  ANA_CHECK(m_jetsHandle.initialize (m_systematicsList));
  ANA_CHECK(m_systematicsList.initialize());

  return StatusCode::SUCCESS;
}

StatusCode TtbarCPalgoAnalysis::execute() {

  for (const auto &sys : m_systematicsList.systematicsVector()) {

    // retrieve all relevant containers
    const xAOD::ElectronContainer *electrons = nullptr;
    ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
    const xAOD::MuonContainer *muons = nullptr;
    ANA_CHECK(m_muonsHandle.retrieve(muons, sys));
    const xAOD::JetContainer *jets = nullptr;
    ANA_CHECK(m_jetsHandle.retrieve(jets, sys));

    // generic decorators
    static const SG::AuxElement::Decorator<float>  dec_energy("e");

    // user-friendly loose electron decorations
    for (const xAOD::Electron *electron: *electrons) {
        dec_energy(*electron) = electron->e();
    }

    // user-friendly loose muon decorations
    for (const xAOD::Muon *muon : *muons) {
      dec_energy(*muon) = muon->e();
    }

    // user-friendly jet decorations
    for (const xAOD::Jet *jet : *jets) {
      dec_energy(*jet) = jet->e();
    }
  }

  return StatusCode::SUCCESS;
}

StatusCode TtbarCPalgoAnalysis::finalize() { return StatusCode::SUCCESS; }
} // namespace top
