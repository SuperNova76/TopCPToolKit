/*
  Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

#include <TopCPToolkit/ExtraParticleDecorationAlg.h>
#include <TopEventSelection/NObjectSelectorAlg.h>
#include <TopEventSelection/METSelectorAlg.h>
#include <TopEventSelection/MWTSelectorAlg.h>
#include <TopEventSelection/METMWTSelectorAlg.h>
#include <TopEventSelection/MLLSelectorAlg.h>
#include <TopEventSelection/MLLWindowSelectorAlg.h>
#include <TopEventSelection/ChargeSelectorAlg.h>
#include <TopEventSelection/SaveFilterAlg.h>
#include <TopCPToolkit/LeptonSFCalculatorAlg.h>
#include <TopCPToolkit/KLFitterAlg.h>
#include <TopCPToolkit/KLFitterFinalizeOutputAlg.h>
#include <TopCPToolkit/ParticleLevelAlg.h>
#include <TopCPToolkit/RunPartonHistoryAlg.h>
#include <TopCPToolkit/RunSpaNetAlg.h>
#include <TopCPToolkit/RunTtbarNNLORecursiveRewAlg.h>

DECLARE_COMPONENT (TtbarCPalgoAnalysis)
