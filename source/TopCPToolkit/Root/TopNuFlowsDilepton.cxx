#include "AthContainers/ConstDataVector.h"
#include "TopNuFlows/Dilepton.h"

namespace top {

TopNuFlowsDilepton::TopNuFlowsDilepton(const std::string &name, std::string model_even,
                                       std::string model_odd)
    : ONNXWrapper(name, {model_even, model_odd}) {}

void TopNuFlowsDilepton::Sample(ConstDataVector<xAOD::ElectronContainer> &electrons,
                                ConstDataVector<xAOD::MuonContainer> &muons,
                                ConstDataVector<xAOD::JetContainer> &jets,
                                float met_mpx, float met_mpy, float met_sumet,
                                unsigned long long eventNumber) {
    // Clear all inputs to the model
    m_input_lep.clear();
    m_input_jet.clear();
    m_input_met.clear();
    m_input_misc.clear();

    // Fill in the leptons
    for (const auto &l : electrons) {
        std::vector<float> v = {static_cast<float>(l->p4().Px()),
                                static_cast<float>(l->p4().Py()),
                                static_cast<float>(l->p4().Pz()),
                                static_cast<float>(std::log(l->p4().E())),
                                static_cast<float>(l->charge()),
                                0.0};  // Flavor = 0 for electrons
        m_input_lep.push_back(v);
    }
    for (const auto &l : muons) {
        std::vector<float> v = {static_cast<float>(l->p4().Px()),
                                static_cast<float>(l->p4().Py()),
                                static_cast<float>(l->p4().Pz()),
                                static_cast<float>(std::log(l->p4().E())),
                                static_cast<float>(l->charge()),
                                0.0};  // Flavor = 0 for electrons
        m_input_lep.push_back(v);
    }

    // Fill in the jets
    for (const auto &j : jets) {
        std::vector<float> v = {static_cast<float>(j->p4().Px()),
                                static_cast<float>(j->p4().Py()),
                                static_cast<float>(j->p4().Pz()),
                                static_cast<float>(std::log(j->p4().E())),
                                static_cast<float>(std::log(j->p4().M())),
                                static_cast<float>(j->auxdataConst<int>("ftag_quantile_" + m_btagger + "_Continuous"))};
        m_input_jet.push_back(v);
    }

    // MET information
    m_input_met.push_back(met_mpx);
    m_input_met.push_back(met_mpy);
    m_input_met.push_back(met_sumet);

    // Misc information (particle multiplicities)
    m_input_misc.push_back(static_cast<float>(electrons.size()));
    m_input_misc.push_back(static_cast<float>(muons.size()));
    m_input_misc.push_back(static_cast<float>(jets.size()));

    // Create the Ort::Value objects for each of the inputs
    this->clearInputs();
    this->addInputs(m_input_lep);
    this->addInputs(m_input_jet);
    this->addInputs(m_input_met);
    this->addInputs(m_input_misc);

    // Select the appropriate network and run using ONNX
    m_model_idx = this->getSessionIndex(eventNumber);
    // this->evaluate(m_model_idx);
    // m_nu_out = this->getOutputs<float>("output");
}

}  // namespace top
