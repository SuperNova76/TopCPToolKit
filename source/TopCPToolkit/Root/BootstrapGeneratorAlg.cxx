/*
    Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

/// @author Baptiste Ravina

#include <TopCPToolkit/BootstrapGeneratorAlg.h>

CP::BootstrapGeneratorAlg::BootstrapGeneratorAlg(const std::string &name,
                                                 ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_nReplicas(1000)
    , m_poisson(1)
{
  declareProperty("nReplicas", m_nReplicas,
                  "number of bootstrapped weights (toys) to generate");
  m_weights.resize(m_nReplicas);
}

long long int CP::BootstrapGeneratorAlg::generateSeed(long long int eventNumber, long int runNumber, int mcChannelNumber) {
  return eventNumber ^ runNumber; // XORing may not be unique!
}

StatusCode CP::BootstrapGeneratorAlg::initialize()
{
  if (m_nReplicas < 0)
  {
    ANA_MSG_ERROR("The number of bootstrapped weights (toys) cannot be negative!");
    return StatusCode::FAILURE;
  }

  ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));
  ANA_CHECK(m_decoration.initialize(m_systematicsList, m_eventInfoHandle));
  ANA_CHECK(m_systematicsList.initialize());

  return StatusCode::SUCCESS;
}

StatusCode CP::BootstrapGeneratorAlg::execute()
{
  for (const auto &sys : m_systematicsList.systematicsVector())
  {
    // retrieve the EventInfo
    const xAOD::EventInfo *evtInfo = nullptr;
    ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

    // TO DO: generate a unique seed from runNumber, eventNumber and DSID!
    m_rng.seed(generateSeed(evtInfo->runNumber(), evtInfo->eventNumber(), evtInfo->mcChannelNumber()));

    // clear the vector of weights
    m_weights.clear();
    // and fill it with Poisson(1)
    for (int i = 0; i < m_nReplicas; i++)
    {
      m_weights[i] = m_poisson(m_rng);
    }

    // decorate weights onto EventInfo
    m_decoration.set(*evtInfo, m_weights, sys);
  }

  return StatusCode::SUCCESS;
}

StatusCode CP::BootstrapGeneratorAlg::finalize()
{
  return StatusCode::SUCCESS;
}
