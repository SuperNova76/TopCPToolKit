#include "TopCPToolkit/ONNXWrapper.h"

#include <functional>
#include <numeric>

namespace top {

  ONNXWrapper::ONNXWrapper(
    const std::string& name,
    const std::vector<std::string>& filepaths_model_cv) :
    asg::AsgTool(name),
    m_env(std::make_shared<Ort::Env>(ORT_LOGGING_LEVEL_WARNING, "")),
    m_session_options(std::make_shared<Ort::SessionOptions>()),
    m_memory_info(Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault))
  {
    // TODO check at least one model path is provided

    // any session options are set via this object
    // use single thread (single CPU core) for the model evaluation
    m_session_options->SetIntraOpNumThreads(1);
    // ONNX can perform optimizations of the model graph to improve performance (ORT_ENABLE_EXTENDED)
    m_session_options->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    // create the session and load model into memory
    for (auto& fpath_model : filepaths_model_cv) {
      auto fp = PathResolver::find_file(fpath_model, "CALIBPATH", PathResolver::RecursiveSearch);

        ANA_MSG_VERBOSE("Load model from " << fp);

        m_sessions.emplace_back(new Ort::Session(*m_env, fp.c_str(), *m_session_options));
    }

    // retrieve the list of input and output tensor names
    Ort::AllocatorWithDefaultOptions allocator;
    Ort::Session* session = m_sessions.front().get();
    for (size_t inode = 0; inode < session->GetInputCount(); inode++) {
        m_input_name_index[session->GetInputNameAllocated(inode, allocator).get()] = inode;
        m_input_node_names.push_back(session->GetInputNameAllocated(inode, allocator).get());
    }
    for (size_t inode = 0; inode < session->GetOutputCount(); inode++) {
        m_output_name_index[session->GetOutputNameAllocated(inode, allocator).get()] = inode;
        m_output_node_names.push_back(session->GetOutputNameAllocated(inode, allocator).get());
    }

    if (m_verbose) {
        ANA_MSG_VERBOSE("Inputs:");
        for (long unsigned int i = 0; i < m_input_name_index.size(); ++i) {
            ANA_MSG_VERBOSE(session->GetInputNameAllocated(i, allocator).get() << " ");
        }
        ANA_MSG_VERBOSE("Outputs:");
        for (long unsigned int i = 0; i < m_output_name_index.size(); ++i) {
            ANA_MSG_VERBOSE(session->GetOutputNameAllocated(i, allocator).get() << " ");
        }
    }

    // first vector -- the individual input nodes
    // // second vector -- the shape of the input node, e.g. for 1xN shape, the vector has two elements with values {1, N}
    size_t input_node_count = session->GetInputCount();
    m_input_shapes = std::vector<std::vector<int64_t>>(input_node_count);
    for (size_t i = 0; i < input_node_count; i++) m_input_shapes[i] = session->GetInputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();

    if (m_verbose) {
        ANA_MSG_VERBOSE("input shapes = ");
        for (long unsigned int i = 0; i < m_input_shapes.size(); ++i) {
            ANA_MSG_VERBOSE(session->GetInputNameAllocated(i, allocator).get() << ": " << m_input_shapes[i].size());

            Ort::TypeInfo type_info = m_sessions.front()->GetInputTypeInfo(i);
            auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
            ONNXTensorElementDataType type = tensor_info.GetElementType();
            std::vector<int64_t> dims = tensor_info.GetShape();

            ANA_MSG_VERBOSE(" : " << " type= " << type << ", shape = [");
            for (long unsigned int j = 0; j < dims.size(); ++j) {
                ANA_MSG_VERBOSE(dims[j]);
            }
            ANA_MSG_VERBOSE("]");
        }
    }

    // output shape
    size_t output_node_count = session->GetOutputCount();
    m_output_shapes = std::vector<std::vector<int64_t>>(output_node_count);
    for (size_t i = 0; i < output_node_count; i++) m_output_shapes[i] = session->GetOutputTypeInfo(i).GetTensorTypeAndShapeInfo().GetShape();

    if (m_verbose) {
        ANA_MSG_VERBOSE("output shapes = ");
        for (long unsigned int i = 0; i < m_output_shapes.size(); ++i) {
            ANA_MSG_VERBOSE(session->GetOutputNameAllocated(i, allocator).get() << ": " << m_output_shapes[i].size());

            Ort::TypeInfo type_info = m_sessions.front()->GetOutputTypeInfo(i);
            auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
            ONNXTensorElementDataType type = tensor_info.GetElementType();
            std::vector<int64_t> dims = tensor_info.GetShape();

            ANA_MSG_VERBOSE(" : " << " type= " << type << ", shape = [");
            for (long unsigned int j = 0; j < dims.size(); ++j) {
                ANA_MSG_VERBOSE(dims[j]);
            }
            ANA_MSG_VERBOSE("]");
        }
    }

}  // ONNXWrapper::ONNXWrapper

}  // namespace top
