#include "TopCPToolkit/SoftMuonSelectorAlg.h"

namespace top {

  SoftMuonSelectorAlg::SoftMuonSelectorAlg(const std::string &name,
                           ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_softmuonDRJetcut(0.4)
  {
  declareProperty("SoftMuonDRJet", m_softmuonDRJetcut = 0.4, "Soft Muon maximum dR wrt nearest selected jet. Can be set to 999. to keep all soft muons. Default 0.4");
  }
  
  StatusCode SoftMuonSelectorAlg::initialize() {
    ANA_MSG_INFO("Initialising the SoftMuonSelector algorithm for TopCPToolkit");

    ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_softmuonsHandle.initialize(m_systematicsList)); //Adding soft muons
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

//    ANA_CHECK(m_dphimetHandle.initialize(m_systematicsList, m_jetsHandle));
//    ANA_CHECK(m_mtwHandle.initialize(m_systematicsList, m_eventInfoHandle));

//    ANA_CHECK(m_selection.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_softmuonSelection.initialize(m_systematicsList, m_softmuonsHandle, SG::AllowEmpty));
    ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));

    // Initialize output variables
    ANA_CHECK(m_SoftMuonJetDRminHandle.initialize(m_systematicsList, m_softmuonsHandle));
    ANA_CHECK(m_SoftMuonPassDRJetcut.initialize(m_systematicsList, m_softmuonsHandle));

    ANA_CHECK(m_pass_SoftMuonPassDRJetcut.initialize(m_systematicsList, m_eventInfoHandle));



    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode SoftMuonSelectorAlg::execute() {

     for (const auto &sys : m_systematicsList.systematicsVector()) {

         const xAOD::EventInfo *evtInfo = nullptr;
//         const xAOD::ElectronContainer *electrons = nullptr;
//         const xAOD::MuonContainer *muons = nullptr;
         const xAOD::JetContainer *jets = nullptr;
//         const xAOD::MissingETContainer *met = nullptr;
         const xAOD::MuonContainer *softmuons = nullptr; //Adding soft muons

         ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

//  	 ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
//         ANA_CHECK(m_muonsHandle.retrieve(muons, sys));
         ANA_CHECK(m_jetsHandle.retrieve(jets, sys));
//         ANA_CHECK(m_metHandle.retrieve(met, sys));
	 ANA_CHECK(m_softmuonsHandle.retrieve(softmuons, sys)); //Adding soft muons

    // Fill the output variables with a default value:
    for (const xAOD::Muon *softmuon : *softmuons) {
      m_SoftMuonJetDRminHandle.set(*softmuon, -99, sys);
      m_SoftMuonPassDRJetcut.set(*softmuon, false, sys);
    }
    //m_pass_SoftMuonPassDRJetcut.setBits(*evtInfo, 0, sys);
    m_pass_SoftMuonPassDRJetcut.setBool(*evtInfo, 0, sys);

	     // first figure out if this event even passes the selection in which we are to run this KLFitter instance

//    if (!m_selection.getBool(*evtInfo, sys))
//      return StatusCode::SUCCESS;


    // perform selection of objects
    ConstDataVector<xAOD::MuonContainer> selected_softmuons(SG::VIEW_ELEMENTS);
    ConstDataVector<xAOD::JetContainer> selected_jets(SG::VIEW_ELEMENTS);

    for (const xAOD::Muon *softmu : *softmuons) {
      if (m_softmuonSelection.getBool(*softmu, sys))
        selected_softmuons.push_back(softmu);
    }

    for (const xAOD::Jet *jet : *jets) {
      if (m_jetSelection.getBool(*jet, sys))
        selected_jets.push_back(jet);
    }


//const float softmuonDRJetcut;

// ANA_CHECK(m_softmuonDRJetcut.retrieve(softmuonDRJetcut));

//         m_mtwHandle.set(*evtInfo, -1, sys);
//         for (const xAOD::Jet *jet : *jets) {
//           m_dphimetHandle.set(*jet, -99, sys);
//         }

//	 TLorentzVector lepton;
//         if ( electrons->size() > 0 ) {
//           lepton = electrons->at(0)->p4();
//         }
//         else if ( muons->size() > 0) {
//           lepton = muons->at(0)->p4();
//         }

//         float et_miss  = (*met)["Final"]->met();
//         float phi_miss = (*met)["Final"]->phi();


         TLorentzVector softmuon_vector;
	 if ( selected_softmuons.size() > 0) {
           softmuon_vector = selected_softmuons.at(0)->p4();


    // Accessing pt, eta, phi, and energy
    //Double_t pt = softmuon_vector.Pt();
    //Double_t eta = softmuon_vector.Eta();
    //Double_t phi = softmuon_vector.Phi();
    //Double_t energy = softmuon_vector.E();

    // Printing pt, eta, phi, and energy
    //std::cout << "Softmuon pt = " << pt << std::endl;
    //std::cout << "Softmuon pseudorapidity (eta) = " << eta << std::endl;
    //std::cout << "Softmuon azimuthal angle (phi) = " << phi << std::endl;
    //std::cout << "Softmuon energy = " << energy << std::endl;
    //ANA_MSG_INFO("  Softmuon pt = " << pt);

    // Calculate SoftMuonJetDRmin for each soft muon
    bool PassSoftMuonDRJetCut = false;

    for (const xAOD::Muon* softmuon : selected_softmuons){

      float DRmin = SoftMuonSelectorAlg::calculateMinDRSoftMuonJet(softmuon, selected_jets);

      m_SoftMuonJetDRminHandle.set(*softmuon, DRmin, sys);

      if(DRmin<m_softmuonDRJetcut){
        m_SoftMuonPassDRJetcut.set(*softmuon, true, sys);

        PassSoftMuonDRJetCut = true;
      }
    }

    if(PassSoftMuonDRJetCut){ m_pass_SoftMuonPassDRJetcut.setBool(*evtInfo, 1, sys);}
    else{ m_pass_SoftMuonPassDRJetcut.setBool(*evtInfo, 0, sys);}


	 }


         // Calculate mtw
//         float dphi_lep_met = TVector2::Phi_mpi_pi( lepton.Phi() - phi_miss );
//         float mtw = std::sqrt( 2 * lepton.Pt() * et_miss * (1-std::cos(dphi_lep_met)) );
//         m_mtwHandle.set(*evtInfo, mtw, sys);

	 // Calculate dphi_jet_met for each jet
//	 for (const xAOD::Jet *jet : *jets) {
//           float dphi_jet_met = TVector2::Phi_mpi_pi( jet->phi() - phi_miss );
//           m_dphimetHandle.set(*jet, dphi_jet_met, sys);
//         }



	 
     }

    return StatusCode::SUCCESS;
  }


  float SoftMuonSelectorAlg::calculateMinDRSoftMuonJet(const xAOD::Muon* softmuon, ConstDataVector<xAOD::JetContainer> selected_jets){

    float dRMin = 100.0;
    // Loop over jets, calculate dR and record smallest value

    for (const xAOD::Jet *jet : selected_jets) {

      float dR = jet->p4().DeltaR(    softmuon->p4()   );//softmuon has to be one

      if(dR < dRMin) dRMin = dR;
    }



    //ANA_MSG_INFO("  DR min " << dRMin);

//    // Decorate the muon with dR of closest jet (ie smallest dR)
//    mu.auxdecor< float >("dRJet") = dRMin;

    return dRMin;
  }



// Safe addigional information closes jet

//Save additional soft muon related variables.
  bool SoftMuonSelectorAlg::SaveAdditionalSoftMuonVairables(std::vector<const xAOD::Muon*> softmuons){

    return true;
  }





} //namespace top
