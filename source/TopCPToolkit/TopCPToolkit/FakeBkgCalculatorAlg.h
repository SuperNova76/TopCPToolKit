#ifndef FAKEBKGCALCULATORALG_H
#define FAKEBKGCALCULATORALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>

#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODEventInfo/EventInfo.h>

#include "AsgAnalysisInterfaces/ILinearFakeBkgTool.h"


namespace top {

  class FakeBkgCalculatorAlg final : public EL::AnaAlgorithm {

    public:
      FakeBkgCalculatorAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;
    
    private:
      CP::SysListHandle m_systematicsList {this};

    // inputs needed for calculation
    CP::SysReadHandle<xAOD::ElectronContainer> m_electronsHandle {
      this, "electrons", "", "the electron container to use"
    };
    CP::SysReadSelectionHandle m_electronSelection {
      this, "electronSelection", "", "the selection on the input electrons"
    };
    CP::SysReadSelectionHandle m_electronSelectionTarget {
      this, "electronSelectionTarget", "", "the tight selection on the input electrons"
    };
    
    CP::SysReadHandle<xAOD::MuonContainer> m_muonsHandle {
      this, "muons", "", "the muon container to use"
    };
    CP::SysReadSelectionHandle m_muonSelection {
      this, "muonSelection", "", "the selection on the input muons"
    };
    CP::SysReadSelectionHandle m_muonSelectionTarget {
      this, "muonSelectionTarget", "", "the tight selection on the input muons"
    };


    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection deciosions from"
    };

    CP::SysReadSelectionHandle m_preselection {
      this, "eventPreselection", "", "event preselection to check before running this algorithm"
    };

    ToolHandle<CP::ILinearFakeBkgTool> m_fake_tool;

    // output container
    CP::SysWriteDecorHandle<float> m_fake_tool_result {
      this, "FakeToolResult", "FakeToolResult_%SYS%", "decoration name for the Fake Tool result"
    };

    // configurable properties
    std::string m_Definition;
    std::string m_Process;
  };

} // namespace top

#endif
