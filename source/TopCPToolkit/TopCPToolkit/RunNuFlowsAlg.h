#ifndef TOPNUFLOWS_RUNNUFLOWSALG_H
#define TOPNUFLOWS_RUNNUFLOWSALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>
#include <xAODMissingET/MissingETContainer.h>
#include <xAODEventInfo/EventInfo.h>

// NuFlows model
#include "TopNuFlows/Dilepton.h"

namespace top
{

  class RunNuFlowsAlg final : public EL::AnaAlgorithm
  {

  public:
    RunNuFlowsAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

  private:

    // Function to run in the event loop per systematic
    StatusCode execute_syst(const CP::SystematicSet &sys);

    // configurable properties
    std::string m_onnxFilePath;
    std::string m_btagger;

    // the nuflows object
    std::unique_ptr<top::TopNuFlowsDilepton> m_nuflows;

    // Systematics
    CP::SysListHandle m_systematicsList{this};

    // Inputs needed for reconstruction
    CP::SysReadHandle<xAOD::ElectronContainer> m_electronsHandle{
        this, "electrons", "", "the electron container to use"};
    CP::SysReadSelectionHandle m_electronSelection{
        this, "electronSelection", "", "the selection on the input electrons"};
    CP::SysReadHandle<xAOD::MuonContainer> m_muonsHandle{
        this, "muons", "", "the muon container to use"};
    CP::SysReadSelectionHandle m_muonSelection{
        this, "muonSelection", "", "the selection on the input muons"};
    CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle{
        this, "jets", "", "the jet container to use"};
    CP::SysReadSelectionHandle m_jetSelection{
        this, "jetSelection", "", "the selection on the input jets"};
    CP::SysReadHandle<xAOD::MissingETContainer> m_metHandle{
        this, "met", "", "the MET container to use"};
    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle{
        this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"};

    // Output decorations
    CP::SysWriteDecorHandle<float> m_nu_px_decor{
        this, "nuflows_nu_px", "nuflows_nu_px_%SYS%", "Sampled value of the neutrino px"};
    CP::SysWriteDecorHandle<float> m_nu_py_decor{
    this, "nuflows_nu_py", "nuflows_nu_py_%SYS%", "Sampled value of the neutrino py"};
    CP::SysWriteDecorHandle<float> m_nu_pz_decor{
        this, "nuflows_nu_pz", "nuflows_nu_pz_%SYS%", "Sampled value of the neutrino pz"};
    CP::SysWriteDecorHandle<float> m_anti_nu_px_decor{
        this, "nuflows_anti_nu_px", "nuflows_anti_nu_px_%SYS%", "Sampled value of the antineutrino px"};
    CP::SysWriteDecorHandle<float> m_anti_nu_py_decor{
        this, "nuflows_anti_nu_py", "nuflows_anti_nu_py_%SYS%", "Sampled value of the antineutrino py"};
    CP::SysWriteDecorHandle<float> m_anti_nu_pz_decor{
        this, "nuflows_anti_nu_pz", "nuflows_anti_nu_pz_%SYS%", "Sampled value of the antineutrino pz"};
    CP::SysWriteDecorHandle<float> m_loglik_decor{
        this, "nuflows_loglik", "nuflows_loglik_%SYS%", "Log likelihood of the (anti)neutrino solution"};

    // Misc
    CP::SysReadSelectionHandle m_eventselection {
        this, "eventSelection", "", "event preselection to check before running this algorithm"};
  };

} // namsepace top

#endif
