#ifndef EVENT_SELECTOR_SAVEFILTERALG_H
#define EVENT_SELECTOR_SAVEFILTERALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <AsgTools/PropertyWrapper.h>
#include <SystematicsHandles/SysFilterReporterParams.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SelectionHelpers/SysWriteSelectionHandle.h>

// Framework includes
#include <xAODEventInfo/EventInfo.h>

namespace top {

  class SaveFilterAlg final : public EL::AnaAlgorithm {

    public:
      SaveFilterAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;
      virtual StatusCode finalize() override;

    private:
      // systematics
      CP::SysListHandle m_systematicsList {this};

      // input handles
      CP::SysReadSelectionHandle m_inputselection {
        this, "selection", "SetMe", "names of the selections to check"
      };
      CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
        this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"
      };

      // filter
      CP::SysFilterReporterParams m_filterParams {
        this, "event selector SAVE filter"
      };

      /// \brief whether to not apply an event filter
      Gaudi::Property<bool> m_noFilter {this, "noFilter", false, "whether to disable the event filter"};

      // output handles
      CP::SysWriteSelectionHandle m_outputselection {
	this, "selectionName", "SetMe", "name of the output selection decision"
      };
      CP::SysWriteDecorHandle<char> m_decoration {
	this, "decorationName", "SetMe", "additional decoration name for the event filter (stores the decision even when the filter is off)"
      };

  }; // class
} // namespace top

#endif // EVENT_SELECTOR_SAVEFILTERALG_H
