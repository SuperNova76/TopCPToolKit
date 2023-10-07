/*
  Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
*/

/// @author Baptiste Ravina

#ifndef TOPCPTOOLKIT__BOOTSTRAP_GENERATOR_ALG_H
#define TOPCPTOOLKIT__BOOTSTRAP_GENERATOR_ALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include <xAODEventInfo/EventInfo.h>

#include <TRandom3.h>

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
    unsigned long int generateSeed(long long int eventNumber, long int runNumber, int mcChannelNumber);

  public:
    unsigned long int fnv1a_32(const void *buffer, size_t size, unsigned long offset_basis);

  private:
    static constexpr unsigned long offset = 2166136261u;
    static constexpr unsigned long prime = 16777619u;

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
    TRandom3 m_rng;

    /// \brief the vector of bootstrap replica weights
  private:
    std::vector<short int> m_weights;

    /// \brief the output decoration
  private:
    SysWriteDecorHandle<std::vector<short int>> m_decoration{
        this, "decorationName", "bootstrapWeights_%SYS%", "decoration name for the vector of bootstrapped weights"};
  };
} // namespace CP

#endif
