## Make-methods

### [makeJetAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/python/JetAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different jet definitions.

`jetCollection`
:   the jet container to run on. It is interpreted to determine the correct config blocks to call for small- or large-R jets.

`runGhostMuonAssociation`
:   whether to set up the jet-ghost-muon association algorithm [`CP::JetGhostMuonAssociationAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/Root/JetGhostMuonAssociationAlg.cxx). The default is `False`.

`runTruthJetTagging`
:   whether to set up the jet truth tagging algorithm [`CP::JetTruthTagAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/Root/JetTruthTagAlg.cxx). The default is `True`.

!!! success "Registers the following variables:"
    - `pt`: jet $p_\mathrm{T}$
    - `m`: jet mass
    - `eta`: jet $\eta$ (no systematics)
    - `phi`: jet $\phi$ (no systematics)

#### Additional options for small-R jets

`runJvtUpdate`
:   whether to update the JVT. The default is `False`.

`runNNJvtUpdate`
:   whether to update the NN-JVT. The default is `False`.

`runFJvtUpdate`
:   whether to update the forward JVT. The default is `False`.

`runJvtSelection`
:   whether to run JVT selection. The default is `True`.

`runFJvtSelection`
:   whether to run forward JVT selection. The default is `False`.

`runJvtEfficiency`
:   whether to calculate the JVT efficiency. The default is `True`.

`runFJvtEfficiency`
:   whether to calculate the forward JVT efficiency. The default is `False`.

`systematicsModelJES`
:   the NP reduction scheme to use for JES: `All`, `Global`, `Category`, `Scenario`. The default is `Category`.

`systematicsModelJER`
:   the NP reduction scheme to use for JER: `All`, `Full`, `Simple`. The default is `Full`.

    !!! note
        Not all combinations of `systematicsModelJES` and `systematicsModelJER` are valid! Please refer to the [JetETmiss twiki](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/JetUncertaintiesRel22).

`recalibratePhyslite`
:   whether to run the [`CP::JetCalibrationAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/Root/JetCalibrationAlg.cxx) on PHYSLITE derivations. The default is `True`.

`calibToolConfigFile`
:   name (str) of the config file to use for the jet calibration tool. Expert option to override JetETmiss recommendations. The default is `None`.

`calibToolCalibArea`
:   name (str) of the CVMFS area to use for the jet calibration tool. Expert option to override JetETmiss recommendations. The default is `None`.

`calibToolCalibSeq`
:   name (str) of the sequence to use for the jet calibration tool (e.g. `'JetArea_Residual_EtaJES_GSC'`). Expert option to override JetETmiss recommendations. The default is `None`.

`uncertToolConfigPath`
:   name (str) of the config file to use for the jet uncertainty tool. Expert option to override JetETmiss recommendations. The default is `None`.

`uncertToolCalibArea`
:   name (str) of the CVMFS area to use for the jet uncertainty tool. Expert option to override JetETmiss recommendations. The default is `None`.

`uncertToolMCType`
:   data type (str) to use for the jet uncertainty tool (e.g. `'AFII'` or `'MC16'`). Expert option to override JetETmiss recommendations. The default is `None`.

!!! success "Registers the following variables:"
    - `jvtEfficiency`: the per-jet JVT efficiency SF (also for fJVT!)

#### Additional options for large-R jets

`largeRMass`
:   which large-R mass definition to use: `Comb`, `Calo`, `TA`. The default is `Comb`.


### [makeJetJvtAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/python/JetJvtAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`enableFJvt`
:   whether to enable forward JVT calculations. The default is `False`.

`globalSF`
:   whether to calculate per-event SFs. The default is `True`.

`runSelection`
:   whether to run the JVT selection. The default is `True`.

!!! success "Registers the following variables:"
    - `weight_jvt_effSF`: the event-level JVT efficiency SF
    - `weight_fjvt_effSF`: the event-level forward JVT efficiency SF
    - `select_jvt`: the per-jet JVT selection flag
    - `select_fjvt`: the per-jet fJVT selection flag

### [makeFTagAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/FTagAnalysisAlgorithms/python/FTagAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`selectionName`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as internally the string `f"{btagger}_{btagWP}"` is used.

`btagger`
:   the flavour tagging algorithm: `DL1dv01`, `GN2v00`. The default is `DL1r`.

`btagWP`
:   the flavour tagging WP. The default is `FixedCutBEff_77`.

`generator`
:   MC generator setup, for MC/MC SFs. The default is `default` (Powheg+Pythia8). A DSID string is expected, see [MC/MC Scale Factors using Top Samples](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PmgTopProcesses#FTAG_MC_MC_Scale_Factors_using_T).

`kinematicSelection`
:   whether to run kinematic selection. The default is `True`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

`minPt`
:   minimum jet $p_\mathrm{T}$ used in the kinematic selection of jets. The default is 20 GeV for EMPFlow and EMTopo jets, or 10 GeV for VR-track jets.

!!! success "Registers the following variables (all names preceded by the tagger + WP combination):"
    - `select`: the per-jet tagging decision (no systematics)
    - `quantile`: only for pseudo-continuous b-tagging, the per-jet PCBT bin (no systematics)
    - `eff`: the per-jet b-tagging efficiency SF

## Config blocks

### Jet calibration

!!! warning
    It is not recommended to use individual config blocks to set up your jet objects! Please instead rely on the he make-methods outlined above.
    These are the ones employed in both the [`ConfigFactory`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AnalysisAlgorithmsConfig/python/ConfigFactory.py) and [`ConfigText`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AnalysisAlgorithmsConfig/python/ConfigText.py) approaches.

### [JetJvtAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/python/JetJvtAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`enableFJvt`
:   whether to enable forward JVT calculations. The default is `False`.

`globalSF`
:   whether to calculate per-event SFs. The default is `True`.

`runSelection`
:   whether to run the JVT selection. The default is `True`.

!!! success "Registers the following variables:"
    - `weight_jvt_effSF`: the event-level JVT efficiency SF
    - `weight_fjvt_effSF`: the event-level forward JVT efficiency SF
    - `select_jvt`: the per-jet JVT selection flag
    - `select_fjvt`: the per-jet fJVT selection flag

### [FTagConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/FTagAnalysisAlgorithms/python/FTagAnalysisConfig.py)

`containerName`
:   the name of the input container.

`selectionName`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as internally the string `f"{btagger}_{btagWP}"` is used.

`btagger`
:   the flavour tagging algorithm: `DL1dv01`, `GN2v00`. The default is `DL1r`.

`btagWP`
:   the flavour tagging WP. The default is `FixedCutBEff_77`.

`generator`
:   MC generator setup, for MC/MC SFs. The default is `default` (Powheg+Pythia8). A DSID string is expected, see [MC/MC Scale Factors using Top Samples](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PmgTopProcesses#FTAG_MC_MC_Scale_Factors_using_T).

`kinematicSelection`
:   whether to run kinematic selection. The default is `True`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

`minPt`
:   minimum jet $p_\mathrm{T}$ used in the kinematic selection of jets. The default is 20 GeV for EMPFlow and EMTopo jets, or 10 GeV for VR-track jets.

`bTagCalibFile`
:   path (string) to a custom b-tagging CDI file. The default is `None`, which uses the latest available recommendations.

!!! success "Registers the following variables (all names preceded by the tagger + WP combination):"
    - `select`: the per-jet tagging decision (no systematics)
    - `quantile`: only for pseudo-continuous b-tagging, the per-jet PCBT bin (no systematics)
    - `eff`: the per-jet b-tagging efficiency SF