#ifndef TTBARCPALGOANALYSIS_H
#define TTBARCPALGOANALYSIS_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include "xAODMissingET/MissingETContainer.h"
#include <xAODJet/JetContainer.h>
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>

namespace top {

class TtbarCPalgoAnalysis final : public EL::AnaAlgorithm {

public:
  TtbarCPalgoAnalysis(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;
  virtual StatusCode finalize() override;

private:
  CP::SysListHandle m_systematicsList {this};
  CP::SysReadHandle<xAOD::ElectronContainer> m_electronsHandle {
    this, "electrons", "SetMe", "the electron collection to run on"};
  CP::SysReadHandle<xAOD::MuonContainer> m_muonsHandle {
    this, "muons", "SetMe", "the muon collection to run on"};
  CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
    this, "jets", "SetMe", "the jet collection to run on"};

};

} // namespace top

#endif
