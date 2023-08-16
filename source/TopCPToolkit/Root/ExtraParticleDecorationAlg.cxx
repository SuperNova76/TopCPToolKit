#include "TopCPToolkit/ExtraParticleDecorationAlg.h"

namespace top {
ExtraParticleDecorationAlg::ExtraParticleDecorationAlg(const std::string &name,
                                                       ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {
}

StatusCode ExtraParticleDecorationAlg::initialize() {
  ANA_MSG_INFO("Initializing");

  ANA_CHECK(m_particlesHandle.initialize (m_systematicsList));
  ANA_CHECK(m_energyDecor.initialize (m_systematicsList, m_particlesHandle));
  ANA_CHECK(m_systematicsList.initialize());

  return StatusCode::SUCCESS;
}

StatusCode ExtraParticleDecorationAlg::execute() {

  for (const auto &sys : m_systematicsList.systematicsVector()) {

    const xAOD::IParticleContainer *particles = nullptr;
    ANA_CHECK(m_particlesHandle.retrieve (particles, sys));

    for (const xAOD::IParticle *particle : *particles) {
      m_energyDecor.set(*particle, particle->e(), sys);
    }

  }

  return StatusCode::SUCCESS;
}

StatusCode ExtraParticleDecorationAlg::finalize() { return StatusCode::SUCCESS; }
} // namespace top
