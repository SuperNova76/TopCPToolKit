#include "PartonHistory/PartonHistory.h"
#include "xAODCore/AddDVProxy.h"

namespace xAOD {
  /// Aux Container
  PartonHistoryAuxContainer::PartonHistoryAuxContainer() :
    AuxContainerBase() {
  }

  /// Interface class
  PartonHistory::PartonHistory() :
    SG::AuxElement() {
  }

  PartonHistoryAux::PartonHistoryAux() :
    AuxInfoBase() {
    }

  //Initialize variables for ttbar events
  void PartonHistory::IniVarTtbar() {
    //ttbar variables
    this->auxdecor< float >("MC_ttbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_phi") = -1000;

    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    //tbar variables
    this->auxdecor< float >("MC_tbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_afterFSR_phi") = -1000;


    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_W_from_tbar_m") = -1;
    this->auxdecor< float >("MC_W_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_W_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_W_from_tbar_phi") = -1000;

    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_bbar_from_tbar_m") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_bbar_from_tbar_phi") = -1000;

    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay1_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = 0;
  }

  //Initialize variables for ttbar events
  void PartonHistory::IniVarTtbarLight() {
    //ttbar variables
    this->auxdecor< float >("MC_ttbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_phi") = -1000;

    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    //tbar variables
    this->auxdecor< float >("MC_tbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_W_from_tbar_m") = -1;
    this->auxdecor< float >("MC_W_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_W_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_W_from_tbar_phi") = -1000;

    this->auxdecor< float >("MC_q_from_t_m") = -1;
    this->auxdecor< float >("MC_q_from_t_pt") = -1;
    this->auxdecor< float >("MC_q_from_t_eta") = -1000;
    this->auxdecor< float >("MC_q_from_t_phi") = -1000;
    this->auxdecor< int >("MC_q_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_q_from_tbar_m") = -1;
    this->auxdecor< float >("MC_q_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_q_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_q_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_q_from_tbar_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay1_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = 0;
  }

  //Initialize variables for tbbar events
  void PartonHistory::IniVarTbbar() {
    //ttbar variables
    this->auxdecor< float >("MC_tbbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbbar_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    //tbbar variables
    this->auxdecor< float >("MC_b_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_b_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_b_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_b_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_b_afterFSR_m") = -1;
    this->auxdecor< float >("MC_b_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_b_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_b_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;
  }

  //Initialize variables for Wlv events
  void PartonHistory::IniVarWlv() {
    // W
    this->auxdecor< float >("MC_W_m") = -1;
    this->auxdecor< float >("MC_W_pt") = -1;
    this->auxdecor< float >("MC_W_eta") = -1000;
    this->auxdecor< float >("MC_W_phi") = -1000;

    this->auxdecor< float >("MC_l_m") = -1;
    this->auxdecor< float >("MC_l_pt") = -1;
    this->auxdecor< float >("MC_l_eta") = -1000;
    this->auxdecor< float >("MC_l_phi") = -1000;
    this->auxdecor< int >("MC_l_pdgId") = 0;

    this->auxdecor< float >("MC_v_m") = -1;
    this->auxdecor< float >("MC_v_pt") = -1;
    this->auxdecor< float >("MC_v_eta") = -1000;
    this->auxdecor< float >("MC_v_phi") = -1000;
    this->auxdecor< int >("MC_v_pdgId") = 0;
  }

  // Initialize variable for Wt ST events
  void PartonHistory::IniVarWtb() {
    // top or antitop
    this->auxdecor< float >("MC_top_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_top_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_top_beforeFSR_phi") = -1000;
    this->auxdecor< float >("MC_top_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_top_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_top_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_top_afterFSR_phi") = -1000;
    this->auxdecor< float >("MC_top_afterFSR_m") = -1;

    // b from top
    this->auxdecor< float >("MC_b_from_top_pt") = -1;
    this->auxdecor< float >("MC_b_from_top_eta") = -1000;
    this->auxdecor< float >("MC_b_from_top_phi") = -1000;
    this->auxdecor< float >("MC_b_from_top_m") = -1;

    // W from top
    this->auxdecor< float >("MC_W_from_top_pt") = -1;
    this->auxdecor< float >("MC_W_from_top_eta") = -1000;
    this->auxdecor< float >("MC_W_from_top_phi") = -1000;
    this->auxdecor< float >("MC_W_from_top_m") = -1;

    // W from top decay product 1
    this->auxdecor< float >("MC_Wdecay1_from_top_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_top_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_top_phi") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_top_m") = -1;
    this->auxdecor< int >("MC_Wdecay1_from_top_pdgId") = 0;

    // W from top decay product 2
    this->auxdecor< float >("MC_Wdecay2_from_top_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_top_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_top_phi") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_top_m") = -1;
    this->auxdecor< int >("MC_Wdecay2_from_top_pdgId") = 0;

    // W NOT from top
    this->auxdecor< float >("MC_W_not_from_top_pt") = -1;
    this->auxdecor< float >("MC_W_not_from_top_eta") = -1000;
    this->auxdecor< float >("MC_W_not_from_top_phi") = -1000;
    this->auxdecor< float >("MC_W_not_from_top_m") = -1;

    // W NOT from top decay product 1
    this->auxdecor< float >("MC_Wdecay1_not_from_top_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_not_from_top_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_not_from_top_phi") = -1000;
    this->auxdecor< float >("MC_Wdecay1_not_from_top_m") = -1;
    this->auxdecor< int >("MC_Wdecay1_not_from_top_pdgId") = 0;

    // W NOT from top decay product 2
    this->auxdecor< float >("MC_Wdecay2_not_from_top_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_not_from_top_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_not_from_top_phi") = -1000;
    this->auxdecor< float >("MC_Wdecay2_not_from_top_m") = -1;
    this->auxdecor< int >("MC_Wdecay2_not_from_top_pdgId") = 0;

    // b not from top, for Wtb events
    this->auxdecor< float >("MC_b_not_from_top_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_b_not_from_top_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_b_not_from_top_beforeFSR_phi") = -1000;
    this->auxdecor< float >("MC_b_not_from_top_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_b_not_from_top_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_b_not_from_top_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_b_not_from_top_afterFSR_phi") = -1000;
    this->auxdecor< float >("MC_b_not_from_top_afterFSR_m") = -1;
    this->auxdecor< int >("MC_b_not_from_top_pdgId") = 0;
  }

  // Initialize variables for an additional final-state Z.
  void PartonHistory::IniVarZ() {
    this->auxdecor< float >("MC_Z_m") = -1;
    this->auxdecor< float >("MC_Z_pt") = -1;
    this->auxdecor< float >("MC_Z_eta") = -1000;
    this->auxdecor< float >("MC_Z_phi") = -1000;

    this->auxdecor< float >("MC_Zdecay1_m") = -1;
    this->auxdecor< float >("MC_Zdecay1_pt") = -1;
    this->auxdecor< float >("MC_Zdecay1_eta") = -1000;
    this->auxdecor< float >("MC_Zdecay1_phi") = -1000;
    this->auxdecor< int >("MC_Zdecay1_pdgId") = 0;

    this->auxdecor< float >("MC_Zdecay2_m") = -1;
    this->auxdecor< float >("MC_Zdecay2_pt") = -1;
    this->auxdecor< float >("MC_Zdecay2_eta") = -1000;
    this->auxdecor< float >("MC_Zdecay2_phi") = -1000;
    this->auxdecor< int >("MC_Zdecay2_pdgId") = 0;

    this->auxdecor< int >("MC_Z_IsOnShell") = -1;
  }

  //Initialize variables for ttbargamma events
  void PartonHistory::IniVarTtGamma() {
    //ttbar variables
    this->auxdecor< float >("MC_ttbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_phi") = -1000;

    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    //tbar variables
    this->auxdecor< float >("MC_tbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_afterFSR_phi") = -1000;

    //W variables
    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_W_from_tbar_m") = -1;
    this->auxdecor< float >("MC_W_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_W_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_W_from_tbar_phi") = -1000;

    //b variables
    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_bbar_from_tbar_m") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_bbar_from_tbar_phi") = -1000;

    //Wdecay1 variables
    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay1_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = 0;

    //Wdecay2 variables
    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = 0;

    //photon variables
    this->auxdecor< float >("MC_ph_m") = -1;
    this->auxdecor< float >("MC_ph_pt") = -1;
    this->auxdecor< float >("MC_ph_eta") = -1000;
    this->auxdecor< float >("MC_ph_phi") = -1000;

    this->auxdecor< int >("MC_branchtype_t") = -1;
    this->auxdecor< int >("MC_branchtype_tbar") = -1;
    this->auxdecor< int >("MC_initial_parton") = -1;
    this->auxdecor< int >("MC_ph_from_t_tbar") = -1;
    this->auxdecor< int >("MC_Event_Category") = -1;
  }

  // Initialize variables for thqtautau events
  void PartonHistory::IniVarThq() {
    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    // Higgs variables
    this->auxdecor< float >("MC_H_m") = -1;
    this->auxdecor< float >("MC_H_pt") = -1;
    this->auxdecor< float >("MC_H_eta") = -1000;
    this->auxdecor< float >("MC_H_phi") = -1000;

    this->auxdecor< float >("MC_Hdecay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay1_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay1_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay2_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay2_pdgId") = 0;

  }

  // Initialize variables for tZq events
  void PartonHistory::IniVarTzq() {
    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_W_from_tbar_m") = -1;
    this->auxdecor< float >("MC_W_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_W_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_W_from_tbar_phi") = -1000;

    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_bbar_from_tbar_m") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_bbar_from_tbar_phi") = -1000;

    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay1_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = 0;

    //Z variables
    this->auxdecor< float >("MC_Z_m") = -1;
    this->auxdecor< float >("MC_Z_pt") = -1;
    this->auxdecor< float >("MC_Z_eta") = -1000;
    this->auxdecor< float >("MC_Z_phi") = -1000;

    this->auxdecor< float >("MC_Zdecay1_m") = -1;
    this->auxdecor< float >("MC_Zdecay1_pt") = -1;
    this->auxdecor< float >("MC_Zdecay1_eta") = -1000;
    this->auxdecor< float >("MC_Zdecay1_phi") = -1000;
    this->auxdecor< int >("MC_Zdecay1_pdgId") = 0;
    this->auxdecor< int >("MC_Zdecay1_status") = -9999;

    this->auxdecor< float >("MC_Zdecay2_m") = -1;
    this->auxdecor< float >("MC_Zdecay2_pt") = -1;
    this->auxdecor< float >("MC_Zdecay2_eta") = -1000;
    this->auxdecor< float >("MC_Zdecay2_phi") = -1000;
    this->auxdecor< int >("MC_Zdecay2_pdgId") = 0;
    this->auxdecor< int >("MC_Zdecay2_status") = -9999;

    // spectator quarks
    this->auxdecor< float >("MC_b_m") = -1;
    this->auxdecor< float >("MC_b_pt") = -1;
    this->auxdecor< float >("MC_b_eta") = -1000;
    this->auxdecor< float >("MC_b_phi") = -1000;
    this->auxdecor< int >("MC_b_pdgId") = 0;

    this->auxdecor< float >("MC_bbar_m") = -1;
    this->auxdecor< float >("MC_bbar_pt") = -1;
    this->auxdecor< float >("MC_bbar_eta") = -1000;
    this->auxdecor< float >("MC_bbar_phi") = -1000;
    this->auxdecor< int >("MC_bbar_pdgId") = 0;

    this->auxdecor< float >("MC_q_m") = -1;
    this->auxdecor< float >("MC_q_pt") = -1;
    this->auxdecor< float >("MC_q_eta") = -1000;
    this->auxdecor< float >("MC_q_phi") = -1000;
    this->auxdecor< int >("MC_q_pdgId") = 0;

    this->auxdecor< float >("MC_qbar_m") = -1;
    this->auxdecor< float >("MC_qbar_pt") = -1;
    this->auxdecor< float >("MC_qbar_eta") = -1000;
    this->auxdecor< float >("MC_qbar_phi") = -1000;
    this->auxdecor< int >("MC_qbar_pdgId") = 0;
  }

  // Initialize variables for an additional final-state Higgs
  void PartonHistory::IniVarTth() {

    // Higgs variables
    this->auxdecor< float >("MC_H_m") = -1;
    this->auxdecor< float >("MC_H_pt") = -1;
    this->auxdecor< float >("MC_H_eta") = -1000;
    this->auxdecor< float >("MC_H_phi") = -1000;

    this->auxdecor< float >("MC_Hdecay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay1_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay1_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay1_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay1_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay2_pdgId") = 0;

    this->auxdecor< float >("MC_Hdecay2_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_phi") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay2_eta") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay2_pdgId") = 0;

    //ttbar variables
    this->auxdecor< float >("MC_ttbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_phi") = -1000;

    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_m") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_pt") = -1;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_eta") = -1000;
    this->auxdecor< float >("MC_ttbar_afterFSR_beforeDecay_phi") = -1000;

    //t variables
    this->auxdecor< float >("MC_t_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_t_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_t_afterFSR_m") = -1;
    this->auxdecor< float >("MC_t_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_t_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_t_afterFSR_phi") = -1000;

    //tbar variables
    this->auxdecor< float >("MC_tbar_beforeFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_beforeFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_beforeFSR_phi") = -1000;

    this->auxdecor< float >("MC_tbar_afterFSR_m") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_pt") = -1;
    this->auxdecor< float >("MC_tbar_afterFSR_eta") = -1000;
    this->auxdecor< float >("MC_tbar_afterFSR_phi") = -1000;

    // W's from t/tbar
    this->auxdecor< float >("MC_W_from_t_m") = -1;
    this->auxdecor< float >("MC_W_from_t_pt") = -1;
    this->auxdecor< float >("MC_W_from_t_eta") = -1000;
    this->auxdecor< float >("MC_W_from_t_phi") = -1000;

    this->auxdecor< float >("MC_W_from_tbar_m") = -1;
    this->auxdecor< float >("MC_W_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_W_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_W_from_tbar_phi") = -1000;

    // decays 1 and 2 from W's from t, all combos
    this->auxdecor< float >("MC_Wdecay1_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_t_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_t_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_t_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_t_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_t_pdgId") = 0;

    // decays 1 and 2 from W's from tbar, all combos
    this->auxdecor< float >("MC_Wdecay1_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay1_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay1_from_tbar_pdgId") = 0;

    this->auxdecor< float >("MC_Wdecay2_from_tbar_m") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_Wdecay2_from_tbar_phi") = -1000;
    this->auxdecor< int >("MC_Wdecay2_from_tbar_pdgId") = 0;

    // b's from t/tbar
    this->auxdecor< float >("MC_b_from_t_m") = -1;
    this->auxdecor< float >("MC_b_from_t_pt") = -1;
    this->auxdecor< float >("MC_b_from_t_eta") = -1000;
    this->auxdecor< float >("MC_b_from_t_phi") = -1000;

    this->auxdecor< float >("MC_bbar_from_tbar_m") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_pt") = -1;
    this->auxdecor< float >("MC_bbar_from_tbar_eta") = -1000;
    this->auxdecor< float >("MC_bbar_from_tbar_phi") = -1000;
  }

  void PartonHistory::IniVarHWW() {
    // Higgs
    this->auxdecor< float >("MC_H_m") = -1;
    this->auxdecor< float >("MC_H_pt") = -1;
    this->auxdecor< float >("MC_H_eta") = -1000;
    this->auxdecor< float >("MC_H_phi") = -1000;

    // W1
    this->auxdecor< float >("MC_Hdecay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_pdgId") = 0;

    // W2
    this->auxdecor< float >("MC_Hdecay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_pdgId") = 0;

    // W1 decay 1
    this->auxdecor< float >("MC_Hdecay1_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay1_pdgId") = 0;

    // W2 decay 1
    this->auxdecor< float >("MC_Hdecay2_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay1_pdgId") = 0;

    // W1 decay 2
    this->auxdecor< float >("MC_Hdecay1_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay2_pdgId") = 0;

    // W2 decay 2
    this->auxdecor< float >("MC_Hdecay2_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay2_pdgId") = 0;
  }

  void PartonHistory::IniVarHZZ() {
    // Higgs
    this->auxdecor< float >("MC_H_m") = -1;
    this->auxdecor< float >("MC_H_pt") = -1;
    this->auxdecor< float >("MC_H_eta") = -1000;
    this->auxdecor< float >("MC_H_phi") = -1000;
    
    // Z1
    this->auxdecor< float >("MC_Hdecay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_pdgId") = 0;

    // Z2
    this->auxdecor< float >("MC_Hdecay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_pdgId") = 0;

    // Z1 decay 1
    this->auxdecor< float >("MC_Hdecay1_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay1_pdgId") = 0;

    // Z2 decay 1
    this->auxdecor< float >("MC_Hdecay2_decay1_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay1_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay1_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay1_pdgId") = 0;

    // Z1 decay 2
    this->auxdecor< float >("MC_Hdecay1_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay1_decay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay1_decay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay1_decay2_pdgId") = 0;

    // Z2 decay 2
    this->auxdecor< float >("MC_Hdecay2_decay2_m") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_pt") = -1;
    this->auxdecor< float >("MC_Hdecay2_decay2_eta") = -1000;
    this->auxdecor< float >("MC_Hdecay2_decay2_phi") = -1000;
    this->auxdecor< int >("MC_Hdecay2_decay2_pdgId") = 0;
  }
}
//ADD_NS_DV_PROXY(xAOD, PartonHistoryContainer);
