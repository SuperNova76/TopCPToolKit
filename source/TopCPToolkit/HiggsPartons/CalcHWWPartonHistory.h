#ifndef TOPPARTONS_CALCHWWPARTONHISTORY_H
#define TOPPARTONS_CALCHWWPARTONHISTORY_H

// Framework include(s):
#include "HiggsPartons/CalcHiggsPartonHistory.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"

namespace top {
  class CalcHWWPartonHistory: public CalcHiggsPartonHistory {
  public:
    explicit CalcHWWPartonHistory(const std::string &name,
				  std::vector<std::string> truthCollections = {"TruthBosonsWithDecayParticles"});
    virtual ~CalcHWWPartonHistory() {}

    struct HWW_values {
      //Higgs boson
      TLorentzVector H_p4;
      //W+
      TLorentzVector Wp_p4;
      //W-
      TLorentzVector Wm_p4;
      //W+ Decays
      TLorentzVector WpDecay1_p4;
      int WpDecay1_pdgId;
      TLorentzVector WpDecay2_p4;
      int WpDecay2_pdgId;
      //W- Decays
      TLorentzVector WmDecay1_p4;
      int WmDecay1_pdgId;
      TLorentzVector WmDecay2_p4;
      int WmDecay2_pdgId;

      void reset(){
        H_p4.SetPtEtaPhiE(0,0,0,0);
        WpDecay1_p4.SetPtEtaPhiE(0,0,0,0);
        WpDecay2_p4.SetPtEtaPhiE(0,0,0,0);
	WmDecay1_p4.SetPtEtaPhiE(0,0,0,0);
        WmDecay2_p4.SetPtEtaPhiE(0,0,0,0);
        WpDecay1_pdgId = -9999;
        WpDecay2_pdgId = -9999;
	WmDecay1_pdgId = -9999;
        WmDecay2_pdgId = -9999;
      }
    } hww;


    //Storing parton history for HWW analysis
    CalcHWWPartonHistory(const CalcHWWPartonHistory& rhs) = delete;
    CalcHWWPartonHistory(CalcHWWPartonHistory&& rhs) = delete;
    CalcHWWPartonHistory& operator = (const CalcHWWPartonHistory& rhs) = delete;

    bool HWW(const xAOD::TruthParticleContainer* truthParticles, int start);

  protected:
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* hwwPartonHistory) override;
  };
}

#endif
