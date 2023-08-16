#ifndef EXTRAPARTICLEDECORATIONALG_H
#define EXTRAPARTICLEDECORATIONALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODBase/IParticleContainer.h>

namespace top {

class ExtraParticleDecorationAlg final : public EL::AnaAlgorithm {

public:
  ExtraParticleDecorationAlg(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;
  virtual StatusCode finalize() override;

private:
  CP::SysListHandle m_systematicsList {this};
  CP::SysReadHandle<xAOD::IParticleContainer> m_particlesHandle {
    this, "particles", "SetMe", "the particle collection to run on"};
  CP::SysWriteDecorHandle<float> m_energyDecor {
    this, "energyDecoration", "e_%SYS%", "decoration for per-object energy"};

};

} // namespace top

#endif
