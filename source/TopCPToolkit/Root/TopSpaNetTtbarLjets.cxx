#include "TopSpaNet/TopologyTtbarLjets.h"

namespace top {

  TopSpaNetTtbarLjets::TopSpaNetTtbarLjets(const std::string& name, std::string model_even, std::string model_odd) :
    TopSpaNetTopology(name, {model_even, model_odd})
  {
    m_MAX_JETS = m_input_shapes[0][1];
    m_NUM_FEATURES = m_input_shapes[0][2];
  }

  TLorentzVector TopSpaNetTtbarLjets::getNeutrino(TLorentzVector lepton, const float met_met, const float met_phi){
    // Reference for quadratic solution: https://arxiv.org/pdf/1806.05463.pdf

    const float mW = 80400;
    const float met_px = met_met * cos(met_phi);
    const float met_py = met_met * sin(met_phi);

    float k = ((mW*mW - lepton.M()*lepton.M()) / 2.) + (lepton.Px()*met_px + lepton.Py()*met_py);
    float a = lepton.E()*lepton.E() - lepton.Pz()*lepton.Pz();
    float b = -2 * k * lepton.Pz();
    float c = lepton.E()*lepton.E()*met_met*met_met - k*k;
    float disc = b*b - 4*a*c; 
    float nu_pz = 0.0;

    if (disc < 0){
      nu_pz = -b/(2*a);
    }
    else{
      float nu_pz_1 = (-b + sqrt(disc)) / (2*a);
      float nu_pz_2 = (-b - sqrt(disc)) / (2*a);

      nu_pz = (fabs(nu_pz_1) < fabs(nu_pz_2)) ? nu_pz_1 : nu_pz_2;
    }

    float energy = sqrt(met_px*met_px+met_py*met_py+nu_pz*nu_pz);
    TLorentzVector neutrino;
    neutrino.SetPxPyPzE(met_px, met_py, nu_pz, energy);

    ANA_MSG_VERBOSE("Neutrino 4vec = " << neutrino.Pt() << " " << neutrino.Eta() << " " << neutrino.Phi() << " " << neutrino.E());

    return neutrino;
  }

  void TopSpaNetTtbarLjets::Predict(ConstDataVector<xAOD::ElectronContainer>& electrons,
				    ConstDataVector<xAOD::MuonContainer>& muons,
				    ConstDataVector<xAOD::JetContainer>& jets,
				    float met_met, float met_phi,
				    unsigned long long eventNumber) {

    xAOD::IParticleContainer leptons(SG::VIEW_ELEMENTS);
    std::vector<int> lepton_charges;
    lepton_charges.clear();
    for (const xAOD::Electron *t : electrons){
      leptons.push_back(const_cast<xAOD::Electron*>(t));
      lepton_charges.push_back(t->charge());
    }
    for (const xAOD::Muon *t : muons){
      leptons.push_back(const_cast<xAOD::Muon*>(t));
      lepton_charges.push_back(t->charge());
    }
    if (leptons.size() > 1) ANA_MSG_VERBOSE("WARNING: Multiple leptons found, using first one only");
    auto lepton = leptons[0];//TODO: should probably do this in a safer way?
    m_lepton = lepton->p4();
    m_lep_charge = lepton_charges[0];

    auto neutrino = getNeutrino(m_lepton, met_met, met_phi);
    m_neutrino = neutrino;

    // currently theres a bug with spanet whereby we need to use a batchsize > 1; so for now, we will just add a dummy second event, hence the [2] below
    float input_values[2][20][7]; // TODO: avoid hard coding these sizes?
    bool input_masks[2][20];

    bool addlep = false;
    bool addnu = false;

    for (long unsigned int i=0; i < static_cast<long unsigned int>(m_MAX_JETS); ++i){
      if (i < jets.size()){

	// TODO: Avoid hard coding these? maybe give the list of inputs in the config, or read the spanet config file, or something?

	// For now, the config used for  training looks like this:
	//[SOURCE]
	//pt = log_normalize
	//eta = normalize
	//cosphi = none
	//sinphi = none
	//e = log_normalize
	//btag = normalize
	//leptag = none

	//note logs need to be done manually, norms happen internally

	auto jet = jets[i];
	input_values[0][i][0] = std::log(jet->p4().Pt());
	input_values[0][i][1] = jet->p4().Eta();
	input_values[0][i][2] = cos(jet->p4().Phi());
	input_values[0][i][3] = sin(jet->p4().Phi());
	input_values[0][i][4] = std::log(jet->p4().E());

	if (jet->isAvailable<int>("ftag_quantile_"+m_btagger+"_Continuous")){
	  input_values[0][i][5] = jet->auxdataConst<int>("ftag_quantile_"+m_btagger+"_Continuous");
	}
	else { 
	  input_values[0][i][5] = 0;
	}
	input_values[0][i][6]=0; //leptag

	input_masks[0][i]=1;
	//input_values.push_back(jet_kin);


	//ANA_MSG_VERBOSE("PT = " << input_values[0][i][0] << ", ETA = " << input_values[0][i][1] << ", PHI = " << input_values[0][i][2] << ", E = " << input_values[0][i][3] << ", btag60 = " << input_values[0][i][4] << ", btag85 = " << input_values[0][i][5] << ", leptag = " << input_values[0][i][6]);
      }
      else if (!addlep){
	input_values[0][i][0] = std::log(m_lepton.Pt());
	input_values[0][i][1] = m_lepton.Eta();
	input_values[0][i][2] = cos(m_lepton.Phi());
	input_values[0][i][3] = sin(m_lepton.Phi());

	input_values[0][i][4] = std::log(m_lepton.E());

	input_values[0][i][5] = 0;
	input_values[0][i][6] = 1;
  
	addlep = true;
	input_masks[0][i]=1;


	//ANA_MSG_VERBOSE("PT = " << input_values[0][i][0] << ", ETA = " << input_values[0][i][1] << ", PHI = " << input_values[0][i][2] << ", E = " << input_values[0][i][3] << ", btag60 = " << input_values[0][i][4] << ", btag85 = " << input_values[0][i][5] << ", leptag = " << input_values[0][i][6]);
      } else if (!addnu){
	input_values[0][i][0] = std::log(m_neutrino.Pt());
	input_values[0][i][1] = m_neutrino.Eta();
	input_values[0][i][2] = cos(m_neutrino.Phi());
	input_values[0][i][3] = sin(m_neutrino.Phi());
	input_values[0][i][4] = std::log(m_neutrino.E());

	input_values[0][i][5] = 0;
	input_values[0][i][6] = 1;
  
	addnu = true;
	input_masks[0][i]=1;
	//ANA_MSG_VERBOSE("PT = " << input_values[0][i][0] << ", ETA = " << input_values[0][i][1] << ", PHI = " << input_values[0][i][2] << ", E = " << input_values[0][i][3] << ", btag60 = " << input_values[0][i][4] << ", btag85 = " << input_values[0][i][5] << ", leptag = " << input_values[0][i][6]);

      } else{
	// now fill the dumym values for the rest 
	for (int j=0; j < m_NUM_FEATURES; ++j) input_values[0][i][j] = 0.0;

	input_masks[0][i]=0;

      }
      // add a dummy second event because einsum is dumb with batchsize=1
      // TODO: fix this :) 
      input_masks[1][i] = 0;
      for (int j=0; j < m_NUM_FEATURES; ++j) input_values[1][i][j] = 0.0;

    }

    // create a vector of 64-bit integers with the input tensor dimension
    std::vector<int64_t> input_tensor_dims = {2, m_MAX_JETS, m_NUM_FEATURES}; // TODO: Fix this when the batching is sorted out

    // create the Ort::Value tensor storing floats.
    // The data is taken from the input_values vector.
    // The dimensions of the tensor are specified based on the input_tensor_dims.

    this->clearInputs();

    int input_size = 1;
    for (unsigned long int i=0; i < input_tensor_dims.size(); ++i){
      input_size = input_size*input_tensor_dims[i];
    }

    this->addInputs(
      **input_values, input_size, input_tensor_dims.data(), input_tensor_dims.size()
    );

    std::vector<int64_t> input_tensor_dims_mask = {2, m_MAX_JETS};
    int mask_size = 1;
    for (unsigned long int i=0; i < input_tensor_dims_mask.size(); ++i){
      mask_size = mask_size*input_tensor_dims_mask[i];
    }

    this->addInputs(
      *input_masks, mask_size, input_tensor_dims_mask.data(), input_tensor_dims_mask.size()
    );

    // make sure we are using the right network!
    unsigned imodel = getSessionIndex(eventNumber);
    this->evaluate(imodel);

    // now read the output
    auto thpred = this->getOutputs<float>("thpred"); // TODO: Might be nice to avoid hard coding this?
    //int n = sizeof(thpred)/sizeof(thpred[0]);
    float max = -999;
    const int NUM_JETS = jets.size();

    int bestrow =-1;
    int bestcol = -1;
    int bestz = -1;

    for (int row=0; row < NUM_JETS; ++row){// third particle in event file from SPANET
        
      for (int col = 0; col < NUM_JETS; ++col) {// second particle

	for (int z = 0; z < NUM_JETS; ++z) {// first particle

	  if (row == col || row == z || z == col){continue;} //ignore overlapping predictions
        
	  //ANA_MSG_VERBOSE(row << col << z);

	  if (thpred[row+col*m_MAX_JETS+z*m_MAX_JETS*m_MAX_JETS] > max){
	    max = thpred[row+col*m_MAX_JETS+z*m_MAX_JETS*m_MAX_JETS];
	    bestrow = row;
	    bestcol = col;
	    bestz = z;
	  }
       
	}}}

    ANA_MSG_VERBOSE("EventNo: " << eventNumber <<  ", Max = " << max << ", indx = " << bestrow << "," << bestcol << "," << bestz);

    float* tlpred = this->getOutputs<float>("tlpred");

    int bestlb = -1;
    float max_lb = -999;
    for (int i=0; i < NUM_JETS; ++i){ // loop only over the jets, we dont want to predict the lep or nu entry
      // For our case, we want to prioritise the hadtop prediction over the leptop; so ignore jets in the hadtop prediction
        
      if (i == bestz || i == bestrow || i == bestcol ) continue;
      //ANA_MSG_VERBOSE(i << ", " << tlpred[i]);
      if (tlpred[i] > max_lb){
	max_lb = tlpred[i];
	bestlb = i;
      }
    }

    //ANA_MSG_VERBOSE("lepton max = " << max_lb << ", indx = " << bestlb);
    
    ANA_MSG_VERBOSE("SPANET Down jet = " << bestz << ", up jet = " << bestcol << ", bhad = " << bestrow << ", blep = " << bestlb << " (Njets = " << NUM_JETS << ")");


    m_lep_b = bestlb;
    m_down = bestz;
    m_up = bestcol;
    m_had_b = bestrow;

    m_hadtop_score = max;
    m_leptop_score = max_lb;

    // now gxrab the spanet prob that the particle is reconstructable
    m_hadtop_existence = *(this->getOutputs<float>("thpresence"));
    m_leptop_existence = *(this->getOutputs<float>("tlpresence"));

  }

  std::vector<int> TopSpaNetTtbarLjets::GetOutputIndices() {

    // indices of the best assignment
    std::vector<int> indices = {m_lep_b, m_had_b, m_down, m_up};

    return indices;
  }

  std::vector<float> TopSpaNetTtbarLjets::GetOutputScores() {

    // scores of the best assignment
    std::vector<float> scores = {m_hadtop_score, m_leptop_score, m_hadtop_existence, m_leptop_existence};

    return scores;
  }

} // namespace top
