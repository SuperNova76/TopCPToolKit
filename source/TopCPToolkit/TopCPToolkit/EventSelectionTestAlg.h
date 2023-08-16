#ifndef TOPCPTOOLKIT_EVENTSELECTIONTESTALG_H_
#define TOPCPTOOLKIT_EVENTSELECTIONTESTALG_H_

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <SystematicsHandles/SysFilterReporterParams.h>

#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>
#include <xAODMissingET/MissingETContainer.h>

namespace top {
  class EventSelectionTestAlg : public EL::AnaAlgorithm {

  public:
    EventSelectionTestAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() final;
    virtual StatusCode execute() final;
    virtual StatusCode finalize() final;

  private:
    // systematics
    CP::SysListHandle m_systematicsList {this};

    CP::SysFilterReporterParams m_filterParams {this, "analysis event preselection"};

    CP::SysReadHandle<xAOD::ElectronContainer> m_electronsHandle {
      this, "electrons", "", "the electron container to use"
    };
    CP::SysReadSelectionHandle m_electronSelection {
      this, "electronSelection", "", "the selection on the input electrons"
    };

    CP::SysReadHandle<xAOD::MuonContainer> m_muonsHandle {
      this, "muons", "", "the muon container to use"
    };
    CP::SysReadSelectionHandle m_muonSelection {
      this, "muonSelection", "", "the selection on the input muons"
    };

    CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
      this, "jets", "", "the jet container to use"
    };
    CP::SysReadSelectionHandle m_jetSelection {
      this, "jetSelection", "", "the selection on the input jets"
    };

    CP::SysReadDecorHandle<char> m_bTagDecision {
      this, "BTaggingDecoration", "", "Decoration for retrieveing b-tagging decision for jets"
    };

    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
      this, "eventInfo", "EventInfo", "the EventInfo container to decorate selection decisions to"
    };

    CP::SysWriteDecorHandle<char> m_eljetsDecision {
      this, "elJetsDecisionFlag", "ejets_%SYS%", "Decoration for pass/fail electron+jets selection"
    };
    CP::SysWriteDecorHandle<char> m_mujetsDecision {
      this, "muJetsDecisionFlag", "mujets_%SYS%", "Decoration for pass/fail muon+jets selection"
    };
  };
}

#endif
