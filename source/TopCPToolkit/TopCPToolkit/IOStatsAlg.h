#ifndef IOSTATSALG_H
#define IOSTATSALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>

namespace top {

  class IOStatsAlg final : public EL::AnaAlgorithm {

  public:

    // Constructor
    IOStatsAlg(const std::string& name, ISvcLocator *pSvcLocator);

    // initialize function: run once at the start of a job before event loop 
    virtual StatusCode initialize() override { return StatusCode::SUCCESS; };

    // execute function: run for each event and loop over all systematics
    virtual StatusCode execute() override { return StatusCode::SUCCESS; };

    // finalize function: run once at the end of a job after event loop
    virtual StatusCode finalize() override;

  private:

    bool m_autoIncludeLinks {false};

  };

} // namespace top

#endif