#include "PartonHistory/CalcPartonHistory.h"
#include "PartonHistory/PartonHistoryUtils.h"
#include "VectorHelpers/DecoratorHelpers.h"

namespace top {
  using ROOT::Math::PtEtaPhiMVector;

  void CalcPartonHistory::FillHiggsPartonHistory(xAOD::PartonHistory* PartonHistory, PartonDecorator& dec) {
    PtEtaPhiMVector v;
    int pdgId = 0;
    dec.decorateDefault("MC_H_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_decay1_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_decay2_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_decay1_beforeFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_decay2_beforeFSR", PartonHistory);

    dec.decorateDefault("MC_H_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_decay1_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay1_decay2_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_decay1_afterFSR", PartonHistory);
    dec.decorateDefault("MC_Hdecay2_decay2_afterFSR", PartonHistory);

    if ( RetrieveParticleInfo("MC_H_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_H_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_Decay1_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_decay1_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_Decay2_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_decay2_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_Decay1_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_decay1_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_Decay2_beforeFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_decay2_beforeFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_H_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_H_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_Decay1_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_decay1_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay1_Decay2_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay1_decay2_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_Decay1_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_decay1_afterFSR", v, pdgId, PartonHistory);
    }
    if ( RetrieveParticleInfo("MC_HDecay2_Decay2_afterFSR", v, pdgId)) {
      dec.decorateParticle("MC_Hdecay2_decay2_afterFSR", v, pdgId, PartonHistory);
    }
  }
}
