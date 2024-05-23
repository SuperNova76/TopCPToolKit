/*
  Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

#include <TopCPToolkit/ExtraParticleDecorationAlg.h>
#include <TopCPToolkit/ExtraPhotonDecorationAlg.h>
#include <TopCPToolkit/LeptonSFCalculatorAlg.h>
#include <TopCPToolkit/KLFitterAlg.h>
#include <TopCPToolkit/KLFitterFinalizeOutputAlg.h>
#include <TopCPToolkit/ParticleLevelAlg.h>
#include <TopCPToolkit/PartonToJetsMatchAlg.h>
#include <TopCPToolkit/RunPartonHistoryAlg.h>
#include <TopCPToolkit/RunSpaNetAlg.h>
#include <TopCPToolkit/RunTtbarNNLORecursiveRewAlg.h>
#include <TopCPToolkit/JetMatchingAlg.h>
#include <TopCPToolkit/JetReclusteringAlg.h>
#include <TopCPToolkit/DiTauMassCalculatorAlg.h>
#include <TopCPToolkit/BTaggingScoresAlg.h>
#include <TopCPToolkit/SVMassAlg.h>
#include <TopCPToolkit/FakeBkgCalculatorAlg.h>
#include <TopCPToolkit/VGammaORAlg.h>
#include <TopCPToolkit/IOStatsAlg.h>

DECLARE_COMPONENT (SVMassAlg)
DECLARE_COMPONENT (top::IOStatsAlg)
DECLARE_COMPONENT (top::RunTtbarNNLORecursiveRewAlg)
DECLARE_COMPONENT (top::RunSpaNetAlg)
DECLARE_COMPONENT (top::RunPartonHistoryAlg)
DECLARE_COMPONENT (top::PartonToJetsMatchAlg)
DECLARE_COMPONENT (top::ParticleLevelAlg)
DECLARE_COMPONENT (top::LeptonSFCalculatorAlg)
DECLARE_COMPONENT (top::KLFitterFinalizeOutputAlg)
DECLARE_COMPONENT (top::KLFitterAlg)
DECLARE_COMPONENT (top::JetMatchingAlg)
DECLARE_COMPONENT (top::JetReclusteringAlg)
DECLARE_COMPONENT (top::ExtraParticleDecorationAlg)
DECLARE_COMPONENT (top::ExtraPhotonDecorationAlg)
DECLARE_COMPONENT (DiTauMassCalculatorAlg)
DECLARE_COMPONENT (BTaggingScoresAlg)
