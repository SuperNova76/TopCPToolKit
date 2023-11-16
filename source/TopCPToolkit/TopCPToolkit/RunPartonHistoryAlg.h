#ifndef TOPPARTONS_RUNPARTONHISTORYALG_H
#define TOPPARTONS_RUNPARTONHISTORYALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>

// EDM include(s):
#include "AthContainers/DataVector.h"
#include "AthContainers/AuxElement.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/CLASS_DEF.h"
#include <vector>

// TopParton histories
#include "TopPartons/CalcTopPartonHistory.h"
#include "TopPartons/CalcTtbarPartonHistory.h"
#include "TopPartons/CalcTtbarLightPartonHistory.h"
#include "TopPartons/CalcTTZPartonHistory.h"
#include "TopPartons/CalcTthPartonHistory.h"

namespace top {

  class RunPartonHistoryAlg final : public EL::AnaAlgorithm {

  public:
    RunPartonHistoryAlg(const std::string &name, ISvcLocator *pSvcLocator);
    virtual StatusCode initialize() override;
    virtual StatusCode execute() override;
    virtual StatusCode finalize() override;

 private:
    const std::string m_topPartonScheme;
    std::unique_ptr<CalcTopPartonHistory> m_topPartonHistory;

  };

} // namespace top

#endif
