#ifndef TOPSPANET_RUNSPANETALG_H
#define TOPSPANET_RUNSPANETALG_H

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

// SpaNet topologies
#include "TopSpaNet/SpaNetEnums.h"
#include "TopSpaNet/TopologyBase.h"
#include "TopSpaNet/TopologyTtbarLjets.h"

namespace top {

  class RunSpaNetAlg final : public EL::AnaAlgorithm {

  public:
    RunSpaNetAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

  private:
    StatusCode execute_syst(const CP::SystematicSet &sys);
    // configurable properties
    const std::string m_topology;
    const std::string m_btagger;

    // the SPA-Net object
    std::unique_ptr<TopSpaNetTopology> m_spanet_reco;
    SpaNetEnums::Topology m_topologyEnum;

    // systematics
    CP::SysListHandle m_systematicsList {this};

    // inputs needed for reconstruction
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

    CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
      this, "jets", "", "the jet container to use"
	};
    CP::SysReadSelectionHandle m_jetSelection {
      this, "jetSelection", "", "the selection on the input jets"
	};

    CP::SysReadHandle<xAOD::MissingETContainer> m_metHandle {
      this, "met", "", "the MET container to use"
	};

    CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"
	};

    CP::SysReadSelectionHandle m_selection {
      this, "eventSelection", "", "Name of the selection on which this SPA-Net instance is allowed to run"
	};

    // output decorations
    CP::SysWriteDecorHandle<int> m_lep_b_idx_decor {
      this, "leptonic_b_index", "spanet_lep_b_index_%SYS%", "Index of the b-jet from the leptonic top in l+jets"
	};
    CP::SysWriteDecorHandle<int> m_had_b_idx_decor {
      this, "hadronic_b_index", "spanet_had_b_index_%SYS%", "Index of the b-jet from the hadronic top in l+jets"
	};
    CP::SysWriteDecorHandle<int> m_down_idx_decor {
      this, "down_index", "spanet_down_index_%SYS%", "Index of the down-type jet from the hadronic W decay in l+jets"
	};
    CP::SysWriteDecorHandle<int> m_up_idx_decor {
      this, "up_index", "spanet_up_index_%SYS%", "Index of the up-type jet from the hadronic W decay in l+jets"
	};
    CP::SysWriteDecorHandle<float> m_lep_top_score_decor {
      this, "leptonic_top_score", "spanet_lep_top_score_%SYS%", "Reconstruction score for the leptonic top in l+jets"
	};
    CP::SysWriteDecorHandle<float> m_had_top_score_decor {
      this, "hadronic_top_score", "spanet_had_top_score_%SYS%", "Reconstruction score for the hadronic top in l+jets"
	};
    CP::SysWriteDecorHandle<float> m_lep_top_exist_decor {
      this, "leptonic_top_existence", "spanet_lep_top_existence_%SYS%", "Reconstruction existence probability for the leptonic top in l+jets"
	};
    CP::SysWriteDecorHandle<float> m_had_top_exist_decor {
      this, "hadronic_top_existence", "spanet_had_top_existence_%SYS%", "Reconstruction existence probability for the hadronic top in l+jets"
	};

  };

} // namespace top

#endif
