#include "PartonHistory/PartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include <array>

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  namespace PartonHistoryUtils {

    bool hasParentPdgId(const xAOD::TruthParticle* particle, int PdgId) {
      // Checks if the parent of the given particle has a specific PDG ID.
      return particle->parent() && particle->parent()->pdgId() == PdgId;
    }

    bool hasParentPdgId(const xAOD::TruthParticle* particle) {
      // Checks if the parent of the given particle has a specific PDG ID.
      return hasParentPdgId(particle, particle->pdgId());
    }

    bool hasIdenticalChild(const xAOD::TruthParticle* particle) {
      // Checks if the given particle has at least one child with an identical PDG ID.
      bool check = false;
      for (size_t i = 0; i < particle->nChildren(); i++) {
	if (particle->child(i)->pdgId() == particle->pdgId()) check=true;
      }
      return check;
    }

    bool hasParentAbsPdgId(const xAOD::TruthParticle* particle, int absPdgId) {
      // Checks if the parent of the given particle has a specific absolute PDG ID.
      return particle->parent() && std::abs(particle->parent()->pdgId()) == absPdgId;
    }

    bool isChildOf(const xAOD::TruthParticle* parent, const xAOD::TruthParticle* potentialChild) {
      if (parent->barcode() == potentialChild->barcode()) {
	return true;
      }
      // Loop through all children of the parent
      for (size_t i = 0; i < parent->nChildren(); ++i) {
        // Recursively check if potentialChild is a child of the current child
        if (isChildOf(parent->child(i), potentialChild)) {
	  return true;
        }
      }
      // If potentialChild is not found in the children or their descendants, return false
      return false;
    }

    bool isBrokenTop(const xAOD::TruthParticle* particle) {
      return (particle->pdgId() == 6 && particle->nChildren() == 0);
    }

    bool isAfterFSR(const xAOD::TruthParticle* particle) {
      bool isAfter = true;
      for (size_t j = 0; j < particle->nChildren(); j++) {
	if (particle->child(j)->pdgId() == particle->pdgId()) isAfter = false;
      }
      return isAfter;
    }

    const xAOD::TruthParticle* findAfterFSR(const xAOD::TruthParticle* particle) {
      bool isAfter(false);
      const int particle_ID = particle->pdgId();
      int forLoop = 0;

      while (!isAfter) {
	forLoop = 0;
	for (size_t j = 0; j < particle->nChildren(); j++) {
	  const xAOD::TruthParticle* tmp_children = particle->child(j);
	  if (tmp_children && tmp_children->pdgId() == particle_ID) {
	    particle = particle->child(j);
	    forLoop++;
	    break;
	  }//if
	}//for
	if (forLoop == 0) isAfter = true;
      }//while
      return particle;
    }

    bool hasParticleIdenticalParent(const xAOD::TruthParticle* particle) {
      bool skipit(false);

      for (size_t i = 0; i < particle->nParents(); i++) {
	const xAOD::TruthParticle* parent = particle->parent(i);
	if (parent && parent->pdgId() == particle->pdgId()) {
	  skipit = true;
	  break;
	}//if
      }//for
      return skipit;
    }

    void decorateWithMPtPhi(xAOD::PartonHistory* pHistory, const std::string & prefix, const PtEtaPhiMVector & vec ){
      constexpr size_t nItems=3;
      const std::array<std::string, nItems> suffix{"_m", "_pt", "_phi"};
      const std::array<double, nItems> values{vec.M(), vec.Pt(), vec.Phi()};
      for(size_t i(0);i<nItems;++i){
      	pHistory->auxdecor< float >(prefix+suffix[i]) = values[i];
      }
      return;
    }
  } // namespace PartonHistoryUtils
} // namespace top
