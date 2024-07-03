#ifndef MINIHVV_LORENTZHELPER_H
#define MINIHVV_LORENTZHELPER_H

#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "Math/Vector4D.h"

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromTruth(const xAOD::TruthParticle *TruthParticle);

ROOT::Math::PxPyPzMVector GetPxPyPzMfromTruth(const xAOD::TruthParticle *TruthParticle);

ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromTruth(const xAOD::TruthParticle *TruthParticle);

ROOT::Math::PxPyPzEVector GetPxPyPzEfromTruth(const xAOD::TruthParticle *TruthParticle);

ROOT::Math::PtEtaPhiMVector TLorentzToPtEtaPhiM(const TLorentzVector& p);

//ToDo Typedef this to work for all LorentzVectors
double SliceLorentz(ROOT::Math::PtEtaPhiMVector &m_p, int i);

#endif
