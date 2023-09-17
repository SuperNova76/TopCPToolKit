#ifndef TOPSPANET_TOPOLOGY_TTBARLJETS_H
#define TOPSPANET_TOPOLOGY_TTBARLJETS_H

// SpaNet includes
#include "TopSpaNet/TopologyBase.h"

namespace top {
  class TopSpaNetTtbarLjets: public TopSpaNetTopology {
    using TopSpaNetTopology::TopSpaNetTopology;
  public:
    TopSpaNetTtbarLjets();

    virtual void Predict(ConstDataVector<xAOD::ElectronContainer>& electrons,
			 ConstDataVector<xAOD::MuonContainer>& muons,
			 ConstDataVector<xAOD::JetContainer>& jets,
			 float met_met, float met_phi,
			 unsigned long long eventNumber)
      override;

    virtual std::vector<int> GetOutputIndices() override;
    virtual std::vector<float> GetOutputScores() override;

    TLorentzVector getNeutrino(TLorentzVector lepton, const float met_met, const float met_phi);

    // best indices
    int m_lep_b;
    int m_had_b;
    int m_down;
    int m_up;

    // reconstruction scores
    float m_hadtop_assignment;
    float m_leptop_assignment;
    float m_hadtop_detection;
    float m_leptop_detection;

    // preliminary computation of the leptonic W boson
    TLorentzVector m_lepton;
    int m_lep_charge;
    TLorentzVector m_neutrino;

  };
} // namespace top

#endif
