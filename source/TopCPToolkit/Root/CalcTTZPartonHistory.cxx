#include "TopPartons/CalcTTZPartonHistory.h"
#include "TopPartons/PartonHistoryUtils.h"
#include "TopPartons/CalcTtbarPartonHistory.h"

namespace top {
  using PartonHistoryUtils::decorateWithMPtPhi; // should this be used instead of the namespace?
  //using CalcTtbarPartonHistory::ttbarHistorySaver;
  CalcTTZPartonHistory::CalcTTZPartonHistory(const std::string& name) :
    CalcTtbarPartonHistory(name, {"TruthTop", "TruthBosonsWithDecayParticles", "HardScatterParticles"})
    {}

  StatusCode CalcTTZPartonHistory::runHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                   xAOD::PartonHistory* ttbarPartonHistory) {
    ANA_CHECK(CalcTtbarPartonHistory::runHistorySaver(truthParticles, ttbarPartonHistory));
    ANA_CHECK(zHistorySaver(truthParticles, ttbarPartonHistory));
    return StatusCode::SUCCESS;
  }

  StatusCode CalcTTZPartonHistory::zHistorySaver(const xAOD::TruthParticleContainer* truthParticles,
                                                 xAOD::PartonHistory* ttbarPartonHistory) {
    ttbarPartonHistory->IniVarZ();
    TLorentzVector Z;
    TLorentzVector ZDecay1;
    TLorentzVector ZDecay2;
    int ZDecay1_pdgId{};
    int ZDecay2_pdgId{};
    bool is_on_shell{};
    bool event_has_Z = CalcTTZPartonHistory::getZ(truthParticles,
                                                  &Z,
                                                  &ZDecay1,
                                                  &ZDecay1_pdgId,
                                                  &ZDecay2,
                                                  &ZDecay2_pdgId,
                                                  &is_on_shell);
 
    if (event_has_Z && !m_ancestry_corrupted) {   
      decorateWithMPtPhi(ttbarPartonHistory, "MC_Z", Z);
      fillEtaBranch(ttbarPartonHistory, "MC_Z_eta", Z);

      decorateWithMPtPhi(ttbarPartonHistory, "MC_Zdecay1", ZDecay1);
      ttbarPartonHistory->auxdecor< int >("MC_Zdecay1_pdgId") = ZDecay1_pdgId;
      fillEtaBranch(ttbarPartonHistory, "MC_Zdecay1_eta", ZDecay1);
    
      decorateWithMPtPhi(ttbarPartonHistory, "MC_Zdecay2", ZDecay2);
      ttbarPartonHistory->auxdecor< int >("MC_Zdecay2_pdgId") = ZDecay2_pdgId;
      fillEtaBranch(ttbarPartonHistory, "MC_Zdecay2_eta", ZDecay2);

      ttbarPartonHistory->auxdecor< int >("MC_Z_IsOnShell") = static_cast<int>(is_on_shell);
    }  // if

    ttbarPartonHistory->auxdecor< int >("MC_Z_AncestryCorrupted") = static_cast<int>(m_ancestry_corrupted);
    return StatusCode::SUCCESS;
  }

  bool CalcTTZPartonHistory::getZ(const xAOD::TruthParticleContainer* truthParticles,
                                  TLorentzVector* Z_p4,
                                  TLorentzVector* ZDecay1,
                                  int* ZDecay1_pdgId,
                                  TLorentzVector* ZDecay2,
                                  int* ZDecay2_pdgId,
                                  bool* is_on_shell) {
    bool hasZ = false;
    bool hasZDecay1 = false;
    bool hasZDecay2 = false;

    *is_on_shell = false;
    m_ancestry_corrupted = false;

    // First check for real (on-shell) Z bosons in the truth record
    // (PDG ID 23). Only consider Z bosons at the end of the chain
    // of radiative corrections (i.e. a Z boson decaying into
    // something else than a Z).
    for (const auto *p : *truthParticles) {
      if (!p->isZ()) continue;  // keep only Z bosons
      if (PartonHistoryUtils::hasParticleIdenticalParent(p)) continue;  // keep only Z before FSR

      const auto& z = PartonHistoryUtils::findAfterFSR(p);  // Z after FSR

      *is_on_shell = true;
      if (z->nChildren() != 2) continue;

      *Z_p4 = z->p4();
      hasZ = true;

      for (size_t i = 0; i < z->nChildren(); ++i) {
        const auto& child = z->child(i);
        if (!child) continue;
        if (child->pdgId() > 0) { // Child is particle
          *ZDecay1 = child->p4();
          *ZDecay1_pdgId = child->pdgId();
          hasZDecay1 = true;
        } else {  // antiparticle
          *ZDecay2 = child->p4();
          *ZDecay2_pdgId = child->pdgId();
          hasZDecay2 = true;
        }
      }  // for
    }  // for

    // Our job is done if the event has a real Z boson.
    if (hasZ && (!hasZDecay1 || !hasZDecay2)) m_ancestry_corrupted = true;
    if (hasZ) return hasZ && hasZDecay1 && hasZDecay2;

    // For off-shell Z bosons it's a bit more tricky. We now look
    // for two same-flavour particles that are attached to the
    // ttbar vertex.
    for (const auto *p : *truthParticles) {
      if (abs(p->pdgId()) > 19) continue;   // Only elementary fermions
      if (p->pdgId() < 0) continue;         // No anti-particles (to avoid
                                            // double-counting)
      const auto& sibling = getFlavourSibling(p);
      if (!sibling) continue;

      // Check whether the particle is attached to the ttbar vertex.
      bool has_top_sibling = false;
      bool has_antitop_sibling = false;

      const auto& parent = p->parent(0);
      if (!parent) continue;
      for (size_t i = 0; i < parent->nChildren(); ++i) {
        const auto* child = parent->child(i);
        if (!child) continue;
        if (child == p) continue; // Make sure we don't look at our candidate.
        if (child->pdgId() == 6) has_top_sibling = true;
        if (child->pdgId() == -6) has_antitop_sibling = true;
        if (has_top_sibling && has_antitop_sibling) break;
      }
      if (!(has_top_sibling && has_antitop_sibling)) continue;

      *ZDecay1 = p->p4();
      *ZDecay1_pdgId = p->pdgId();
      hasZDecay1 = true;
      *ZDecay2 = sibling->p4();
      *ZDecay2_pdgId = sibling->pdgId();
      hasZDecay2 = true;

      *Z_p4 = *ZDecay1 + *ZDecay2;
      hasZ = true;
    }  // for

    if (hasZ && (!hasZDecay1 || !hasZDecay2)) m_ancestry_corrupted = true;
    return hasZ && hasZDecay1 && hasZDecay2;
  }

  const xAOD::TruthParticle* CalcTTZPartonHistory::getFlavourSibling(const xAOD::TruthParticle* particle) {
    const auto& parent = particle->parent(0);

    if (!parent) return nullptr;

    for (size_t i = 0; i < parent->nChildren(); ++i) {
      const auto& sibling_candidate = parent->child(i);
      if (!sibling_candidate) continue;
      if (sibling_candidate->pdgId() == -particle->pdgId()) {
        return sibling_candidate;
      }
    }
    return nullptr;
  }
} // namespace top