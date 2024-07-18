#include "TopCPToolkit/TopSpinDensityMatrixAlg.h"
#include "TopCPToolkit/SpinHelpers.h"

namespace top {

  TopSpinDensityMatrixAlg::TopSpinDensityMatrixAlg(const std::string &name,
                                                   ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator) {}

  StatusCode TopSpinDensityMatrixAlg::initialize() {

    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));
    ANA_CHECK(m_selection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));

    ANA_CHECK(m_top.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_tbar.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_top_analyser.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_tbar_analyser.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_cos_theta_helicity_p.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_theta_helicity_m.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_theta_transverse_p.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_theta_transverse_m.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_theta_raxis_p.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_theta_raxis_m.initialize(m_systematicsList, m_eventInfoHandle));
    ANA_CHECK(m_cos_phi.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode TopSpinDensityMatrixAlg::execute() {

    for (const auto &sys : m_systematicsList.systematicsVector()) {

      // retrieve the EventInfo
      const xAOD::EventInfo *evtInfo = nullptr;
      ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

      // default-decorate EventInfo
      float defaultvalue = -999.;
      m_cos_theta_helicity_p.set(*evtInfo, defaultvalue, sys);
      m_cos_theta_helicity_m.set(*evtInfo, defaultvalue, sys);
      m_cos_theta_transverse_p.set(*evtInfo, defaultvalue, sys);
      m_cos_theta_transverse_m.set(*evtInfo, defaultvalue, sys);
      m_cos_theta_raxis_p.set(*evtInfo, defaultvalue, sys);
      m_cos_theta_raxis_m.set(*evtInfo, defaultvalue, sys);
      m_cos_phi.set(*evtInfo, defaultvalue, sys);

      // check the selection
      if (m_selection && !m_selection.getBool(*evtInfo, sys))
	continue;

      // collect the necessary TLorentzVectors
      TLorentzVector top, tbar, top_analyser, tbar_analyser;
      top           = m_top.get(*evtInfo, sys);
      tbar          = m_tbar.get(*evtInfo, sys);
      top_analyser  = m_top_analyser.get(*evtInfo, sys);
      tbar_analyser = m_tbar_analyser.get(*evtInfo, sys);

      // the ttbar ZMF
      TLorentzVector ttbar = top + tbar;

      // compute the spin observables
      m_cos_theta_helicity_p.set(*evtInfo,
				  SpinHelpers::cos_theta_helicity_plus(   top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_theta_helicity_m.set(*evtInfo,
				  SpinHelpers::cos_theta_helicity_minus(  top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_theta_transverse_p.set(*evtInfo,
				  SpinHelpers::cos_theta_transverse_plus( top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_theta_transverse_m.set(*evtInfo,
				  SpinHelpers::cos_theta_transverse_minus(top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_theta_raxis_p.set(*evtInfo,
          SpinHelpers::cos_theta_raxis_plus(      top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_theta_raxis_m.set(*evtInfo,
			    SpinHelpers::cos_theta_raxis_minus(     top, tbar, ttbar, top_analyser, tbar_analyser), sys);
      m_cos_phi.set(*evtInfo,
		      SpinHelpers::cos_phi(                   top, tbar, ttbar, top_analyser, tbar_analyser), sys);
    }

    return StatusCode::SUCCESS;
  }

} // namespace
