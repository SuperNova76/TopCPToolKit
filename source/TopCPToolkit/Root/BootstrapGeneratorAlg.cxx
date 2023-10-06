/*
    Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

/// @author Baptiste Ravina

#include <TopCPToolkit/BootstrapGeneratorAlg.h>

CP::BootstrapGeneratorAlg::BootstrapGeneratorAlg(const std::string &name,
                                                 ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_nReplicas(1000)
{
  declareProperty("nReplicas", m_nReplicas,
                  "number of bootstrapped weights (toys) to generate");
  m_weights.resize(m_nReplicas);
}

unsigned long int CP::BootstrapGeneratorAlg::fnv1a_32(const void *buffer, size_t size, unsigned long offset_basis) {
  unsigned long h = offset_basis;
  unsigned char *p = (unsigned char *)buffer;
  for (size_t i = 0; i < size; i++) {
    h ^= p[i];
    h *= prime;
  }
  return h;
}

unsigned long int CP::BootstrapGeneratorAlg::generateSeed(long long int eventNumber, long int runNumber, int mcChannelNumber)
{
  unsigned long hash = fnv1a_32(&runNumber, sizeof(runNumber), offset);
  hash = fnv1a_32(&eventNumber, sizeof(eventNumber), hash);
  hash = fnv1a_32(&mcChannelNumber, sizeof(mcChannelNumber), hash);
  return hash;
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

    // generate a unique seed from runNumber, eventNumber and DSID!
    m_rng.SetSeed(generateSeed(evtInfo->eventNumber(), evtInfo->runNumber(), evtInfo->mcChannelNumber()));

    // clear the vector of weights
    m_weights.clear();
    // and fill it with Poisson(1)
    for (int i = 0; i < m_nReplicas; i++)
    {
      m_weights[i] = m_rng.Poisson(1);
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
