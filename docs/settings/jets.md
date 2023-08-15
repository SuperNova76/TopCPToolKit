## [makeJetAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/python/JetAnalysisConfig.py)

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

!!! success "Registers the following variables:"
    - `pt`: jet $p_\mathrm{T}$
    - `m`: jet mass
    - `eta`: jet $\eta$ (no systematics)
    - `phi`: jet $\phi$ (no systematics)

### Additional options for small-R jets

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

`reduction`
:   the NP reduction scheme to use for JES: `All`, `Global`, `Category`, `Scenario`. The default is `Global`.

`JEROption`
:   the NP reduction scheme to use for JER: `All`, `Full`, `Simple`. The default is `Simple`.

!!! note
    Not all combinations of `reduction` and `JEROption` are valid! Please refer to the [JetETmiss twiki](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/JetUncertaintiesRel22).

!!! success "Registers the following variables:"
    - `jvtEfficiency`: the per-jet JVT efficiency SF

### Additional options for large-R jets

`largeRMass`
:   which large-R mass definition to use: `Comb`, `Calo`, `TA`. The default is `Comb`.


## [makeJetJvtAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/JetAnalysisAlgorithms/python/JetJvtAnalysisConfig.py)

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

!!! tip
    Since variables attached to `EventInfo` cannot be added automatically from the config blocks at the moment, you probably want to do it by hand for `jvt_effSF_%SYS%` and `fjvt_effSF_%SYS%`, the resulting per-event SFs.

## [makeFTagAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/FTagAnalysisAlgorithms/python/FTagAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`btagger`
:   the flavour tagging algorithm: `DL1dv01`, `GN2v00`. The default is `DL1r`.

`btagWP`
:   the flavour tagging WP. The default is `FixedCutBEff_77`.

`generator`
:   MC generator setup, for MC/MC SFs. The default is `default` (Powheg+Pythia8). A DSID string is expected, see [MC/MC Scale Factors using Top Samples](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PmgTopProcesses#FTAG_MC_MC_Scale_Factors_using_T).

`kinematicSelection`
:   whether to run kinematic selection. The default is `True`.

`noEfficiency`
:   whether to calculate efficiencies. The default is `False` (i.e. compute them).

`legacyRecommendations`
:   whether to use legacy recommendations without shallow-copied containers. The default is `False`.

`minPt`
:   minimum jet $p_\mathrm{T}$ used in the kinematic selection of jets. The default is 20 GeV for EMPFlow and EMTopo jets, or 10 GeV for VR-track jets.

!!! success "Registers the following variables (all names preceded by the tagger + WP combination):"
    - `select`: the per-jet tagging decision (no systematics)
    - `quantile`: only for pseudo-continuous b-tagging, the per-jet PCBT bin (no systematics)
    - `eff`: the per-jet b-tagging efficiency SF