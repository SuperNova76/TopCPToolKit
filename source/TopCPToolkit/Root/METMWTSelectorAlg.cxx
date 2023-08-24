#include "TopEventSelection/METMWTSelectorAlg.h"

namespace top {

  METMWTSelectorAlg::METMWTSelectorAlg(const std::string &name, ISvcLocator *pSvcLocator)
  : EL::AnaAlgorithm(name, pSvcLocator)
  , m_sumref(0.)
  , m_sign("SetMe")
  {
    declareProperty ("refMETMWT", m_sumref, "MET+MWT cut (in MeV)");
    declareProperty ("sign", m_sign, "comparison sign to use");
  }

  StatusCode METMWTSelectorAlg::initialize() {
    ANA_CHECK(m_metHandle.initialize(m_systematicsList));
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

  StatusCode METMWTSelectorAlg::execute() {
    for (const auto &sys : m_systematicsList.systematicsVector()) {
      // retrieve the EventInfo
      const xAOD::EventInfo *evtInfo = nullptr;
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

      // default-decorate EventInfo
      m_decoration.setBool(*evtInfo, 0, sys);

      // check the preselection
      if (m_preselection && !m_preselection.getBool(*evtInfo, sys))
        continue;
      
      // retrieve the MET container
      const xAOD::MissingETContainer *met = nullptr;
      ANA_CHECK(m_metHandle.retrieve(met, sys));
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

      // compute the W boson transverse mass
      float etmiss_pt = (*met)["Final"]->met();
      float etmiss_phi = (*met)["Final"]->phi();
      float lep_pt, lep_phi;
      if (selected_electrons.size()) {
        lep_pt  = selected_electrons[0]->pt();
        lep_phi = selected_electrons[0]->phi();
      } else if (selected_muons.size()) {
        lep_pt  = selected_muons[0]->pt();
        lep_phi = selected_muons[0]->phi();
      } else {
        ATH_MSG_ERROR("No charged lepton in the event, cannot compute MWT!");
        return StatusCode::FAILURE;
      }
      float mwt = sqrt(2. * lep_pt * etmiss_pt * (1. - std::cos(lep_phi - etmiss_phi)));

      // compute the sum
      float sum = etmiss_pt + mwt;

      // calculate decision
      bool decision = SignEnum::checkValue(m_sumref, m_signEnum, sum);
      m_decoration.setBool(*evtInfo, decision, sys);
    }
    return StatusCode::SUCCESS;
  }

  StatusCode METMWTSelectorAlg::finalize() {
    return StatusCode::SUCCESS;
  }
} // namespace top
