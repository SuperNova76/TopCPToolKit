#include "TopCPToolkit/RunNuFlowsAlg.h"

namespace top
{

    RunNuFlowsAlg::RunNuFlowsAlg(const std::string &name, ISvcLocator *pSvcLocator)
        : EL::AnaAlgorithm(name, pSvcLocator)
        , m_onnxFilePath("SetMe")
        , m_btagger("SetMe")
    {
        declareProperty("onnxfilepath", m_onnxFilePath, "Path to folder containing even/odd ONNX files");
        declareProperty("btagger", m_btagger, "Btagging algorithm to use. Must support the 'Continuous' WP in order to retrieve the quantile bin.");
    }

    StatusCode RunNuFlowsAlg::initialize()
    {
        ANA_MSG_INFO("Initializing RunNuFlows " << name());
        ANA_MSG_INFO("  --> Using even/odd onnx files in: " << m_onnxFilePath);
        ANA_MSG_INFO("  --> Using btagger: " << m_btagger);

        // The preselection for the event
        ANA_CHECK(m_eventselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));

        // Initialise all input handles
        ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
        ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
        ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
        ANA_CHECK(m_metHandle.initialize(m_systematicsList));
        ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

        // Initialise all selection handles
        ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle, SG::AllowEmpty));
        ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle, SG::AllowEmpty));
        ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));

        // Initialise all output decorations
        ANA_CHECK(m_nu_px_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_nu_py_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_nu_pz_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_anti_nu_px_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_anti_nu_py_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_anti_nu_pz_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
        ANA_CHECK(m_loglik_decor.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));

        // Initialise the systematics list
        ANA_CHECK(m_systematicsList.initialize());

        // Load the NuFlows model and set the btagger
        m_nuflows = std::unique_ptr<top::TopNuFlowsDilepton>(new top::TopNuFlowsDilepton("AsgNuFlowsTool", m_onnxFilePath + "/even.onnx", m_onnxFilePath + "/odd.onnx"));
        m_nuflows->setBtagger(m_btagger);

        return StatusCode::SUCCESS;
    }

    StatusCode RunNuFlowsAlg::execute()
    {

        // Loop over all relevant systematics and execute the syst method
        for (const auto &sys : m_systematicsList.systematicsVector())
            ANA_CHECK(execute_syst(sys));

        return StatusCode::SUCCESS;
    }

    StatusCode RunNuFlowsAlg::execute_syst(const CP::SystematicSet &sys)
    {
        // Load the event information, especially with the run number
        const xAOD::EventInfo *evtInfo = nullptr;
        ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));
        unsigned long long eventNumber = evtInfo->eventNumber();

        // default outputs
        m_nu_px_decor.set(*evtInfo, -999, sys);
        m_nu_py_decor.set(*evtInfo, -999, sys);
        m_nu_pz_decor.set(*evtInfo, -999, sys);
        m_anti_nu_px_decor.set(*evtInfo, -999, sys);
        m_anti_nu_py_decor.set(*evtInfo, -999, sys);
        m_anti_nu_pz_decor.set(*evtInfo, -999, sys);
        m_loglik_decor.set(*evtInfo, -999, sys);

        // Skip the event if it does not pass the selection
        if (m_eventselection && !m_eventselection.getBool(*evtInfo, sys))
            return StatusCode::SUCCESS;

        // Load the objects
        const xAOD::ElectronContainer *electrons = nullptr;
        const xAOD::MuonContainer *muons = nullptr;
        const xAOD::JetContainer *jets = nullptr;
        const xAOD::MissingETContainer *met = nullptr;
        ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
        ANA_CHECK(m_muonsHandle.retrieve(muons, sys));
        ANA_CHECK(m_jetsHandle.retrieve(jets, sys));
        ANA_CHECK(m_metHandle.retrieve(met, sys));

        // Get the selected electrons
        ConstDataVector<xAOD::ElectronContainer> selected_electrons(SG::VIEW_ELEMENTS);
        for (const xAOD::Electron *el : *electrons) {
            if (m_electronSelection.getBool(*el, sys))
                selected_electrons.push_back(el);
        }

        // Get the selected muons
        ConstDataVector<xAOD::MuonContainer> selected_muons(SG::VIEW_ELEMENTS);
        for (const xAOD::Muon *mu : *muons) {
            if (m_muonSelection.getBool(*mu, sys))
                selected_muons.push_back(mu);
        }

        // Get the selected jets
        ConstDataVector<xAOD::JetContainer> selected_jets(SG::VIEW_ELEMENTS);
        for (const xAOD::Jet *jet : *jets) {
            if (m_jetSelection.getBool(*jet, sys))
                selected_jets.push_back(jet);
        }

        // Load the MET
        float met_mpx = (*met)["Final"]->mpx();
        float met_mpy = (*met)["Final"]->mpy();
        float met_sumet = (*met)["Final"]->sumet();

        // Run Nuflows with the selected object
        m_nuflows->Sample(
            selected_electrons,
            selected_muons,
            selected_jets,
            met_mpx,
            met_mpy,
            met_sumet,
            eventNumber
        );

        // Decorare EventInfo with the output
        std::vector<float> sample = m_nuflows->GetSample();
        m_nu_px_decor.set(*evtInfo, sample[0], sys);
        m_nu_py_decor.set(*evtInfo, sample[1], sys);
        m_nu_pz_decor.set(*evtInfo, sample[2], sys);
        m_anti_nu_px_decor.set(*evtInfo, sample[3], sys);
        m_anti_nu_py_decor.set(*evtInfo, sample[4], sys);
        m_anti_nu_pz_decor.set(*evtInfo, sample[5], sys);
        m_loglik_decor.set(*evtInfo, sample[6], sys);

        return StatusCode::SUCCESS;
    }

    StatusCode RunNuFlowsAlg::finalize()
    {
        ANA_MSG_INFO("Finalizing RunNuFlows");
        return StatusCode::SUCCESS;
    }

} // namespace top
