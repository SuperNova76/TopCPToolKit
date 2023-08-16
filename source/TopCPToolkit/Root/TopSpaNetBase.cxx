#include "TopSpaNet/TopologyBase.h"

namespace top {

  TopSpaNetTopology::TopSpaNetTopology(const std::string& name, std::string model_even, std::string model_odd) :
    asg::AsgTool(name),
    m_spanet_path_trainedoneven(std::move(model_even)),
    m_spanet_path_trainedonodd(std::move(model_odd))
  {

    // initialise all the ort stuff

    m_spanet_path_trainedoneven = PathResolverFindCalibFile(m_spanet_path_trainedoneven) ;
    m_spanet_path_trainedonodd  = PathResolverFindCalibFile(m_spanet_path_trainedonodd) ;

    m_env = std::shared_ptr<Ort::Env>(new Ort::Env(ORT_LOGGING_LEVEL_WARNING, ""));

    ANA_MSG_VERBOSE("Reading SPANET prediction from " << m_spanet_path_trainedoneven << "(for odd events) and " << m_spanet_path_trainedonodd << " (for even events)");

    // any session options are set via this object
    // use single thread (single CPU core) for the model evaluation
    m_session_options = std::shared_ptr<Ort::SessionOptions>(new Ort::SessionOptions());
    m_session_options->SetIntraOpNumThreads(1);
    // ONNX can perform optimizations of the model graph to improve performance (ORT_ENABLE_EXTENDED)
    m_session_options->SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

    // create the session and load model into memory
    m_session_trainedoneven = std::shared_ptr<Ort::Experimental::Session>(new Ort::Experimental::Session(*m_env, m_spanet_path_trainedoneven, *m_session_options));
    m_session_trainedonodd  = std::shared_ptr<Ort::Experimental::Session>(new Ort::Experimental::Session(*m_env, m_spanet_path_trainedonodd, *m_session_options));
    // retrieve the list of input and output tensor names
    m_input_node_names = m_session_trainedoneven->GetInputNames();
    m_output_node_names = m_session_trainedoneven->GetOutputNames();

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
    // TODO: Remove assumption that the even and odd networks are the same?
    m_input_shapes = m_session_trainedoneven->GetInputShapes();

    m_MAX_JETS = m_input_shapes[0][1]; // TODO: Fix this when we fix the batching thing
    m_NUM_FEATURES = m_input_shapes[0][2];

    if (m_verbose) {
      ANA_MSG_VERBOSE("input shapes = ");
      for (long unsigned int i=0; i < m_input_shapes.size(); ++i){
	ANA_MSG_VERBOSE(m_input_node_names[i] << ": " << m_input_shapes[i].size());

	Ort::TypeInfo type_info = m_session_trainedoneven->GetInputTypeInfo(i);
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
    // // output shapes are stored exactly the same as input shapes.
    // // In our example, we will have a single element = vector of length 2 with values {1, 1}, corresponding to a 1x1 output tensor shape.
    m_output_shapes = m_session_trainedoneven->GetOutputShapes();
    if (m_verbose) {
      ANA_MSG_VERBOSE("output shapes = ");
      for (long unsigned int i=0; i < m_output_shapes.size(); ++i){
	ANA_MSG_VERBOSE(m_output_node_names[i] << ": " << m_output_shapes[i].size());

	Ort::TypeInfo type_info = m_session_trainedoneven->GetOutputTypeInfo(i);
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
  }

  TopSpaNetTopology::~TopSpaNetTopology() {}

} // namespace top
