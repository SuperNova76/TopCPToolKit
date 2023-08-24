#include "TopEventSelection/MLLSelectorAlg.h"

namespace top {

  MLLSelectorAlg::MLLSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator)
  : EL::AnaAlgorithm(name, pSvcLocator)
  , m_mllref(0.)
  , m_sign("SetMe")
  {
    declareProperty ("refMLL", m_mllref, "MLL cut (in MeV)");
    declareProperty ("sign", m_sign, "comparison sign to use");
  }

  StatusCode MLLSelectorAlg::initialize() {
    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_decoration.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_systematicsList.initialize());

    m_signEnum = SignEnum::stringToOperator.at( m_sign );

    return StatusCode::SUCCESS;
  }

  StatusCode MLLSelectorAlg::execute() {
    for (const auto &sys : m_systematicsList.systematicsVector()) {
      // retrieve the EventInfo
      const xAOD::EventInfo *evtInfo = nullptr;
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

      // default-decorate EventInfo
      m_decoration.setBool(*evtInfo, 0, sys);

      // check the preselection
      if (m_preselection && !m_preselection.getBool(*evtInfo, sys))
        continue;

      // retrieve the electron container
      const xAOD::ElectronContainer *electrons = nullptr;
      ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
      // retrieve the electron container
      const xAOD::MuonContainer *muons = nullptr;
      ANA_CHECK(m_muonsHandle.retrieve(muons, sys));

      // apply the requested selection
      ConstDataVector<xAOD::ElectronContainer> selected_electrons(SG::VIEW_ELEMENTS);
      ConstDataVector<xAOD::MuonContainer> selected_muons(SG::VIEW_ELEMENTS);
      for (const xAOD::Electron *el : *electrons) {
        if (!m_electronSelection || m_electronSelection.getBool(*el, sys)) selected_electrons.push_back(el);
      }
      for (const xAOD::Muon *mu : *muons) {
        if (!m_muonSelection || m_muonSelection.getBool(*mu, sys)) selected_muons.push_back(mu);
      }

      // retrieve the two leptons
      const xAOD::IParticle* lepton0 = nullptr;
      const xAOD::IParticle* lepton1 = nullptr;
      if (selected_electrons.size() == 2 ) {
        lepton0 = selected_electrons.at(0);
        lepton1 = selected_electrons.at(1);
      } else if (selected_muons.size() == 2 ) {
        lepton0 = selected_muons.at(0);
        lepton1 = selected_muons.at(1);
      } else if (selected_electrons.size() == 1 && selected_muons.size() == 1 ) {
        lepton0 = selected_electrons.at(0);
        lepton1 = selected_muons.at(0);
      } else {
        ATH_MSG_ERROR("Didn't find two charged leptons in the event, cannot compute MLL!");
        return StatusCode::FAILURE;
      }

      // compute MLL
      float mll = (lepton0->p4() + lepton1->p4()).M();

      // calculate decision
      bool decision = SignEnum::checkValue(m_mllref, m_signEnum, mll);
      m_decoration.setBool(*evtInfo, decision, sys);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode MLLSelectorAlg::finalize() {
    return StatusCode::SUCCESS;
  }
} // namespace top
