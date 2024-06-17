#ifndef TOPPARTONS_CALCTOPPARTONHISTORY_H
#define TOPPARTONS_CALCTOPPARTONHISTORY_H

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

  class CalcTopPartonHistory: public asg::AsgTool {

  public:
    explicit CalcTopPartonHistory(const std::string& name,
				  std::vector<std::string> truthCollections = {"TruthTop"});
    virtual ~CalcTopPartonHistory() {};
    
    CalcTopPartonHistory(const CalcTopPartonHistory& rhs) = delete;
    CalcTopPartonHistory(CalcTopPartonHistory&& rhs) = delete;
    CalcTopPartonHistory& operator = (const CalcTopPartonHistory& rhs) = delete;

    std::map<std::string, const xAOD::TruthParticle* > particleMap;

    /** Store the four-momentum of the post-FSR top or anti-top found using statusCodes
     *   This would only work if there is at most one "true" top of each charge (i.e. won't work for SS tops or 4 tops)
     *   This code was adapted from the 7TeV parton-level differential ttbar routine:
     * https://svnweb.cern.ch/trac/atlasphys-top/browser/Physics/Top/Software/MCvalidation/Rivet/Rivet2.X/trunk/routines/ATLAS_2014_I1304289/ATLAS_2014_I1304289.cc
     */
    
    bool ExistsInMap(const std::string key);
    bool Retrievep4(const std::string key, TLorentzVector& p4);
    bool RetrievepdgId(const std::string key, int& pdgId);
    std::string GetParticleType(const xAOD::TruthParticle* particle);

    void printPaths(const std::vector<std::vector<const xAOD::TruthParticle*>>& allPaths);
    void TraceParticle(const xAOD::TruthParticle* particle,
		       std::vector<const xAOD::TruthParticle*>& currentPath,
		       std::vector<std::vector<const xAOD::TruthParticle*>>& allPaths);
    void TraceParticles(const xAOD::TruthParticleContainer* truthParticles);
    
    bool topAfterFSR_SC(const xAOD::TruthParticleContainer* truthParticles, int start,
                        TLorentzVector& top_afterFSR_SC_p4);

    ///Store the four-momentum of several particles in the top decay chain
    bool topWb(const xAOD::TruthParticleContainer* truthParticles, int start, TLorentzVector& t_beforeFSR_p4,
               TLorentzVector& t_afterFSR_p4, TLorentzVector& W_p4, TLorentzVector& b_p4, TLorentzVector& Wdecay1_p4,
               int& Wdecay1_pdgId, TLorentzVector& Wdecay2_p4, int& Wdecay2_pdgId);
    bool topWq(const xAOD::TruthParticleContainer* truthParticles, int start, TLorentzVector& t_beforeFSR_p4,
               TLorentzVector& t_afterFSR_p4, TLorentzVector& W_p4, TLorentzVector& q_p4, int& q_pdgId,
               TLorentzVector& Wdecay1_p4, int& Wdecay1_pdgId, TLorentzVector& Wdecay2_p4, int& Wdecay2_pdgId);

    ///Store the four-momentum of b (not from tops_ before and after FSR
    bool b(const xAOD::TruthParticleContainer* truthParticles, TLorentzVector& b_beforeFSR, TLorentzVector& b_afterFSR);

    ///Store the four-momentum of several particles in the W decay chain
    bool Wlv(const xAOD::TruthParticleContainer* truthParticles, TLorentzVector& W_p4, TLorentzVector& Wdecay1_p4,
             int& Wdecay1_pdgId, TLorentzVector& Wdecay2_p4, int& Wdecay2_pdgId);

    /// Store the four-momentum of several particles in W decay chain for W that is NOT from top in Wt ST events
    bool Wt_W(const xAOD::TruthParticleContainer* truthParticles, TLorentzVector& W_p4, int& W_pdgId,
              TLorentzVector& Wdecay1_p4, int& Wdecay1_pdgId, TLorentzVector& Wdecay2_p4, int& Wdecay2_pdgId);

    /// Store the four-momentum of b quark that is NOT from top in Wt(b) ST events
    bool Wt_b(const xAOD::TruthParticleContainer* truthParticles, TLorentzVector& b_beforeFSR,
              TLorentzVector& b_afterFSR, int& b_pdgId);

    /// Store the four-momentum of photon coming from virtual top in ttgamma events
    bool topPhWb(const xAOD::TruthParticleContainer* truthParticles, int topId, TLorentzVector& t_beforeFSR_p4,
                 TLorentzVector& t_afterFSR_p4, TLorentzVector& Ph_p4, TLorentzVector& W_p4, TLorentzVector& b_p4,
                 TLorentzVector& Wdecay1_p4, int& Wdecay1_pdgId, TLorentzVector& Wdecay2_p4, int& Wdecay2_pdgId,
                 bool& has_ph, int& BranchType, int& IniPartonType, bool& missingTop);

    virtual StatusCode execute();

  protected:

    const std::vector<std::string> m_truthCollections;
    std::string m_topPartonsSGKey; // name of the output PartonHistory container to be stored in eventStore

    // this method is used to perform the linking of various TRUTH3 particle containers for TopPartons to work
    virtual StatusCode linkTruthContainers(const xAOD::TruthParticleContainer* &tp);

    // this is the method that runs the actual parton history reconstruction
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* ttbarPartonHistory) = 0;

    void fillEtaBranch(xAOD::PartonHistory* partonHistory, std:: string branchName, TLorentzVector& tlv);

    /** used to build container from multiple collections
     *   in DAOD_PHYS we don't have the TruthParticles collection, so we have to build a TruthParticleContainer (named out_contName) by merging several collections; this is stored in the evtStore
     *   this method has to use some tricks, like the helper m_tempParticles ConstDataVector, due to the desing of DataVector, see https://twiki.cern.ch/twiki/bin/view/AtlasComputing/DataVector
     */
    StatusCode buildContainerFromMultipleCollections(const std::vector<std::string> &collections, const std::string& out_contName);
    
    /** currently in DAOD_PHYS TruthTop have links to Ws from the TruthBoson collection, which have no link to their decay products;
     *   we have therefore to associate the W from the TruthBoson collections to those in the TruthBosonsWithDecayParticles collection.
     *   This method will use the helper method decorateCollectionWithLinksToAnotherCollection to decorate bosons in the TruthBoson collection with 
     *   "AT_linkToTruthBosonsWithDecayParticles", which is a link to the same bosons in the TruthBosonsWithDecayParticles collection
     */
    StatusCode linkBosonCollections();
    
    ///helper method to handle retriveing the truth particle linked in the decoration of another particle
    const xAOD::TruthParticle* getTruthParticleLinkedFromDecoration(const xAOD::TruthParticle* part, const std::string &decorationName);
    
  private:
    /**helper method currently used in DAOD_PHYS to link particles from a given collection to the same particles included in another collection;
     *  needed because particles may be duplicated in different collections, but their navigation links may only be there in some of them...
     */
    StatusCode decorateCollectionWithLinksToAnotherCollection(const std::string &collectionToDecorate, const std::string &collectionToLink, const std::string &nameOfDecoration);

  };

} // namespace top

#endif
