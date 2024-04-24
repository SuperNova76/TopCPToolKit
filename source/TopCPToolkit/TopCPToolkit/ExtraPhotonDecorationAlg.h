#ifndef EXTRAPHOTONDECORATIONALG_H
#define EXTRAPHOTONDECORATIONALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODEgamma/PhotonContainer.h>


namespace top {

  class ExtraPhotonDecorationAlg final : public EL::AnaAlgorithm {

    public:
      ExtraPhotonDecorationAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;
    
    private:
      CP::SysListHandle m_systematicsList {this};
      CP::SysReadHandle<xAOD::PhotonContainer> m_photonsHandle { this, "photons", "", "the input photon container" };
      CP::SysWriteDecorHandle<int> m_conversionTypeHandle { this, "conversionType", "conversionType_%SYS%", "decoration name for photon conversionType" };
      CP::SysWriteDecorHandle<float> m_caloEtaHandle { this, "caloEta", "caloEta_%SYS%", "decoration name for photon caloEta" };
  };

} // namsepace top

#endif
