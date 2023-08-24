#include "TopEventSelection/ChargeSelectorAlg.h"

namespace top {

  ChargeSelectorAlg::ChargeSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator)
  : EL::AnaAlgorithm(name, pSvcLocator)
  , m_OSmode(true)
  {
    declareProperty ("OS", m_OSmode, "whether to request 2 opposite-sign leptons");
  }

  StatusCode ChargeSelectorAlg::initialize() {
    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_decoration.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode ChargeSelectorAlg::execute() {
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

      // check there are only two leptons
      if (selected_electrons.size() + selected_muons.size() != 2 ) {
        ATH_MSG_ERROR("Exactly two leptons are required to check whether the event is OS or SS!");
        return StatusCode::FAILURE;
      }

      // compute the charge
      int total_charge = 0;
      for (const xAOD::Electron *el : selected_electrons) total_charge += el->charge();
      for (const xAOD::Muon *mu : selected_muons) total_charge += mu->charge();

      // compare to the requested mode
      bool decision = m_OSmode ? total_charge == 0 : std::abs(total_charge) == 1;
      m_decoration.setBool(*evtInfo, decision, sys);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode ChargeSelectorAlg::finalize() {
    return StatusCode::SUCCESS;
  }
} // namespace top
