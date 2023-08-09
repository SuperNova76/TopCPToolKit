#ifndef TOPSPANET_TOPOLOGY_BASE_H
#define TOPSPANET_TOPOLOGY_BASE_H

// ONNX includes
#include <core/session/experimental_onnxruntime_cxx_api.h>
#include <core/session/onnxruntime_cxx_api.h>

// useful
#include <TLorentzVector.h>
#include <vector>
#include <iostream>
#include <math.h>
#include <PathResolver/PathResolver.h>

// Framework includes
#include "AsgTools/AsgTool.h"
//#include <AsgTools/SgTEvent.h> // FIXME! currently required to prevent crash on "ConstDataVector<DataVector<xAOD::Electron_v1> >' has incomplete type"...
#include <xAODEgamma/ElectronContainer.h>
#include <xAODMuon/MuonContainer.h>
#include <xAODJet/JetContainer.h>


namespace top {
  class TopSpaNetTopology: public asg::AsgTool {
  public:
    TopSpaNetTopology(const std::string& name, std::string model_even, std::string model_odd);

    ~TopSpaNetTopology();

    virtual StatusCode execute() { return StatusCode::SUCCESS; }; // we would need to refactor things a bit in order to let the tool know about the selected objects, then we could use execute() instead of Predict()

    virtual void Predict(ConstDataVector<xAOD::ElectronContainer>& electrons,
			 ConstDataVector<xAOD::MuonContainer>& muons,
			 ConstDataVector<xAOD::JetContainer>& jets,
			 float met_met, float met_phi,
			 unsigned long long eventNumber) = 0;

    virtual std::vector<int> GetOutputIndices() = 0;
    virtual std::vector<float> GetOutputScores() = 0;

    void makeVerbose(bool verbosity) { m_verbose = verbosity; };
    void setBtagger(std::string algorithm) { m_btagger = algorithm; };

  protected:
    std::string m_spanet_path_trainedoneven;
    std::string m_spanet_path_trainedonodd;
    std::shared_ptr<Ort::Env> m_env;
    std::shared_ptr<Ort::SessionOptions> m_session_options;
    std::shared_ptr<Ort::Experimental::Session> m_session_trainedoneven;
    std::shared_ptr<Ort::Experimental::Session> m_session_trainedonodd;
    std::vector<std::string> m_input_node_names;
    std::vector<std::string> m_output_node_names;
    std::vector<std::vector<int64_t>> m_input_shapes;
    std::vector<std::vector<int64_t>> m_output_shapes;

    bool m_verbose = false;
    std::string m_btagger;
    int m_MAX_JETS;
    int m_NUM_FEATURES;

  };
} // namespace top

#endif
    
