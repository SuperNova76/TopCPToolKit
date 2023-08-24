#ifndef EVENT_SELECTOR_METMWTSELECTORALG_H
#define EVENT_SELECTOR_METMWTSELECTORALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SelectionHelpers/SysWriteSelectionHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODMissingET/MissingETContainer.h>
#include <xAODEventInfo/EventInfo.h>

#include <TopEventSelection/SignEnums.h>

namespace top {

  class METMWTSelectorAlg final : public EL::AnaAlgorithm {

    public:
      METMWTSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;
      virtual StatusCode finalize() override;

    private:
      // configurable properties
      const float m_sumref;
      const std::string m_sign;

      // internal properties
      SignEnum::ComparisonOperator m_signEnum;

      // systematics
      CP::SysListHandle m_systematicsList {this};

      // input handles
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
      CP::SysReadHandle<xAOD::MissingETContainer> m_metHandle {
        this, "met", "SetMe", "the MET container to use"
      };
      CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
        this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"
      };
      CP::SysReadSelectionHandle m_preselection {
        this, "eventPreselection", "SetMe", "name of the preselection to check before applying this one"
      };

      // output handles
      CP::SysWriteSelectionHandle m_decoration {
        this, "decorationName", "SetMe", "decoration name for the MET+MWT selector"
      };

  }; // class
} // namespace top

#endif // EVENT_SELECTOR_METMWTSELECTORALG_H
