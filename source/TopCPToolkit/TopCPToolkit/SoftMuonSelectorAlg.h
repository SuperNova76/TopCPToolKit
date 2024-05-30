#ifndef SOFTMUONSELECTORALG_H
#define SOFTMUONSELECTORALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>

#include <SelectionHelpers/SysWriteSelectionHandle.h>

//#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>
//#include <xAODMissingET/MissingETContainer.h>
#include <xAODEventInfo/EventInfo.h>

#include <TVector2.h>

namespace top {

  class SoftMuonSelectorAlg final : public EL::AnaAlgorithm {

    public:
      SoftMuonSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;      

    private:
      CP::SysListHandle m_systematicsList {this};

      CP::SysReadSelectionHandle m_preselection {
        this, "eventPreselection", "", "event preselection to check before running this algorithm"
      };

      CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
        this, "jets", "", "the jet container to use"
      };
      CP::SysReadSelectionHandle m_jetSelection {
        this, "jetSelection", "", "the selection on the input jets"
      };


      CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle {
        this, "eventInfo", "EventInfo", "the input EventInfo container"
      };
//      CP::SysWriteDecorHandle<float> m_dphimetHandle {
//        this, "dphimet", "dphimet_%SYS%", "decoration name for DeltaPhi between each jet and the MET"
//      };
//      CP::SysWriteDecorHandle<float> m_mtwHandle {
//        this, "mtw", "mtw_%SYS%", "decoration name for the transverse W mass"
//      };

      //Trying to add soft muons
      CP::SysReadHandle<xAOD::MuonContainer> m_softmuonsHandle {
        this, "softmuons", "", "the input soft muon container"
      };
      CP::SysReadSelectionHandle m_softmuonSelection {
        this, "softmuonSelection", "", "the selection on the input soft muons"
      };

//      CP::SysReadDecorHandle<float> m_softmuonDRJetcut {
//        this, "SoftMuonDRJet", "", "Soft Muon maximum dR wrt nearest selected jet. Can be set to 999. to keep all soft muons. Default 0.4"
//      };

//      float m_softmuonDRJetcut {
//        this, "SoftMuonDRJet", 0.4, "Soft Muon maximum dR wrt nearest selected jet. Can be set to 999. to keep all soft muons. Default 0.4"
//      };
       float m_softmuonDRJetcut;// = 0.4;

      CP::SysReadSelectionHandle m_selection {
        this, "selection", "", "Name of the selection on which the SoftMuonSelectors instance is allowed to run"
      };

    private:
//      float calculateMinDRMuonJet(const xAOD::Muon& mu, const xAOD::JetContainer* xaod_jet, std::vector<unsigned int>& goodJets);
      virtual float calculateMinDRSoftMuonJet(const xAOD::Muon* softmuon, ConstDataVector<xAOD::JetContainer> selected_jets);

//      CP::SysWriteDecorHandle<float> m_DRminSoftMuonJetHandle {
//          this, "DRminSoftMuonJet", "DRminSoftMuonJet_%SYS%", "decoration name for the dR of the closest jet to the soft muon"
//      };

//      CP::SysWriteDecorHandle<std::vector<float>> m_SoftMuonJetDRminHandle {
      CP::SysWriteDecorHandle<float> m_SoftMuonJetDRminHandle {
        this, "SoftMuonJetDRmin", "SoftMuonJetDRmin_%SYS%", "decoration name for the dR of the closest jet to the soft muon"
      };

//      CP::SysWriteDecorHandle<std::vector<bool>> m_SoftMuonPassDRJetcut {
      CP::SysWriteDecorHandle<bool> m_SoftMuonPassDRJetcut {
        this, "SoftMuonPassDRJetcut", "SoftMuonPassDRJetcut_%SYS%", "decoration name for tagging soft muons that pass the dR condition with its closest jet in the event"
      };


      CP::SysWriteSelectionHandle m_pass_SoftMuonPassDRJetcut {
	 this, "pass_SoftMuonPassDRJetcut", "pass_SoftMuonPassDRJetcut_%SYS%,as_char", "decoration name for tagging the events that have at least one soft muon passing the dR condition with its closest jet in the event"
      };

    //Functions to add additional variables with additional information about the soft muons, and/or the nearest jet to the soft muon
    private:
      virtual bool SaveAdditionalSoftMuonVairables(std::vector<const xAOD::Muon*> softmuons);
	      //SaveAdditionalInformationFromNearestJet

      //list of variables.

 //      CP::SysWriteDecorHandle<float> m_dphimetHandle {                                                                //        this, "dphimet", "dphimet_%SYS%", "decoration name for DeltaPhi between each jet and the MET"                 //      };
/*
      vector<float> m_outtree_softmu_qOverP;
      vector<float> m_outtree_softmu_qOverP_ID;
      vector<float> m_outtree_softmu_qOverP_ME;
      vector<float> m_outtree_softmu_qOverPerr;
      vector<float> m_outtree_softmu_qOverPerr_ID;
      vector<float> m_outtree_softmu_qOverPerr_ME;
      vector<float> m_outtree_softmu_z0_sintheta;
      vector<float> m_outtree_softmu_d0;
      vector<float> m_outtree_softmu_d0sig;
      vector<float> m_outtree_softmu_reducedChi2;
      vector<float> m_outtree_softmu_reducedChi2_ID;
      vector<float> m_outtree_softmu_reducedChi2_ME;
      vector<float> m_outtree_softmu_reducedSegmentChi2;
      vector<float> m_outtree_softmu_momentumBalanceSignificance;
      vector<float> m_outtree_softmu_scatteringCurvatureSignificance;
      vector<float> m_outtree_softmu_scatteringNeighbourSignificance;
      vector<float> m_outtree_softmu_qOverPSignificance;
      vector<float> m_outtree_softmu_rhoPrime;
      vector<float> m_outtree_softmu_spectrometerFieldIntegral;

      vector<int> m_outtree_softmu_nprecisionLayers;
      vector<int> m_outtree_softmu_nprecisionHoleLayers;
      vector<int> m_outtree_softmu_nGoodPrecLayers;
      vector<int> m_outtree_softmu_innerSmallHits;
      vector<int> m_outtree_softmu_innerLargeHits;
      vector<int> m_outtree_softmu_middleSmallHits;
      vector<int> m_outtree_softmu_middleLargeHits;
      vector<int> m_outtree_softmu_outerSmallHits;
      vector<int> m_outtree_softmu_outerLargeHits;
      vector<int> m_outtree_softmu_extendedSmallHits;
      vector<int> m_outtree_softmu_extendedLargeHits;
      vector<int> m_outtree_softmu_extendedSmallHoles;
      vector<int> m_outtree_softmu_isSmallGoodSectors;
      vector<int> m_outtree_softmu_cscUnspoiledEtaHits;
      vector<int> m_outtree_softmu_numberOfPixelHits;
      vector<int> m_outtree_softmu_numberOfPixelDeadSensors;
      vector<int> m_outtree_softmu_numberOfPixelHoles;
      vector<int> m_outtree_softmu_numberOfSCTHits;
      vector<int> m_outtree_softmu_numberOfSCTDeadSensors;
      vector<int> m_outtree_softmu_numberOfSCTHoles;
      vector<int> m_outtree_softmu_numberOfTRTHits;
      vector<int> m_outtree_softmu_numberOfTRTOutliers;

      vector<float> m_outtree_softmu_ptcone20_Nonprompt_All_MaxWeightTTVA_pt500;
      vector<float> m_outtree_softmu_ptvarcone30_Nonprompt_All_MaxWeightTTVA_pt500;
      vector<float> m_outtree_softmu_ptcone20_Nonprompt_All_MaxWeightTTVA_pt1000;
      vector<float> m_outtree_softmu_ptvarcone30_Nonprompt_All_MaxWeightTTVA_pt1000;
      vector<float> m_outtree_softmu_neflowisol20;
      vector<float> m_outtree_softmu_EnergyLoss;
      vector<float> m_outtree_softmu_EnergyLossSigma;
      vector<unsigned char> m_outtree_softmu_EnergyLossType;
      vector<float> m_outtree_softmu_ParamEnergyLoss;
      vector<float> m_outtree_softmu_MeasEnergyLoss;
      vector<float> m_outtree_softmu_ParamEnergyLossSigmaPlus;
      vector<float> m_outtree_softmu_ParamEnergyLossSigmaMinus;
      vector<float> m_outtree_softmu_MeasEnergyLossSigma;

      //inline void IdMsPt(const xAOD::Muon& muon, float& idPt, float& msPt) const;
      inline float qOverPsignificance(const xAOD::Muon& muon) const;
      inline float rhoPrime(const xAOD::Muon& muon) const;

      //Additinal variables about the nearest jet
      vector<int> m_outtree_softmu_nearestJet_Index;
      vector<float> m_outtree_softmu_nearestJet_dR;
      vector<float> m_outtree_softmu_nearestJet_EMFrac;
      vector<int> m_outtree_softmu_nearestJet_NumTrkPt500;
      vector<float> m_outtree_softmu_nearestJet_SumPtTrkPt500;
      vector<int> m_outtree_softmu_nearestJet_NumTrkPt1000;
      vector<float> m_outtree_softmu_nearestJet_SumPtTrkPt1000;
      vector<int> m_outtree_softmu_nearestJet_N90Constituents;
      vector<float> m_outtree_softmu_nearestJet_TrackWidthPt500;
      vector<float> m_outtree_softmu_nearestJet_TrackWidthPt1000;
      vector<float> m_outtree_softmu_nearestJet_Width;
      vector<float> m_outtree_softmu_nearestJet_Charge;
      vector<float> m_outtree_softmu_nearestJet_ChargedPFOWidthPt500;
      vector<float> m_outtree_softmu_nearestJet_ChargedPFOWidthPt1000;
*/


  };

} // namsepace top

#endif
