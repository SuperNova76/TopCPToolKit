#ifndef LORENTZHELPER_H
#define LORENTZHELPER_H

// Include necessary header files
#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "Math/Vector4D.h"
#include "Math/VectorUtil.h"

// Using directives for convenience with ROOT::Math vector types
using ROOT::Math::PtEtaPhiMVector;
using ROOT::Math::PtEtaPhiEVector;
using ROOT::Math::PxPyPzMVector;
using ROOT::Math::PxPyPzEVector;

PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Electron *Lepton);
PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Electron *Lepton);
PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Muon *Lepton);
PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Muon *Lepton);
PtEtaPhiMVector GetPtEtaPhiMfromJet(const xAOD::Jet *Jet);
PtEtaPhiEVector GetPtEtaPhiEfromJet(const xAOD::Jet *Jet);
PtEtaPhiMVector GetPtEtaPhiMfromTruth(const xAOD::TruthParticle *TruthParticle);
PxPyPzMVector GetPxPyPzMfromTruth(const xAOD::TruthParticle *TruthParticle);
PtEtaPhiEVector GetPtEtaPhiEfromTruth(const xAOD::TruthParticle *TruthParticle);
PxPyPzEVector GetPxPyPzEfromTruth(const xAOD::TruthParticle *TruthParticle);
PtEtaPhiMVector TLorentzToPtEtaPhiM(const TLorentzVector& p);

#endif
