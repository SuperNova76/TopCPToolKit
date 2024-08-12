#ifndef LORENTZHELPER_H
#define LORENTZHELPER_H

#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"

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

#endif
