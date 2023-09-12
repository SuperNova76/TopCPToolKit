/*
  Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

/// @author Baptiste Ravina

#ifndef TOPCPTOOLKIT__BOOTSTRAP_GENERATOR_ALG_H
#define TOPCPTOOLKIT__BOOTSTRAP_GENERATOR_ALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <xAODEventInfo/EventInfo.h>

#include <random>

namespace CP
{
  /// \brief an algorithm to compute per-event bootstrap replica weights

  class BootstrapGeneratorAlg final : public EL::AnaAlgorithm
  {
    /// \brief the standard constructor
  public:
    BootstrapGeneratorAlg(const std::string &name,
                          ISvcLocator *pSvcLocator);

  public:
    StatusCode initialize() override;

  public:
    StatusCode execute() override;

  public:
    StatusCode finalize() override;

  public:
    long long int generateSeed(long long int eventNumber, long int runNumber, int mcChannelNumber);

    /// \brief the systematics list we run
  private:
    SysListHandle m_systematicsList{this};

    /// \brief the EventInfo container
  private:
    SysReadHandle<xAOD::EventInfo> m_eventInfoHandle{
        this, "eventInfo", "EventInfo", "the EventInfo container"};

    /// \brief the number of bootstrap replicas
  private:
    int m_nReplicas;

    /// \brief the random number generator (Mersenne Twister)
  private:
    std::mt19937 m_rng;

    /// \brief a Poisson distribution with central value 1
  private:
    std::poisson_distribution<int> m_poisson(1.0);

    /// \brief the vector of bootstrap replica weights
  private:
    std::vector<int> m_weights;

    /// \brief the output decoration
    SysWriteDecorHandle m_decoration{
        this, "decorationName", "bootstrapWeights_%SYS%", "decoration name for the vector of bootstrapped weights"};
  };
} // namespace CP

#endif