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
      bool hasH;
      TLorentzVector Wp_p4;
      bool hasWp;
      TLorentzVector Wm_p4;
      bool hasWm;
      TLorentzVector WpDecay1_p4;
      TLorentzVector WpDecay2_p4;
      int WpDecay1_pdgId;
      int WpDecay2_pdgId;
      bool hasWpDecay1;
      bool hasWpDecay2;
      TLorentzVector WmDecay1_p4;
      TLorentzVector WmDecay2_p4;
      int WmDecay1_pdgId;
      int WmDecay2_pdgId;
      bool hasWmDecay1;
      bool hasWmDecay2;

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
	hasH = false;
	hasWm = false;
	hasWp = false;
	hasWpDecay1 = false;
	hasWpDecay2 = false;
	hasWmDecay1 = false;
	hasWmDecay2 = false;
      }
    } PartonLevelHWW;

    //Storing parton history for HWW analysis
    CalcHWWPartonHistory(const CalcHWWPartonHistory& rhs) = delete;
    CalcHWWPartonHistory(CalcHWWPartonHistory&& rhs) = delete;
    CalcHWWPartonHistory& operator = (const CalcHWWPartonHistory& rhs) = delete;

    bool Fill(const xAOD::TruthParticleContainer* truthParticles, int start);

  protected:
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* hwwPartonHistory) override;
  };
}

#endif
