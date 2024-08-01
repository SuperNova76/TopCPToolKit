#ifndef PARTONS_CALCPARTONHISTORY_H
#define PARTONS_CALCPARTONHISTORY_H

// system include(s):
#include <memory>
#include <vector>

// Framework include(s):
#include "AsgTools/AsgTool.h"
#include "AthContainers/DataVector.h"
#include "AthContainers/AuxElement.h"
#include "xAODTruth/TruthParticleContainer.h"
#include "PartonHistory/PartonHistory.h"

namespace top {

  class CalcPartonHistory: public asg::AsgTool {

  public:
    explicit CalcPartonHistory(const std::string& name,
			       const std::vector<std::string>& truthCollections = {"TruthTop"});
    virtual ~CalcPartonHistory() {};

    CalcPartonHistory(const CalcPartonHistory& rhs) = delete;
    CalcPartonHistory(CalcPartonHistory&& rhs) = delete;
    CalcPartonHistory& operator = (const CalcPartonHistory& rhs) = delete;

    std::map<std::string, const xAOD::TruthParticle* > particleMap;

    void AddToParticleMap(const xAOD::TruthParticle* particle, std::string key);
    bool ExistsInMap(const std::string& key);
    bool Retrievep4(const std::string& key, TLorentzVector& p4);
    bool RetrievepdgId(const std::string& key, int& pdgId);
    bool RetrieveParticleInfo(const std::string& prefix, TLorentzVector& particle, int& pdgId);

    void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m, const SG::AuxElement::Decorator<float>& dec_pt,
			  const SG::AuxElement::Decorator<float>& dec_eta, const SG::AuxElement::Decorator<float>& dec_phi,
			  const TLorentzVector& particle,
			  xAOD::PartonHistory *history);
    void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m, const SG::AuxElement::Decorator<float>& dec_pt,
			  const SG::AuxElement::Decorator<float>& dec_eta, const SG::AuxElement::Decorator<float>& dec_phi,
			  const SG::AuxElement::Decorator<int>& dec_pdgId,
			  const TLorentzVector& particle, int pdgId,
			  xAOD::PartonHistory *history);
    void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m, const SG::AuxElement::Decorator<float>& dec_pt,
				 const SG::AuxElement::Decorator<float>& dec_eta, const SG::AuxElement::Decorator<float>& dec_phi,
				 const SG::AuxElement::Decorator<int>& dec_pdgId,
				 xAOD::PartonHistory* history);
    void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m, const SG::AuxElement::Decorator<float>& dec_pt,
				 const SG::AuxElement::Decorator<float>& dec_eta, const SG::AuxElement::Decorator<float>& dec_phi,
				 xAOD::PartonHistory* history);

    void EnsureKeyExists(const std::string& key, const std::string& fallbackKey);
    void EnsureTtbarKeysExist();

    bool hasParentPdgId(const xAOD::TruthParticle* particle, int PdgId);
    bool hasIdenticalChild(const xAOD::TruthParticle* particle);
    bool hasParentAbsPdgId(const xAOD::TruthParticle* particle, int absPdgId);

    std::string GetParticleType(const xAOD::TruthParticle* particle);

    void TraceParticle(const xAOD::TruthParticle* particle,
		       std::vector<const xAOD::TruthParticle*>& currentPath,
		       std::vector<std::vector<const xAOD::TruthParticle*>>& allPaths);
    void TraceParticles(const xAOD::TruthParticleContainer* truthParticles);
    bool handleBeforeFSR(const xAOD::TruthParticle* particle, const std::string& newKey, std::string& key);
    bool handleAfterFSR(const xAOD::TruthParticle* particle, const std::string& newKey, const std::string& oldKey, std::string& key);
    bool handleDecay(const xAOD::TruthParticle* particle, std::string& key, int decayID);
    void handleSameAsParent(const xAOD::TruthParticle* particle, std::string& key);
    void handleDefault(const xAOD::TruthParticle* particle, const std::string& newKey, std::string& key);

    void FillParticleMap(std::vector<std::vector<const xAOD::TruthParticle*>>& allPaths);
    void FillTopPartonHistory(xAOD::PartonHistory* PartonHistory);
    void FillAntiTopPartonHistory(xAOD::PartonHistory* PartonHistory);
    void FillBottomPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent);
    void FillAntiBottomPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent);
    void FillWpPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent);
    void FillWmPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent);
    void FillZPartonHistory(xAOD::PartonHistory* PartonHistory, const std::string& parent, const int bosoID=-1);
    void FillTtbarPartonHistory(xAOD::PartonHistory* PartonHistory);
    void FillHiggsPartonHistory(xAOD::PartonHistory* PartonHistory);

    virtual StatusCode execute();

  protected:

    const std::vector<std::string> m_truthCollections;
    std::string m_PartonsSGKey; // name of the output PartonHistory container to be stored in eventStore

    // this method is used to perform the linking of various TRUTH3 particle containers for Partons to work
    virtual StatusCode linkTruthContainers(const xAOD::TruthParticleContainer* &tp);

    // this is the method that runs the actual parton history reconstruction
    virtual StatusCode runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                       xAOD::PartonHistory* ttbarPartonHistory) = 0;

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
