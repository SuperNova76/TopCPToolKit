#ifndef TOP_PARTICLELEVELALG_H
#define TOP_PARTICLELEVELALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>

#include <vector>

// EDM include(s):
#include "AthContainers/AuxElement.h"
#include "AthContainers/DataVector.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/CLASS_DEF.h"

// TopParticleLevel
#include "MCTruthClassifier/MCTruthClassifierDefs.h"
#include "TopParticleLevel/ParticleLevel.h"
#include "xAODJet/Jet.h"
#include "xAODJet/JetAuxContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODMissingET/MissingET.h"
#include "xAODMissingET/MissingETAuxContainer.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthParticleAuxContainer.h"
#include "xAODTruth/TruthParticleContainer.h"

namespace top {

  class ParticleLevelAlg final : public EL::AnaAlgorithm {

  public:
    ParticleLevelAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

  private:
    std::string outputSGKey;
    StatusCode save;
    StatusCode saveAux;

    const bool m_useTruthElectrons, m_useTruthMuons, m_useTruthPhotons,
      m_useTruthTaus, m_useTruthJets, m_useTruthLargeRJets, m_useTruthMET,
      m_doOverlapRemoval;
    const float m_el_ptMin, m_el_etaMax;
    const bool m_el_notFromHadron, m_el_tauIsHadron;
    const float m_mu_ptMin, m_mu_etaMax;
    const bool m_mu_notFromHadron, m_mu_tauIsHadron;
    const float m_ph_ptMin, m_ph_etaMax;
    const std::string m_ph_origin, m_ph_isolation;
    const float m_tau_ptMin, m_tau_etaMax;
    const float m_jet_ptMin, m_jet_etaMax;
    const float m_ljet_ptMin, m_ljet_etaMax;
    const std::string m_ljet_collection;

    const xAOD::TruthParticleContainer *inputElectrons, *inputMuons,
      *inputPhotons, *inputTaus;
    xAOD::TruthParticleContainer *outputElectrons, *outputMuons, *outputPhotons,
      *outputTaus;
    xAOD::TruthParticleAuxContainer *outputElectronsAux, *outputMuonsAux,
      *outputPhotonsAux, *outputTausAux;

    const xAOD::JetContainer *inputJets, *inputLargeRJets;
    xAOD::JetContainer *outputJets, *outputLargeRJets;
    xAOD::JetAuxContainer *outputJetsAux, *outputLargeRJetsAux;

    const xAOD::MissingETContainer *inputMissingET;
    xAOD::MissingETContainer *outputMissingET;
    xAOD::MissingETAuxContainer *outputMissingETAux;

    std::vector<MCTruthPartClassifier::ParticleOrigin> photon_origins;
    std::string photon_isolationVar;
    float photon_isolationCut;

    const xAOD::EventInfo *evtInfo;
  };

}  // namespace top

#endif
