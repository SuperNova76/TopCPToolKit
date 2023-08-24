#ifndef EVENT_SELECTOR_METSELECTORALG_H
#define EVENT_SELECTOR_METSELECTORALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SelectionHelpers/SysWriteSelectionHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODMissingET/MissingETContainer.h>
#include <xAODEventInfo/EventInfo.h>

#include <TopEventSelection/SignEnums.h>

namespace top {

  class METSelectorAlg final : public EL::AnaAlgorithm {

    public:
      METSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;
      virtual StatusCode finalize() override;

    private:
      // configurable properties
      const float m_metref;
      const std::string m_sign;

      // internal properties
      SignEnum::ComparisonOperator m_signEnum;

      // systematics
      CP::SysListHandle m_systematicsList {this};

      // input handles
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
        this, "decorationName", "SetMe", "decoration name for the MET selector"
      };

  }; // class
} // namespace top

#endif // EVENT_SELECTOR_METSELECTORALG_H
