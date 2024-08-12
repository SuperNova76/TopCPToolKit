#include <AsgMessaging/MessageCheck.h>
#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "Math/Vector4D.h"
#include "VectorHelpers/LorentzHelper.h"

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Electron *Lepton){
  ROOT::Math::PtEtaPhiMVector MassSafeVector(Lepton->pt(), //float px and py cast to double to build pT
					     Lepton->eta(), //double
					     Lepton->phi(), //double
					     Lepton->m()); //double
  return MassSafeVector;
}

ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Electron *Lepton){
  ROOT::Math::PtEtaPhiEVector EnergySafeVector(Lepton->pt(), //float px and py cast to double to build pT
					       Lepton->eta(), //double
					       Lepton->phi(), //double
					       Lepton->e()); //double
  return EnergySafeVector;
}

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromLepton(const xAOD::Muon *Lepton){
  ROOT::Math::PtEtaPhiMVector MassSafeVector(Lepton->pt(), //float px and py cast to double to build pT
					     Lepton->eta(), //double
					     Lepton->phi(), //double
					     Lepton->m()); //double
  return MassSafeVector;
}

ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromLepton(const xAOD::Muon *Lepton){
  ROOT::Math::PtEtaPhiEVector EnergySafeVector(Lepton->pt(), //float px and py cast to double to build pT
					       Lepton->eta(), //double
					       Lepton->phi(), //double
					       Lepton->e()); //double
  return EnergySafeVector;
}

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromJet(const xAOD::Jet *Jet){
  ROOT::Math::PtEtaPhiMVector MassSafeVector(Jet->pt(), //float px and py cast to double to build pT
					     Jet->eta(), //double
					     Jet->phi(), //double
					     Jet->m()); //double
  return MassSafeVector;
}

ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromJet(const xAOD::Jet *Jet){
  ROOT::Math::PtEtaPhiEVector EnergySafeVector(Jet->pt(), //float px and py cast to double to build pT
					       Jet->eta(), //double
					       Jet->phi(), //double
					       Jet->e()); //double
  return EnergySafeVector;
}

ROOT::Math::PxPyPzMVector GetPxPyPzMfromTruth(const xAOD::TruthParticle *TruthParticle){
  ROOT::Math::PxPyPzMVector MassSafeVector(TruthParticle->px(), //float
					   TruthParticle->py(), //float
					   TruthParticle->pz(), //float
					   TruthParticle->m()); //double (generator mass)
  return MassSafeVector;
}

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromTruth(const xAOD::TruthParticle *TruthParticle){
  ROOT::Math::PtEtaPhiMVector MassSafeVector(TruthParticle->pt(), //float px and py cast to double to build pT
					     TruthParticle->eta(), //double
					     TruthParticle->phi(), //double
					     TruthParticle->m()); //double (generator energy)
  return MassSafeVector;
}

ROOT::Math::PtEtaPhiEVector GetPtEtaPhiEfromTruth(const xAOD::TruthParticle *TruthParticle){
  asg::msgUserCode::ANA_MSG_WARNING ("LorentzHelper WARNING: We can't guarantee the mass from this 4-vector is correct, consider using GetPtEtaPhiMfromTruth");
  ROOT::Math::PtEtaPhiEVector EnergySafeVector(TruthParticle->pt(), //float px and py cast to double to build pT
					       TruthParticle->eta(), //double
					       TruthParticle->phi(), //double
					       TruthParticle->e()); //double (generator energy)
  return EnergySafeVector;
}

ROOT::Math::PxPyPzEVector GetPxPyPzEfromTruth(const xAOD::TruthParticle *TruthParticle){
  asg::msgUserCode::ANA_MSG_WARNING ("LorentzHelper WARNING: We can't guarantee the mass from this 4-vector is correct, consider using GetPxPyPzMfromTruth");
  ROOT::Math::PxPyPzEVector EnergySafeVector(TruthParticle->px(), //float px and py cast to double to build pT
					     TruthParticle->py(), //double
					     TruthParticle->pz(), //double
					     TruthParticle->e()); //double (generator energy)
  return EnergySafeVector;
}

ROOT::Math::PtEtaPhiMVector TLorentzToPtEtaPhiM(const TLorentzVector& p){
  asg::msgUserCode::ANA_MSG_WARNING ("LorentzHelper WARNING: can't guarantee mass from TLorentzVector object will be calculated accurately, consider using ROOT::Math::PtEtaPhiMVector or ROOT::Math::PxPyPzMVector instead");
  ROOT::Math::PtEtaPhiMVector MassSafeVector(p.Pt(),
					     p.Eta(),
					     p.Phi(),
					     p.M());
  return MassSafeVector;
}
