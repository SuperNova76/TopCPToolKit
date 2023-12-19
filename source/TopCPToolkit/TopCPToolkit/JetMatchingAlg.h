#ifndef TOP_JET_MATCHING_ALGORITHM_H
#define TOP_JET_MATCHING_ALGORITHM_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>
#include <xAODMissingET/MissingETContainer.h>
#include <xAODEventInfo/EventInfo.h>

namespace top {

  class JetMatchingAlg final : public EL::AnaAlgorithm {

  public:
    JetMatchingAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;

  private: 
    //systematics
    CP::SysListHandle m_systematicsList {this};
    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"
    };
    CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
      this, "jets", "", "the jet container to use"
    };
    CP::SysReadHandle<xAOD::JetContainer> m_truthJetsHandle {
      this, "truthJets", "", "the truthjet container to use"
    };
    CP::SysReadSelectionHandle m_jetSelection {
      this, "jetSelection", "", "the selection on the input jets"
    };
    CP::SysReadSelectionHandle m_selection {
      this, "eventSelection", "", "Name of the selection on which this JetMatching instance is allowed to run"
    };
    
    //output decorations
    CP::SysWriteDecorHandle<int> m_truth_jet_paired_index {
      this, "truth_jet_paired_index", "truth_jet_paired_index_%SYS%", "Index of the matched true jet"
    };
    CP::SysWriteDecorHandle<float> m_reco_to_reco_jet_closest_dR {
      this, "reco_to_reco_jet_closest_dR", "reco_to_reco_jet_closest_dR_%SYS%", "dR of the closest reco jet"
    };
    CP::SysWriteDecorHandle<float> m_truth_to_truth_jet_closest_dR {
      this, "truth_to_truth_jet_closest_dR", "truth_to_truth_jet_closest_dR_%SYS%", "dR between the matched truth jet and its closest truth jet"
    };
    
    float m_criticalDR = 0.3;
    
    float get_minDR_reco(TLorentzVector jet1, unsigned int ijet1, ConstDataVector<xAOD::JetContainer> selected_jets);
    float get_minDR_truth(const xAOD::JetContainer &truth_jets, int truth_jet_index);
    int get_matched_truth(TLorentzVector reco_jet, const xAOD::JetContainer &truth_jets);
    
  };

} // namespace top

#endif
