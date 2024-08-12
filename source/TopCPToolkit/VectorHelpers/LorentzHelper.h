#ifndef MINIHVV_LORENTZHELPER_H
#define MINIHVV_LORENTZHELPER_H

#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"
#include "PartonHistory/PartonHistory.h"

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Electron *Lepton);
ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Electron *Lepton);
ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Muon *Lepton);
ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Muon *Lepton);
ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromJet(const xAOD::Jet *Jet);
ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromJet(const xAOD::Jet *Jet);
ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromTruth(const xAOD::TruthParticle *TruthParticle);
ROOT::Math::PxPyPzMVector GetPxPyPzMfromTruth(const xAOD::TruthParticle *TruthParticle);
ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromTruth(const xAOD::TruthParticle *TruthParticle);
ROOT::Math::PxPyPzEVector GetPxPyPzEfromTruth(const xAOD::TruthParticle *TruthParticle);
ROOT::Math::PtEtaPhiMVector TLorentzToPtEtaPhiM(const TLorentzVector& p);

void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
		      const SG::AuxElement::Decorator<float>& dec_pt,
		      const SG::AuxElement::Decorator<float>& dec_eta,
		      const SG::AuxElement::Decorator<float>& dec_phi,
		      const ROOT::Math::PtEtaPhiMVector& particle,
		      xAOD::PartonHistory *history);
void FillParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
		      const SG::AuxElement::Decorator<float>& dec_pt,
		      const SG::AuxElement::Decorator<float>& dec_eta,
		      const SG::AuxElement::Decorator<float>& dec_phi,
		      const SG::AuxElement::Decorator<int>& dec_pdgId,
		      const ROOT::Math::PtEtaPhiMVector& particle, int pdgId,
		      xAOD::PartonHistory *history);
void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
			     const SG::AuxElement::Decorator<float>& dec_pt,
			     const SG::AuxElement::Decorator<float>& dec_eta,
			     const SG::AuxElement::Decorator<float>& dec_phi,
			     const SG::AuxElement::Decorator<int>& dec_pdgId,
			     xAOD::PartonHistory* history);
void FillDefaultParticleInfo(const SG::AuxElement::Decorator<float>& dec_m,
			     const SG::AuxElement::Decorator<float>& dec_pt,
			     const SG::AuxElement::Decorator<float>& dec_eta,
			     const SG::AuxElement::Decorator<float>& dec_phi,
			     xAOD::PartonHistory* history);

#endif
