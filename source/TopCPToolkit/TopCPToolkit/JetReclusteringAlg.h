#pragma once

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODJet/JetAuxContainer.h>
#include <xAODJet/JetContainer.h>

#include "fastjet/ClusterSequence.hh"

#include <memory>
#include <vector>

namespace top {

class JetReclusteringAlg final : public EL::AnaAlgorithm {

public:
  JetReclusteringAlg(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;

private:
  CP::SysListHandle m_systematicsList {this};
  CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
    this, "jets", "", "the jet container to use"
  };
  CP::SysReadSelectionHandle m_jetSelection {
    this, "jetSelection", "", "the selection on the input jets"
  };

  CP::SysWriteDecorHandle<std::vector<int>> m_smallRjetIndicesDecor {
    this, "smallRjetIndices", "smallRjetIndices_%SYS%", "Indices of the small R jets used to build a given RC jet"
  };

  CP::SysWriteDecorHandle<float> m_rcEnergyDecor {
    this, "rcJetEnergy", "e_%SYS%", "Energy of the RC jet"
  };

  // output container
  CP::SysWriteHandle<xAOD::JetContainer, xAOD::JetAuxContainer> m_outHandle {this, "reclusteredJets", "reclusteredJets_%SYS%", "Reclustered jets collection"};

  std::unique_ptr<fastjet::JetDefinition> m_fastjetClustering;

  float m_reclusteredJetsRadius = 1.0;

private:
  StatusCode executeSystematics(const CP::SystematicSet &sys);

  std::vector<int> matchRCjets(const std::vector<const xAOD::Jet*>& smallJets, const std::vector<fastjet::PseudoJet>& constituents) const;
};
}
