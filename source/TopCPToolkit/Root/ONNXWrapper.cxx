#include "TopCPToolkit/ONNXWrapper.h"

#include <numeric>
#include <functional>

namespace top {

  ONNXWrapper::ONNXWrapper(
    const std::string& name, 
    const std::vector<std::string>& filepaths_model_cv) :
    asg::AsgTool(name),
    m_memory_info(Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault))
  {
    // TODO check at least one model path is provided

    // initialise all the ort stuff
    m_env = std::make_shared<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "");

    // any session options are set via this object
    // use single thread (single CPU core) for the model evaluation
    m_session_options = std::make_shared<Ort::SessionOptions>();
    m_session_options->SetIntraOpNumThreads(1);
    // ONNX can perform optimizations of the model graph to improve performance (ORT_ENABLE_EXTENDED)
    m_session_options->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    // create the session and load model into memory
    for (auto& fpath_model : filepaths_model_cv) {
      auto fp = PathResolverFindCalibFile(fpath_model);

      ANA_MSG_VERBOSE("Load model from " << fp);

      m_sessions.emplace_back(new Ort::Experimental::Session(*m_env, fp, *m_session_options));
    }

    // retrieve the list of input and output tensor names
    m_input_node_names = m_sessions.front()->GetInputNames();
    m_output_node_names = m_sessions.front()->GetOutputNames();

    for (size_t inode = 0; inode < m_input_node_names.size(); inode++) {
      m_input_name_index[ m_input_node_names[inode] ] = inode;
    }
    for (size_t inode = 0; inode < m_output_node_names.size(); inode++) {
      m_output_name_index[ m_output_node_names[inode] ] = inode;
    }

    if (m_verbose){
      ANA_MSG_VERBOSE("Inputs:");
      for (long unsigned int i=0; i<m_input_node_names.size(); ++i){
        ANA_MSG_VERBOSE(m_input_node_names[i]);
      }
      ANA_MSG_VERBOSE("Outputs:");
      for (long unsigned int i=0; i<m_output_node_names.size(); ++i){
        ANA_MSG_VERBOSE(m_output_node_names[i] << " ");
      }
    }

    // first vector -- the individual input nodes
    // // second vector -- the shape of the input node, e.g. for 1xN shape, the vector has two elements with values {1, N}
    m_input_shapes = m_sessions.front()->GetInputShapes();

    if (m_verbose) {
      ANA_MSG_VERBOSE("input shapes = ");
      for (long unsigned int i=0; i < m_input_shapes.size(); ++i){
        ANA_MSG_VERBOSE(m_input_node_names[i] << ": " << m_input_shapes[i].size());

        Ort::TypeInfo type_info = m_sessions.front()->GetInputTypeInfo(i);
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        ONNXTensorElementDataType type = tensor_info.GetElementType();
        std::vector<int64_t> dims = tensor_info.GetShape();

        ANA_MSG_VERBOSE(" : "<<" type= "<<type << ", shape = [");
        for (long unsigned int j=0; j < dims.size(); ++j){
          ANA_MSG_VERBOSE(dims[j]);
        }
        ANA_MSG_VERBOSE("]");
      }
    }

    // output shape
    m_output_shapes = m_sessions.front()->GetOutputShapes();
    if (m_verbose) {
      ANA_MSG_VERBOSE("output shapes = ");
      for (long unsigned int i=0; i < m_output_shapes.size(); ++i){
        ANA_MSG_VERBOSE(m_output_node_names[i] << ": " << m_output_shapes[i].size());

        Ort::TypeInfo type_info = m_sessions.front()->GetOutputTypeInfo(i);
        auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
        ONNXTensorElementDataType type = tensor_info.GetElementType();
        std::vector<int64_t> dims = tensor_info.GetShape();

        ANA_MSG_VERBOSE(" : "<<" type= "<<type << ", shape = [");
        for (long unsigned int j=0; j < dims.size(); ++j){
          ANA_MSG_VERBOSE(dims[j]);
        }
        ANA_MSG_VERBOSE("]");
      }
    }

  } // ONNXWrapper::ONNXWrapper

} // namespace top