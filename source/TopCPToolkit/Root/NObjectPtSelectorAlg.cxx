#include "TopEventSelection/NObjectPtSelectorAlg.h"

namespace top {

  NObjectPtSelectorAlg::NObjectPtSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_ptmin(0.)
    , m_sign("SetMe")
    , m_count(0)
    {
      declareProperty ("minPt", m_ptmin, "minimum pT (in MeV)");
      declareProperty ("sign", m_sign, "comparison sign to use");
      declareProperty ("count", m_count, "count value");
    }

  StatusCode NObjectPtSelectorAlg::initialize() {
    ANA_CHECK(m_objectsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_objectSelection.initialize(m_systematicsList, m_objectsHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_decoration.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_systematicsList.initialize());

    m_signEnum = SignEnum::stringToOperator.at( m_sign );

    return StatusCode::SUCCESS;
  }

  StatusCode NObjectPtSelectorAlg::execute() {
    for (const auto &sys : m_systematicsList.systematicsVector()) {
      // retrieve the EventInfo
      const xAOD::EventInfo *evtInfo = nullptr;
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

      // default-decorate EventInfo
      m_decoration.setBool(*evtInfo, 0, sys);

      // check the preselection
      if (m_preselection && !m_preselection.getBool(*evtInfo, sys))
        continue;

      // retrieve the object container
      const xAOD::IParticleContainer *objects = nullptr;
      ANA_CHECK(m_objectsHandle.retrieve(objects, sys));

      // apply the requested selection
      ConstDataVector<xAOD::IParticleContainer> selected_objects(SG::VIEW_ELEMENTS);
      for (const xAOD::IParticle *obj : *objects) {
        if (!m_objectSelection || m_objectSelection.getBool(*obj, sys)) selected_objects.push_back(obj);
      }

      // calculate decision
      auto func = [&](const xAOD::IParticle* objPtr) {
        return objPtr->pt() > m_ptmin;
      };
      int count = std::count_if(selected_objects.begin(), selected_objects.end(), func);
      bool decision = SignEnum::checkValue(m_count, m_signEnum, count);
      m_decoration.setBool(*evtInfo, decision, sys);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode NObjectPtSelectorAlg::finalize() {
    return StatusCode::SUCCESS;
  }
} // namespace top
