#ifndef DECORATORHELPERS_H
#define DECORATORHELPERS_H

#include <Math/Vector4D.h>
#include <TMath.h>

// Template for filling particle information without a PDG ID
template<typename T, typename U>
void FillParticleInfo(const SG::AuxElement::Decorator<T>& dec_m, 
                      const SG::AuxElement::Decorator<T>& dec_pt, 
                      const SG::AuxElement::Decorator<T>& dec_eta, 
                      const SG::AuxElement::Decorator<T>& dec_phi, 
                      const ROOT::Math::PtEtaPhiMVector& particle, 
                      U* object) {
  dec_m(*object) = particle.M();
  dec_pt(*object) = particle.Pt();
  dec_eta(*object) = particle.Eta();
  dec_phi(*object) = particle.Phi();
}

// Template for filling particle information with a PDG ID
template<typename T, typename U>
void FillParticleInfo(const SG::AuxElement::Decorator<T>& dec_m, 
                      const SG::AuxElement::Decorator<T>& dec_pt, 
                      const SG::AuxElement::Decorator<T>& dec_eta, 
                      const SG::AuxElement::Decorator<T>& dec_phi, 
                      const SG::AuxElement::Decorator<int>& dec_pdgId, 
                      const ROOT::Math::PtEtaPhiMVector& particle, int pdgId, 
                      U* object) {
  dec_pdgId(*object) = pdgId;
  FillParticleInfo(dec_m, dec_pt, dec_eta, dec_phi, particle, object);
}

// Template for filling default particle information without a PDG ID
template<typename T, typename U>
void FillDefaultParticleInfo(const SG::AuxElement::Decorator<T>& dec_m, 
                             const SG::AuxElement::Decorator<T>& dec_pt, 
                             const SG::AuxElement::Decorator<T>& dec_eta, 
                             const SG::AuxElement::Decorator<T>& dec_phi, 
                             U* object) {
  dec_m(*object) = static_cast<T>(-1);
  dec_pt(*object) = static_cast<T>(-1);
  dec_eta(*object) = static_cast<T>(-999);
  dec_phi(*object) = static_cast<T>(-999);
}

// Template for filling default particle information with a PDG ID
template<typename T, typename U>
void FillDefaultParticleInfo(const SG::AuxElement::Decorator<T>& dec_m, 
                             const SG::AuxElement::Decorator<T>& dec_pt, 
                             const SG::AuxElement::Decorator<T>& dec_eta, 
                             const SG::AuxElement::Decorator<T>& dec_phi, 
                             const SG::AuxElement::Decorator<int>& dec_pdgId, 
                             U* object) {
  dec_pdgId(*object) = 0;
  FillDefaultParticleInfo(dec_m, dec_pt, dec_eta, dec_phi, object);
}

#endif // DECORATORHELPERS_H
