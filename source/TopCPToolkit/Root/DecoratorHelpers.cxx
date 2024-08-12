#include "VectorHelpers/LorentzHelper.h"

void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
		      const SG::AuxElement::Decorator<float>& dec_pt,
		      const SG::AuxElement::Decorator<float>& dec_eta,
		      const SG::AuxElement::Decorator<float>& dec_phi,
		      const SG::AuxElement::Decorator<int>& dec_pdgId,
		      const ROOT::Math::PtEtaPhiMVector& particle, int pdgId,
		      xAOD::PartonHistory* history) {
  dec_m(*history) = particle.M();
  dec_pt(*history) = particle.Pt();
  dec_eta(*history) = particle.Eta();
  dec_phi(*history) = particle.Phi();
  dec_pdgId(*history) = pdgId;
}

void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
		      const SG::AuxElement::Decorator<float>& dec_pt,
		      const SG::AuxElement::Decorator<float>& dec_eta,
		      const SG::AuxElement::Decorator<float>& dec_phi,
		      const ROOT::Math::PtEtaPhiMVector& particle,
		      xAOD::PartonHistory* history) {
  dec_m(*history) = particle.M();
  dec_pt(*history) = particle.Pt();
  dec_eta(*history) = particle.Eta();
  dec_phi(*history) = particle.Phi();
}

void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
			     const SG::AuxElement::Decorator<float>& dec_pt,
			     const SG::AuxElement::Decorator<float>& dec_eta,
			     const SG::AuxElement::Decorator<float>& dec_phi,
			     const SG::AuxElement::Decorator<int>& dec_pdgId,
			     xAOD::PartonHistory* history) {
  dec_m(*history) = -1;
  dec_pt(*history) = -1;
  dec_eta(*history) = -999;
  dec_phi(*history) = -999;
  dec_pdgId(*history) = 0;
}

void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
			     const SG::AuxElement::Decorator<float>& dec_pt,
			     const SG::AuxElement::Decorator<float>& dec_eta,
			     const SG::AuxElement::Decorator<float>& dec_phi,
			     xAOD::PartonHistory* history) {
  dec_m(*history) = -1;
  dec_pt(*history) = -1;
  dec_eta(*history) = -999;
  dec_phi(*history) = -999;
}
