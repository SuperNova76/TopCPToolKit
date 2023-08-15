#ifndef TTBARCPALGOANALYSIS_COMMONSFCALCULATOR_H
#define TTBARCPALGOANALYSIS_COMMONSFCALCULATOR_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODEventInfo/EventInfo.h>

namespace top {
  class LeptonSFCalculator : public EL::AnaAlgorithm {
  public:
    LeptonSFCalculator(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() final;
    virtual StatusCode execute() final;
    virtual StatusCode finalize() final;

  private:
    // systematics
    CP::SysListHandle m_systematicsList {this};

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

    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
      this, "eventInfo", "EventInfo", "the EventInfo container to decorate selection decisions to"
    };

    CP::SysReadDecorHandle<float> m_electronRecoSF {
      this, "electronRecoSF", "reco_effSF_%SYS%", "Decorated per-electron reconstruction SF"
    };

    CP::SysReadDecorHandle<float> m_electronIDSF {
      this, "electronIDSF", "id_effSF_%SYS%", "Decorated per-electron ID SF"
    };

    CP::SysReadDecorHandle<float> m_electronIsolSF {
      this, "electronIsolSF", "isol_effSF_%SYS%", "Decorated per-electron isolation SF"
    };

    CP::SysReadDecorHandle<float> m_muonRecoSF {
      this, "muonRecoSF", "reco_effSF_%SYS%", "Decorated per-muon reconstruction SF"
    };

    CP::SysReadDecorHandle<float> m_muonIsolSF {
      this, "muonIsolSF", "isol_effSF_%SYS%", "Decorated per-muon isol SF"
    };

    CP::SysReadDecorHandle<float> m_muonTTVASF {
      this, "muonTTVASF", "TTVA_effSF_%SYS%", "Decorated per-muon TTVA SF"
    };

    CP::SysWriteDecorHandle<float> m_event_leptonSF {
      this, "event_leptonSF", "leptonSF_%SYS%", "Decoration for per-event leptonSF"
    };
  };
}

#endif
