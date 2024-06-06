#ifndef HIGGSPARTONS_CALCHIGGSPARTONHISTORY_H
#define HIGGSPARTONS_CALCHIGGSPARTONHISTORY_H

// system include(s):
#include <memory>
#include <vector>

// Framework include(s):
#include "AsgTools/AsgTool.h"
#include "AthContainers/DataVector.h"
#include "AthContainers/AuxElement.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "TopPartons/PartonHistory.h"

namespace top {

  class CalcHiggsPartonHistory: public asg::AsgTool {

  public:
    explicit CalcHiggsPartonHistory(const std::string& name,
				    std::vector<std::string> truthCollections = {"TruthBosonsWithDecayParticles"});
    virtual ~CalcHiggsPartonHistory() {};

    CalcHiggsPartonHistory(const CalcHiggsPartonHistory& rhs) = delete;
    CalcHiggsPartonHistory(CalcHiggsPartonHistory&& rhs) = delete;
    CalcHiggsPartonHistory& operator = (const CalcHiggsPartonHistory& rhs) = delete;

    bool higgsWW(const xAOD::TruthParticleContainer* truthParticles, int start, TLorentzVector& higgs_p4, TLorentzVector& Wp_p4, TLorentzVector& Wm_p4, TLorentzVector& Wp_decay1_p4, TLorentzVector& Wp_decay2_p4, TLorentzVector& Wm_decay1_p4, TLorentzVector& Wm_decay2_p4, int& Wp_decay1_pdgId, int& Wp_decay2_pdgId, int& Wm_decay1_pdgId, int& Wm_decay2_pdgId);
    
    virtual StatusCode execute();

  protected:

    const std::vector<std::string> m_truthCollections;
    std::string m_higgsPartonsSGKey; // name of the output PartonHistory container to be stored in eventStore

    // this method is used to perform the linking of various TRUTH3 particle containers for HiggsPartons to work
    virtual StatusCode linkTruthContainers(const xAOD::TruthParticleContainer* &tp);

    // this is the method that runs the actual parton history reconstruction
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* hwwPartonHistory) = 0;

    void fillEtaBranch(xAOD::PartonHistory* partonHistory, std:: string branchName, TLorentzVector& tlv);

    StatusCode buildContainerFromMultipleCollections(const std::vector<std::string> &collections, const std::string& out_contName);

    StatusCode linkBosonCollections();

    StatusCode decorateCollectionWithLinksToAnotherCollection(const std::string &collectionToDecorate, const std::string &collectionToLink, const std::string &nameOfDecoration);

  };

} // namespace top

#endif
