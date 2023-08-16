#include "TopCPToolkit/TtbarCPalgoAnalysis.h"

namespace top {
TtbarCPalgoAnalysis::TtbarCPalgoAnalysis(const std::string &name,
                                         ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
}

StatusCode TtbarCPalgoAnalysis::initialize() {
  ANA_MSG_INFO("Initializing");

  // ANA_CHECK(m_electronsHandle.initialize (m_systematicsListElectrons));
  // ANA_CHECK(m_muonsHandle.initialize (m_systematicsListMuons));
  // ANA_CHECK(m_jetsHandle.initialize (m_systematicsListJets));

  // ANA_CHECK(m_electronsEnergyDecor.initialize (m_systematicsListElectrons, m_electronsHandle));
  // ANA_CHECK(m_muonsEnergyDecor.initialize (m_systematicsListMuons, m_muonsHandle));
  // ANA_CHECK(m_jetsEnergyDecor.initialize (m_systematicsListJets, m_jetsHandle));

  // ANA_CHECK(m_systematicsListElectrons.initialize());
  // ANA_CHECK(m_systematicsListMuons.initialize());
  // ANA_CHECK(m_systematicsListJets.initialize());

  ANA_CHECK(m_particlesHandle.initialize (m_systematicsList));
  ANA_CHECK(m_energyDecor.initialize (m_systematicsList, m_particlesHandle));
  ANA_CHECK(m_systematicsList.initialize());

  return StatusCode::SUCCESS;
}

StatusCode TtbarCPalgoAnalysis::execute() {

  for (const auto &sys : m_systematicsList.systematicsVector()) {

    const xAOD::IParticleContainer *particles = nullptr;
    ANA_CHECK(m_particlesHandle.retrieve (particles, sys));

    for (const xAOD::IParticle *particle : *particles) {
      m_energyDecor.set(*particle, particle->e(), sys);
    }

  }

  // for (const auto &sys : m_systematicsListElectrons.systematicsVector()) {

  //   const xAOD::ElectronContainer *electrons = nullptr;
  //   ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));

  //   // user-friendly loose electron decorations
  //   for (const xAOD::Electron *electron: *electrons) {
  //     m_electronsEnergyDecor.set(*electron, electron->e(), sys);
  //   }

  // }

  // for (const auto &sys : m_systematicsListMuons.systematicsVector()) {

  //   const xAOD::MuonContainer *muons = nullptr;
  //   ANA_CHECK(m_muonsHandle.retrieve(muons, sys));

  //   // user-friendly loose muon decorations
  //   for (const xAOD::Muon *muon : *muons) {
  //     m_muonsEnergyDecor.set(*muon, muon->e(), sys);
  //   }

  // }

  // for (const auto &sys : m_systematicsListJets.systematicsVector()) {

  //   const xAOD::JetContainer *jets = nullptr;
  //   ANA_CHECK(m_jetsHandle.retrieve(jets, sys));

  //   // user-friendly jet decorations
  //   for (const xAOD::Jet *jet : *jets) {
  //     m_jetsEnergyDecor.set(*jet, jet->e(), sys);
  //   }

  // }

  return StatusCode::SUCCESS;
}

StatusCode TtbarCPalgoAnalysis::finalize() { return StatusCode::SUCCESS; }
} // namespace top
