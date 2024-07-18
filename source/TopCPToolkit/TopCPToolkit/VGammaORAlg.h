#ifndef VGAMMAORALG_H
#define VGAMMAORALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODEventInfo/EventInfo.h>

#include "GammaORTools/IVGammaORTool.h"

namespace top {

  class VGammaORAlg final : public EL::AnaAlgorithm {

    public:
      VGammaORAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;

    private:
      CP::SysListHandle m_systematicsList {this};
      ToolHandle<IVGammaORTool> m_vgammaORTool;

      // Handles for the input containers
      CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
        this, "eventInfo", "EventInfo", "the input EventInfo container"
      };

      // Handles for the output decorations
      CP::SysWriteDecorHandle<bool> m_inOverlapHandle {
        this, "in_vgamma_overlap", "in_vgamma_overlap_%SYS%", "decoration name for the VGammaORTool overlap flag"
      };

  };

} // namsepace top

#endif
