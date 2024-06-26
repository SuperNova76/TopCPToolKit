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
    // Create the collection of input arrays
    // We are using fixed sizes for now because I don't know how to get
    // ONNX not to complain when we use vectors and dynamic sizes
    std::vector<int64_t> el_dims = {5, 5};
    std::vector<int64_t> mu_dims = {5, 5};
    std::vector<int64_t> jet_dims = {15, 6};
    std::vector<int64_t> met_dims = {1, 3};
    std::vector<int64_t> misc_dims = {1, 3};
    float input_elec[5][5] = {};  // Zero initialisation
    float input_muon[5][5] = {};
    float input_jet[15][6] = {};
    float input_met[1][3] = {};
    float input_misc[1][3] = {};

    // Fill in the electrons
    for (long i = 0; i < el_dims[0] && i < (long)electrons.size(); i++) {
        input_elec[i][0] = static_cast<float>(electrons[i]->p4().Px());
        input_elec[i][1] = static_cast<float>(electrons[i]->p4().Py());
        input_elec[i][2] = static_cast<float>(electrons[i]->p4().Pz());
        input_elec[i][3] = static_cast<float>(std::log(electrons[i]->p4().E()));
        input_elec[i][4] = static_cast<float>(electrons[i]->charge());
    }

    // Fill in the muons
    for (long i = 0; i < mu_dims[0] && i < (long)muons.size(); i++) {
        input_muon[i][0] = static_cast<float>(muons[i]->p4().Px());
        input_muon[i][1] = static_cast<float>(muons[i]->p4().Py());
        input_muon[i][2] = static_cast<float>(muons[i]->p4().Pz());
        input_muon[i][3] = static_cast<float>(std::log(muons[i]->p4().E()));
        input_muon[i][4] = static_cast<float>(muons[i]->charge());
    }

    // Fill in the jets
    for (long i = 0; i < jet_dims[0] && i < (long)jets.size(); i++) {
        input_jet[i][0] = static_cast<float>(jets[i]->p4().Px()),
        input_jet[i][1] = static_cast<float>(jets[i]->p4().Py()),
        input_jet[i][2] = static_cast<float>(jets[i]->p4().Pz()),
        input_jet[i][3] = static_cast<float>(std::log(jets[i]->p4().E())),
        input_jet[i][4] = static_cast<float>(std::log(jets[i]->p4().M())),
        input_jet[i][5] = static_cast<float>(jets[i]->auxdataConst<int>("ftag_quantile_" + m_btagger + "_Continuous"));
    };

    // MET information
    input_met[0][0] = static_cast<float>(met_mpx);
    input_met[0][1] = static_cast<float>(met_mpy);
    input_met[0][2] = static_cast<float>(met_sumet);

    // Misc information (particle multiplicities)
    input_misc[0][0] = static_cast<float>(electrons.size());
    input_misc[0][1] = static_cast<float>(muons.size());
    input_misc[0][2] = static_cast<float>(jets.size());

    // Some printouts
    ANA_MSG_INFO("Hello from TopNuFlowsDilepton");
    ANA_MSG_INFO("Number of electrons: " << electrons.size());
    ANA_MSG_INFO("Number of muons: " << muons.size());
    ANA_MSG_INFO("Number of jets: " << jets.size());
    ANA_MSG_INFO("MET: " << met_mpx << " " << met_mpy << " " << met_sumet);
    ANA_MSG_INFO("Would run on ONNX: " << eventNumber % 2);

    // Create the Ort::Value objects for the inputs (double dereference to get datatype)
    this->clearInputs();
    this->addInputs(*input_elec, product(el_dims), el_dims.data(), el_dims.size());
    this->addInputs(*input_muon, product(mu_dims), mu_dims.data(), mu_dims.size());
    this->addInputs(*input_jet, product(jet_dims), jet_dims.data(), jet_dims.size());
    this->addInputs(*input_met, product(met_dims), met_dims.data(), met_dims.size());
    this->addInputs(*input_misc, product(misc_dims), misc_dims.data(), misc_dims.size());

    // Select the appropriate network and run using ONNX
    m_model_idx = this->getSessionIndex(eventNumber);
    // this->evaluate(m_model_idx);
    // auto outputs = this->getOutputs<float>("output");
    float outputs[] = {0, 0, 0, 0, 0, 0, 0};

    m_nu_px = outputs[0];
    m_nu_py = outputs[1];
    m_nu_pz = outputs[2];
    m_anti_nu_px = outputs[3];
    m_anti_nu_py = outputs[4];
    m_anti_nu_pz = outputs[5];
    m_loglik = outputs[6];
}

std::vector<float> TopNuFlowsDilepton::GetSample() {
    return std::vector<float>{m_nu_px, m_nu_py, m_nu_pz, m_anti_nu_px,
                              m_anti_nu_py, m_anti_nu_pz, m_loglik};
}

}  // namespace top
