from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType

truth_branches = {
    "Ttbar" : [
        'MC_ttbar_beforeFSR_pt',
        'MC_ttbar_beforeFSR_eta',
        'MC_ttbar_beforeFSR_phi',
        'MC_ttbar_beforeFSR_m',
        'MC_ttbar_fromDecay_beforeFSR_pt',
        'MC_ttbar_fromDecay_beforeFSR_eta',
        'MC_ttbar_fromDecay_beforeFSR_phi',
        'MC_ttbar_fromDecay_beforeFSR_m',
        'MC_ttbar_fromDecay_afterFSR_pt',
        'MC_ttbar_fromDecay_afterFSR_eta',
        'MC_ttbar_fromDecay_afterFSR_phi',
        'MC_ttbar_fromDecay_afterFSR_m',
        'MC_ttbar_afterFSR_pt',
        'MC_ttbar_afterFSR_eta',
        'MC_ttbar_afterFSR_phi',
        'MC_ttbar_afterFSR_m',
        'MC_t_beforeFSR_pt',
        'MC_t_beforeFSR_eta',
        'MC_t_beforeFSR_phi',
        'MC_t_beforeFSR_m',
        'MC_t_beforeFSR_pdgId',
        'MC_t_afterFSR_pt',
        'MC_t_afterFSR_eta',
        'MC_t_afterFSR_phi',
        'MC_t_afterFSR_m',
        'MC_t_afterFSR_pdgId',
        'MC_W_from_t_pt',
        'MC_W_from_t_eta',
        'MC_W_from_t_phi',
        'MC_W_from_t_m',
        'MC_W_from_t_pdgId',
        'MC_b_from_t_pt',
        'MC_b_from_t_eta',
        'MC_b_from_t_phi',
        'MC_b_from_t_m',
        'MC_b_from_t_pdgId',
        'MC_Wdecay1_from_t_pt',
        'MC_Wdecay1_from_t_eta',
        'MC_Wdecay1_from_t_phi',
        'MC_Wdecay1_from_t_m',
        'MC_Wdecay1_from_t_pdgId',
        'MC_Wdecay2_from_t_pt',
        'MC_Wdecay2_from_t_eta',
        'MC_Wdecay2_from_t_phi',
        'MC_Wdecay2_from_t_m',
        'MC_Wdecay2_from_t_pdgId',
        'MC_tbar_beforeFSR_pt',
        'MC_tbar_beforeFSR_eta',
        'MC_tbar_beforeFSR_phi',
        'MC_tbar_beforeFSR_m',
        'MC_tbar_beforeFSR_pdgId',
        'MC_tbar_afterFSR_pt',
        'MC_tbar_afterFSR_eta',
        'MC_tbar_afterFSR_phi',
        'MC_tbar_afterFSR_m',
        'MC_tbar_afterFSR_pdgId',
        'MC_W_from_tbar_pt',
        'MC_W_from_tbar_eta',
        'MC_W_from_tbar_phi',
        'MC_W_from_tbar_m',
        'MC_W_from_tbar_pdgId',
        'MC_bbar_from_tbar_pt',
        'MC_bbar_from_tbar_eta',
        'MC_bbar_from_tbar_phi',
        'MC_bbar_from_tbar_m',
        'MC_bbar_from_tbar_pdgId',
        'MC_Wdecay1_from_tbar_pt',
        'MC_Wdecay1_from_tbar_eta',
        'MC_Wdecay1_from_tbar_phi',
        'MC_Wdecay1_from_tbar_m',
        'MC_Wdecay1_from_tbar_pdgId',
        'MC_Wdecay2_from_tbar_pt',
        'MC_Wdecay2_from_tbar_eta',
        'MC_Wdecay2_from_tbar_phi',
        'MC_Wdecay2_from_tbar_m',
        'MC_Wdecay2_from_tbar_pdgId'
    ],
    "TtbarLight": [
        'MC_ttbar_beforeFSR_pt',
        'MC_ttbar_beforeFSR_eta',
        'MC_ttbar_beforeFSR_phi',
        'MC_ttbar_beforeFSR_m',
        'MC_ttbar_afterFSR_pt',
        'MC_ttbar_afterFSR_eta',
        'MC_ttbar_afterFSR_phi',
        'MC_ttbar_afterFSR_m',
        'MC_t_beforeFSR_pt',
        'MC_t_beforeFSR_eta',
        'MC_t_beforeFSR_phi',
        'MC_t_beforeFSR_m',
        'MC_t_afterFSR_pt',
        'MC_t_afterFSR_eta',
        'MC_t_afterFSR_phi',
        'MC_t_afterFSR_m',
        'MC_W_from_t_pt',
        'MC_W_from_t_eta',
        'MC_W_from_t_phi',
        'MC_W_from_t_m',
        'MC_q_from_t_pt',
        'MC_q_from_t_eta',
        'MC_q_from_t_phi',
        'MC_q_from_t_m',
        'MC_q_from_t_pdgId',
        'MC_Wdecay1_from_t_pt',
        'MC_Wdecay1_from_t_eta',
        'MC_Wdecay1_from_t_phi',
        'MC_Wdecay1_from_t_m',
        'MC_Wdecay1_from_t_pdgId',
        'MC_Wdecay2_from_t_pt',
        'MC_Wdecay2_from_t_eta',
        'MC_Wdecay2_from_t_phi',
        'MC_Wdecay2_from_t_m',
        'MC_Wdecay2_from_t_pdgId',
        'MC_tbar_beforeFSR_pt',
        'MC_tbar_beforeFSR_eta',
        'MC_tbar_beforeFSR_phi',
        'MC_tbar_beforeFSR_m',
        'MC_tbar_afterFSR_pt',
        'MC_tbar_afterFSR_eta',
        'MC_tbar_afterFSR_phi',
        'MC_tbar_afterFSR_m',
        'MC_W_from_tbar_pt',
        'MC_W_from_tbar_eta',
        'MC_W_from_tbar_phi',
        'MC_W_from_tbar_m',
        'MC_q_from_tbar_pt',
        'MC_q_from_tbar_eta',
        'MC_q_from_tbar_phi',
        'MC_q_from_tbar_m',
        'MC_q_from_tbar_pdgId',
        'MC_Wdecay1_from_tbar_pt',
        'MC_Wdecay1_from_tbar_eta',
        'MC_Wdecay1_from_tbar_phi',
        'MC_Wdecay1_from_tbar_m',
        'MC_Wdecay1_from_tbar_pdgId',
        'MC_Wdecay2_from_tbar_pt',
        'MC_Wdecay2_from_tbar_eta',
        'MC_Wdecay2_from_tbar_phi',
        'MC_Wdecay2_from_tbar_m',
        'MC_Wdecay2_from_tbar_pdgId'
    ],
    "Ttz" : [
        'MC_ttbar_beforeFSR_pt',
        'MC_ttbar_beforeFSR_eta',
        'MC_ttbar_beforeFSR_phi',
        'MC_ttbar_beforeFSR_m',
        'MC_ttbar_fromDecay_beforeFSR_pt',
        'MC_ttbar_fromDecay_beforeFSR_eta',
        'MC_ttbar_fromDecay_beforeFSR_phi',
        'MC_ttbar_fromDecay_beforeFSR_m',
        'MC_ttbar_fromDecay_afterFSR_pt',
        'MC_ttbar_fromDecay_afterFSR_eta',
        'MC_ttbar_fromDecay_afterFSR_phi',
        'MC_ttbar_fromDecay_afterFSR_m',
        'MC_ttbar_afterFSR_pt',
        'MC_ttbar_afterFSR_eta',
        'MC_ttbar_afterFSR_phi',
        'MC_ttbar_afterFSR_m',
        'MC_t_beforeFSR_pt',
        'MC_t_beforeFSR_eta',
        'MC_t_beforeFSR_phi',
        'MC_t_beforeFSR_m',
        'MC_t_beforeFSR_pdgId',
        'MC_t_afterFSR_pt',
        'MC_t_afterFSR_eta',
        'MC_t_afterFSR_phi',
        'MC_t_afterFSR_m',
        'MC_t_afterFSR_pdgId',
        'MC_W_from_t_pt',
        'MC_W_from_t_eta',
        'MC_W_from_t_phi',
        'MC_W_from_t_m',
        'MC_W_from_t_pdgId',
        'MC_b_from_t_pt',
        'MC_b_from_t_eta',
        'MC_b_from_t_phi',
        'MC_b_from_t_m',
        'MC_b_from_t_pdgId',
        'MC_Wdecay1_from_t_pt',
        'MC_Wdecay1_from_t_eta',
        'MC_Wdecay1_from_t_phi',
        'MC_Wdecay1_from_t_m',
        'MC_Wdecay1_from_t_pdgId',
        'MC_Wdecay2_from_t_pt',
        'MC_Wdecay2_from_t_eta',
        'MC_Wdecay2_from_t_phi',
        'MC_Wdecay2_from_t_m',
        'MC_Wdecay2_from_t_pdgId',
        'MC_tbar_beforeFSR_pt',
        'MC_tbar_beforeFSR_eta',
        'MC_tbar_beforeFSR_phi',
        'MC_tbar_beforeFSR_m',
        'MC_tbar_beforeFSR_pdgId',
        'MC_tbar_afterFSR_pt',
        'MC_tbar_afterFSR_eta',
        'MC_tbar_afterFSR_phi',
        'MC_tbar_afterFSR_m',
        'MC_tbar_afterFSR_pdgId',
        'MC_W_from_tbar_pt',
        'MC_W_from_tbar_eta',
        'MC_W_from_tbar_phi',
        'MC_W_from_tbar_m',
        'MC_W_from_tbar_pdgId',
        'MC_bbar_from_tbar_pt',
        'MC_bbar_from_tbar_eta',
        'MC_bbar_from_tbar_phi',
        'MC_bbar_from_tbar_m',
        'MC_bbar_from_tbar_pdgId',
        'MC_Wdecay1_from_tbar_pt',
        'MC_Wdecay1_from_tbar_eta',
        'MC_Wdecay1_from_tbar_phi',
        'MC_Wdecay1_from_tbar_m',
        'MC_Wdecay1_from_tbar_pdgId',
        'MC_Wdecay2_from_tbar_pt',
        'MC_Wdecay2_from_tbar_eta',
        'MC_Wdecay2_from_tbar_phi',
        'MC_Wdecay2_from_tbar_m',
        'MC_Wdecay2_from_tbar_pdgId',
        'MC_Z_pt',
        'MC_Z_eta',
        'MC_Z_phi',
        'MC_Z_m',
        'MC_Zdecay1_pt',
        'MC_Zdecay1_eta',
        'MC_Zdecay1_phi',
        'MC_Zdecay1_m',
        'MC_Zdecay1_pdgId',
        'MC_Zdecay2_pt',
        'MC_Zdecay2_eta',
        'MC_Zdecay2_phi',
        'MC_Zdecay2_m',
        'MC_Zdecay2_pdgId',
        'MC_Z_IsOnShell'
    ],
    "Tth" : [
        'MC_ttbar_beforeFSR_pt',
        'MC_ttbar_beforeFSR_eta',
        'MC_ttbar_beforeFSR_phi',
        'MC_ttbar_beforeFSR_m',
        'MC_ttbar_fromDecay_beforeFSR_pt',
        'MC_ttbar_fromDecay_beforeFSR_eta',
        'MC_ttbar_fromDecay_beforeFSR_phi',
        'MC_ttbar_fromDecay_beforeFSR_m',
        'MC_ttbar_fromDecay_afterFSR_pt',
        'MC_ttbar_fromDecay_afterFSR_eta',
        'MC_ttbar_fromDecay_afterFSR_phi',
        'MC_ttbar_fromDecay_afterFSR_m',
        'MC_ttbar_afterFSR_pt',
        'MC_ttbar_afterFSR_eta',
        'MC_ttbar_afterFSR_phi',
        'MC_ttbar_afterFSR_m',
        'MC_t_beforeFSR_pt',
        'MC_t_beforeFSR_eta',
        'MC_t_beforeFSR_phi',
        'MC_t_beforeFSR_m',
        'MC_t_beforeFSR_pdgId',
        'MC_t_afterFSR_pt',
        'MC_t_afterFSR_eta',
        'MC_t_afterFSR_phi',
        'MC_t_afterFSR_m',
        'MC_t_afterFSR_pdgId',
        'MC_W_from_t_pt',
        'MC_W_from_t_eta',
        'MC_W_from_t_phi',
        'MC_W_from_t_m',
        'MC_W_from_t_pdgId',
        'MC_b_from_t_pt',
        'MC_b_from_t_eta',
        'MC_b_from_t_phi',
        'MC_b_from_t_m',
        'MC_b_from_t_pdgId',
        'MC_Wdecay1_from_t_pt',
        'MC_Wdecay1_from_t_eta',
        'MC_Wdecay1_from_t_phi',
        'MC_Wdecay1_from_t_m',
        'MC_Wdecay1_from_t_pdgId',
        'MC_Wdecay2_from_t_pt',
        'MC_Wdecay2_from_t_eta',
        'MC_Wdecay2_from_t_phi',
        'MC_Wdecay2_from_t_m',
        'MC_Wdecay2_from_t_pdgId',
        'MC_tbar_beforeFSR_pt',
        'MC_tbar_beforeFSR_eta',
        'MC_tbar_beforeFSR_phi',
        'MC_tbar_beforeFSR_m',
        'MC_tbar_beforeFSR_pdgId',
        'MC_tbar_afterFSR_pt',
        'MC_tbar_afterFSR_eta',
        'MC_tbar_afterFSR_phi',
        'MC_tbar_afterFSR_m',
        'MC_tbar_afterFSR_pdgId',
        'MC_W_from_tbar_pt',
        'MC_W_from_tbar_eta',
        'MC_W_from_tbar_phi',
        'MC_W_from_tbar_m',
        'MC_W_from_tbar_pdgId',
        'MC_bbar_from_tbar_pt',
        'MC_bbar_from_tbar_eta',
        'MC_bbar_from_tbar_phi',
        'MC_bbar_from_tbar_m',
        'MC_bbar_from_tbar_pdgId',
        'MC_Wdecay1_from_tbar_pt',
        'MC_Wdecay1_from_tbar_eta',
        'MC_Wdecay1_from_tbar_phi',
        'MC_Wdecay1_from_tbar_m',
        'MC_Wdecay1_from_tbar_pdgId',
        'MC_Wdecay2_from_tbar_pt',
        'MC_Wdecay2_from_tbar_eta',
        'MC_Wdecay2_from_tbar_phi',
        'MC_Wdecay2_from_tbar_m',
        'MC_Wdecay2_from_tbar_pdgId',
        'MC_H_pt',
        'MC_H_eta',
        'MC_H_phi',
        'MC_H_m',
        'MC_Hdecay1_pt',
        'MC_Hdecay1_eta',
        'MC_Hdecay1_phi',
        'MC_Hdecay1_m',
        'MC_Hdecay1_pdgId',
        'MC_Hdecay2_pt',
        'MC_Hdecay2_eta',
        'MC_Hdecay2_phi',
        'MC_Hdecay2_m',
        'MC_Hdecay2_pdgId',
        'MC_Hdecay1_decay1_pt',
        'MC_Hdecay1_decay1_eta',
        'MC_Hdecay1_decay1_phi',
        'MC_Hdecay1_decay1_m',
        'MC_Hdecay1_decay1_pdgId',
        'MC_Hdecay2_decay1_pt',
        'MC_Hdecay2_decay1_eta',
        'MC_Hdecay2_decay1_phi',
        'MC_Hdecay2_decay1_m',
        'MC_Hdecay2_decay1_pdgId',
        'MC_Hdecay1_decay2_pt',
        'MC_Hdecay1_decay2_eta',
        'MC_Hdecay1_decay2_phi',
        'MC_Hdecay1_decay2_m',
        'MC_Hdecay1_decay2_pdgId',
        'MC_Hdecay2_decay2_pt',
        'MC_Hdecay2_decay2_eta',
        'MC_Hdecay2_decay2_phi',
        'MC_Hdecay2_decay2_m',
        'MC_Hdecay2_decay2_pdgId',
    ],
    "Tzq" : [
        "MC_t_beforeFSR_m",
        "MC_t_beforeFSR_pt",
        "MC_t_beforeFSR_eta",
        "MC_t_beforeFSR_phi",
        "MC_t_beforeFSR_pdgId",
        "MC_t_afterFSR_m",
        "MC_t_afterFSR_pt",
        "MC_t_afterFSR_eta",
        "MC_t_afterFSR_phi",
        "MC_t_afterFSR_pdgId",
        "MC_W_from_t_m",
        "MC_W_from_t_pt",
        "MC_W_from_t_eta",
        "MC_W_from_t_phi",
        "MC_W_from_t_pdgId",
        "MC_b_from_t_m",
        "MC_b_from_t_pt",
        "MC_b_from_t_eta",
        "MC_b_from_t_phi",
        "MC_b_from_t_pdgId",
        "MC_Wdecay1_from_t_m",
        "MC_Wdecay1_from_t_pt",
        "MC_Wdecay1_from_t_eta",
        "MC_Wdecay1_from_t_phi",
        "MC_Wdecay1_from_t_pdgId",
        "MC_Wdecay2_from_t_m",
        "MC_Wdecay2_from_t_pt",
        "MC_Wdecay2_from_t_eta",
        "MC_Wdecay2_from_t_phi",
        "MC_Wdecay2_from_t_pdgId",
        "MC_Z_m",
        "MC_Z_pt",
        "MC_Z_eta",
        "MC_Z_phi",
        "MC_Zdecay1_m",
        "MC_Zdecay1_pt",
        "MC_Zdecay1_eta",
        "MC_Zdecay1_phi",
        "MC_Zdecay1_pdgId",
        "MC_Zdecay1_status",
        "MC_Zdecay2_m",
        "MC_Zdecay2_pt",
        "MC_Zdecay2_eta",
        "MC_Zdecay2_phi",
        "MC_Zdecay2_pdgId",
        "MC_Zdecay2_status",
        "MC_b_m",
        "MC_b_pt",
        "MC_b_eta",
        "MC_b_phi",
        "MC_b_pdgId",
        "MC_q_m",
        "MC_q_pt",
        "MC_q_eta",
        "MC_q_phi",
        "MC_q_pdgId",
    ],
    "Thq" : [
        "MC_t_beforeFSR_m",
        "MC_t_beforeFSR_pt",
        "MC_t_beforeFSR_eta",
        "MC_t_beforeFSR_phi",
        "MC_t_beforeFSR_pdgId",
        "MC_t_afterFSR_m",
        "MC_t_afterFSR_pt",
        "MC_t_afterFSR_eta",
        "MC_t_afterFSR_phi",
        "MC_t_afterFSR_pdgId",
        "MC_W_from_t_m",
        "MC_W_from_t_pt",
        "MC_W_from_t_eta",
        "MC_W_from_t_phi",
        "MC_W_from_t_pdgId",
        "MC_b_from_t_m",
        "MC_b_from_t_pt",
        "MC_b_from_t_eta",
        "MC_b_from_t_phi",
        "MC_b_from_t_pdgId",
        "MC_Wdecay1_from_t_m",
        "MC_Wdecay1_from_t_pt",
        "MC_Wdecay1_from_t_eta",
        "MC_Wdecay1_from_t_phi",
        "MC_Wdecay1_from_t_pdgId",
        "MC_Wdecay2_from_t_m",
        "MC_Wdecay2_from_t_pt",
        "MC_Wdecay2_from_t_eta",
        "MC_Wdecay2_from_t_phi",
        "MC_Wdecay2_from_t_pdgId",
        'MC_H_pt',
        'MC_H_eta',
        'MC_H_phi',
        'MC_H_m',
        'MC_Hdecay1_pt',
        'MC_Hdecay1_eta',
        'MC_Hdecay1_phi',
        'MC_Hdecay1_m',
        'MC_Hdecay1_pdgId',
        'MC_Hdecay2_pt',
        'MC_Hdecay2_eta',
        'MC_Hdecay2_phi',
        'MC_Hdecay2_m',
        'MC_Hdecay2_pdgId',
        'MC_Hdecay1_decay1_pt',
        'MC_Hdecay1_decay1_eta',
        'MC_Hdecay1_decay1_phi',
        'MC_Hdecay1_decay1_m',
        'MC_Hdecay1_decay1_pdgId',
        'MC_Hdecay2_decay1_pt',
        'MC_Hdecay2_decay1_eta',
        'MC_Hdecay2_decay1_phi',
        'MC_Hdecay2_decay1_m',
        'MC_Hdecay2_decay1_pdgId',
        'MC_Hdecay1_decay2_pt',
        'MC_Hdecay1_decay2_eta',
        'MC_Hdecay1_decay2_phi',
        'MC_Hdecay1_decay2_m',
        'MC_Hdecay1_decay2_pdgId',
        'MC_Hdecay2_decay2_pt',
        'MC_Hdecay2_decay2_eta',
        'MC_Hdecay2_decay2_phi',
        'MC_Hdecay2_decay2_m',
        'MC_Hdecay2_decay2_pdgId',
        "MC_b_m",
        "MC_b_pt",
        "MC_b_eta",
        "MC_b_phi",
        "MC_b_pdgId",
        "MC_q_m",
        "MC_q_pt",
        "MC_q_eta",
        "MC_q_phi",
        "MC_q_pdgId",
    ],
    "Tqgamma" : [
        "MC_t_beforeFSR_m",
        "MC_t_beforeFSR_pt",
        "MC_t_beforeFSR_eta",
        "MC_t_beforeFSR_phi",
        "MC_t_beforeFSR_pdgId",
        "MC_t_afterFSR_m",
        "MC_t_afterFSR_pt",
        "MC_t_afterFSR_eta",
        "MC_t_afterFSR_phi",
        "MC_t_afterFSR_pdgId",
        "MC_W_from_t_m",
        "MC_W_from_t_pt",
        "MC_W_from_t_eta",
        "MC_W_from_t_phi",
        "MC_W_from_t_pdgId",
        "MC_b_from_t_m",
        "MC_b_from_t_pt",
        "MC_b_from_t_eta",
        "MC_b_from_t_phi",
        "MC_b_from_t_pdgId",
        "MC_Wdecay1_from_t_m",
        "MC_Wdecay1_from_t_pt",
        "MC_Wdecay1_from_t_eta",
        "MC_Wdecay1_from_t_phi",
        "MC_Wdecay1_from_t_pdgId",
        "MC_Wdecay2_from_t_m",
        "MC_Wdecay2_from_t_pt",
        "MC_Wdecay2_from_t_eta",
        "MC_Wdecay2_from_t_phi",
        "MC_Wdecay2_from_t_pdgId",
        "MC_gamma_m",
        "MC_gamma_pt",
        "MC_gamma_eta",
        "MC_gamma_phi",
        "MC_gamma_origin",
        "MC_b_m",
        "MC_b_pt",
        "MC_b_eta",
        "MC_b_phi",
        "MC_b_pdgId",
        "MC_q_m",
        "MC_q_pt",
        "MC_q_eta",
        "MC_q_phi",
        "MC_q_pdgId",
    ],
    "Ttgamma" : [
        "MC_t_beforeFSR_m",
        "MC_t_beforeFSR_pt",
        "MC_t_beforeFSR_eta",
        "MC_t_beforeFSR_phi",
        "MC_t_beforeFSR_pdgId",
        "MC_t_afterFSR_m",
        "MC_t_afterFSR_pt",
        "MC_t_afterFSR_eta",
        "MC_t_afterFSR_phi",
        "MC_t_afterFSR_pdgId",
        "MC_tbar_beforeFSR_m",
        "MC_tbar_beforeFSR_pt",
        "MC_tbar_beforeFSR_eta",
        "MC_tbar_beforeFSR_phi",
        "MC_tbar_beforeFSR_pdgId",
        "MC_tbar_afterFSR_m",
        "MC_tbar_afterFSR_pt",
        "MC_tbar_afterFSR_eta",
        "MC_tbar_afterFSR_phi",
        "MC_tbar_afterFSR_pdgId",
        "MC_W_from_t_m",
        "MC_W_from_t_pt",
        "MC_W_from_t_eta",
        "MC_W_from_t_phi",
        "MC_W_from_t_pdgId",
        "MC_W_from_tbar_m",
        "MC_W_from_tbar_pt",
        "MC_W_from_tbar_eta",
        "MC_W_from_tbar_phi",
        "MC_W_from_tbar_pdgId",
        "MC_b_from_t_m",
        "MC_b_from_t_pt",
        "MC_b_from_t_eta",
        "MC_b_from_t_phi",
        "MC_b_from_t_pdgId",
        "MC_bbar_from_tbar_m",
        "MC_bbar_from_tbar_pt",
        "MC_bbar_from_tbar_eta",
        "MC_bbar_from_tbar_phi",
        "MC_bbar_from_tbar_pdgId",
        "MC_Wdecay1_from_t_m",
        "MC_Wdecay1_from_t_pt",
        "MC_Wdecay1_from_t_eta",
        "MC_Wdecay1_from_t_phi",
        "MC_Wdecay1_from_t_pdgId",
        "MC_Wdecay2_from_t_m",
        "MC_Wdecay2_from_t_pt",
        "MC_Wdecay2_from_t_eta",
        "MC_Wdecay2_from_t_phi",
        "MC_Wdecay2_from_t_pdgId",
        "MC_Wdecay1_from_tbar_m",
        "MC_Wdecay1_from_tbar_pt",
        "MC_Wdecay1_from_tbar_eta",
        "MC_Wdecay1_from_tbar_phi",
        "MC_Wdecay1_from_tbar_pdgId",
        "MC_Wdecay2_from_tbar_m",
        "MC_Wdecay2_from_tbar_pt",
        "MC_Wdecay2_from_tbar_eta",
        "MC_Wdecay2_from_tbar_phi",
        "MC_Wdecay2_from_tbar_pdgId",
        "MC_gamma_m",
        "MC_gamma_pt",
        "MC_gamma_eta",
        "MC_gamma_phi",
        "MC_gamma_origin",
    ],
    "HWW" : [
        'MC_H_pt',
        'MC_H_eta',
        'MC_H_phi',
        'MC_H_m',
        'MC_H_pdgId',
        'MC_Hdecay1_pt',
        'MC_Hdecay1_eta',
        'MC_Hdecay1_phi',
        'MC_Hdecay1_m',
        'MC_Hdecay1_pdgId',
        'MC_Hdecay2_pt',
        'MC_Hdecay2_eta',
        'MC_Hdecay2_phi',
        'MC_Hdecay2_m',
        'MC_Hdecay2_pdgId',
        'MC_Hdecay1_decay1_pt',
        'MC_Hdecay1_decay1_eta',
        'MC_Hdecay1_decay1_phi',
        'MC_Hdecay1_decay1_m',
        'MC_Hdecay1_decay1_pdgId',
        'MC_Hdecay2_decay1_pt',
        'MC_Hdecay2_decay1_eta',
        'MC_Hdecay2_decay1_phi',
        'MC_Hdecay2_decay1_m',
        'MC_Hdecay2_decay1_pdgId',
        'MC_Hdecay1_decay2_pt',
        'MC_Hdecay1_decay2_eta',
        'MC_Hdecay1_decay2_phi',
        'MC_Hdecay1_decay2_m',
        'MC_Hdecay1_decay2_pdgId',
        'MC_Hdecay2_decay2_pt',
        'MC_Hdecay2_decay2_eta',
        'MC_Hdecay2_decay2_phi',
        'MC_Hdecay2_decay2_m',
        'MC_Hdecay2_decay2_pdgId'
    ],
    "HZZ" : [
        'MC_H_pt',
        'MC_H_eta',
        'MC_H_phi',
        'MC_H_m',
        'MC_H_pdgId',
        'MC_Hdecay1_pt',
        'MC_Hdecay1_eta',
        'MC_Hdecay1_phi',
        'MC_Hdecay1_m',
        'MC_Hdecay1_pdgId',
        'MC_Hdecay2_pt',
        'MC_Hdecay2_eta',
        'MC_Hdecay2_phi',
        'MC_Hdecay2_m',
        'MC_Hdecay2_pdgId',
        'MC_Hdecay1_decay1_pt',
        'MC_Hdecay1_decay1_eta',
        'MC_Hdecay1_decay1_phi',
        'MC_Hdecay1_decay1_m',
        'MC_Hdecay1_decay1_pdgId',
        'MC_Hdecay2_decay1_pt',
        'MC_Hdecay2_decay1_eta',
        'MC_Hdecay2_decay1_phi',
        'MC_Hdecay2_decay1_m',
        'MC_Hdecay2_decay1_pdgId',
        'MC_Hdecay1_decay2_pt',
        'MC_Hdecay1_decay2_eta',
        'MC_Hdecay1_decay2_phi',
        'MC_Hdecay1_decay2_m',
        'MC_Hdecay1_decay2_pdgId',
        'MC_Hdecay2_decay2_pt',
        'MC_Hdecay2_decay2_eta',
        'MC_Hdecay2_decay2_phi',
        'MC_Hdecay2_decay2_m',
        'MC_Hdecay2_decay2_pdgId',
    ]
}

class truthConfig(ConfigBlock):
    """ConfigBlock for truth/parton-level objects"""

    def __init__(self):
        super(truthConfig, self).__init__()
        self.addOption('histories', None, type=str)

    def makeAlgs(self, config):

        if config.dataType() is DataType.Data: return

        # loop over all histories
        for history in self.getPartonHistories():
            alg = config.createAlgorithm("top::RunPartonHistoryAlg", "PartonHistory" + history)
            alg.partonScheme = history
            container = "PartonHistory" + history
            _ = config.writeName(container)

            for branch in truth_branches[history]:
                config.addOutputVar(container, branch, branch, noSys=True)

    def getPartonHistories(self):
        # parton histories can be provided as History1.History2.etc
        return self.histories.split(".")

    def getOutputContainers(self):
        # return a dictionary of containers that can be added to the OutputAnalysisConfig
        containerDict = {}
        for history in self.getPartonHistories():
            containerDict[history + '_'] = 'PartonHistory' + history
        return containerDict
