#include "TopCPToolkit/ExtraPhotonDecorationAlg.h"

namespace top {

  ExtraPhotonDecorationAlg::ExtraPhotonDecorationAlg(const std::string &name, ISvcLocator *pSvcLocator) : EL::AnaAlgorithm(name, pSvcLocator) {}
  
  StatusCode ExtraPhotonDecorationAlg::initialize() {
    ANA_MSG_INFO("Initialising the algorithm for the TopCPToolkit ExtraPhotonDecorationAlg");

    ANA_CHECK(m_photonsHandle.initialize(m_systematicsList));

    ANA_CHECK(m_conversionTypeHandle.initialize(m_systematicsList, m_photonsHandle));
    ANA_CHECK(m_caloEtaHandle.initialize(m_systematicsList, m_photonsHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode ExtraPhotonDecorationAlg::execute() {
    for (const auto &sys : m_systematicsList.systematicsVector()) {
      const xAOD::PhotonContainer *photons = nullptr;

      ANA_CHECK(m_photonsHandle.retrieve(photons, sys));

      for (const xAOD::Photon *photon : *photons) {
        int conversionType = photon->conversionType();
        m_conversionTypeHandle.set(*photon, conversionType, sys);

        float caloEta = photon->caloCluster()->etaBE(2);
        m_caloEtaHandle.set(*photon, caloEta, sys);
      }
    }

    return StatusCode::SUCCESS;
  }

} //namespace top