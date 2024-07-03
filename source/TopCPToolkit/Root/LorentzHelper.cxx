#include <AsgMessaging/MessageCheck.h>
#include "xAODTruth/xAODTruthHelpers.h"
#include "xAODTruth/TruthParticle.h"
#include "Math/Vector4D.h"

ROOT::Math::PtEtaPhiMVector GetPtEtaPhiMfromTruth(const xAOD::TruthParticle *TruthParticle){
    ROOT::Math::PtEtaPhiMVector MassSafeVector(TruthParticle->pt(), //float px and py cast to double to build pT 
                                               TruthParticle->eta(), //double
                                               TruthParticle->phi(), //double
                                               TruthParticle->m()); //double (generator mass)
    return MassSafeVector;
}

ROOT::Math::PxPyPzMVector GetPxPyPzMfromTruth(const xAOD::TruthParticle *TruthParticle){
    ROOT::Math::PxPyPzMVector MassSafeVector(TruthParticle->px(), //float
                                             TruthParticle->py(), //float
                                             TruthParticle->pz(), //float
                                             TruthParticle->m()); //double (generator mass)
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

double SliceLorentz(ROOT::Math::PtEtaPhiMVector &m_p, int i){
    double coord1, coord2, coord3, coord4;
    m_p.GetCoordinates(coord1, coord2, coord3, coord4);
    switch(i) {
    case 0:
        return coord1;
        break;
    case 1:
        return coord2;
        break;
    case 2:
        return coord3;
        break;
    case 3:
        return coord4;
        break;
    default:
        asg::msgUserCode::ANA_MSG_WARNING ("LorentzHelper WARNING: Bad index, there are only 4 elements of a 4-vector..., returning 0!");
        return 0.0;
    }
}
