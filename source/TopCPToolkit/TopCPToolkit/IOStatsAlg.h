#ifndef IOSTATSALG_H
#define IOSTATSALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <AsgTools/PropertyWrapper.h>

namespace top {

  class IOStatsAlg final : public EL::AnaAlgorithm {

  public:

    // Constructor
    using EL::AnaAlgorithm::AnaAlgorithm;

    // finalize function: run once at the end of a job after event loop
    virtual StatusCode finalize() override;

  private:

    Gaudi::Property<bool> m_autoIncludeLinks {this, "autoIncludeLinks", false, "whether to add all ElementLink variables"};

  };

} // namespace top

#endif