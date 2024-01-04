## Make-methods

!!! warning
    No such method exist yet for truth-related algorithms!

## Config blocks

### [truthConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/truthConfig.py)

`histories`
:   parton-level interpretations of the MC truth record. Multiple histories can be provided as `history1.history2.etc`. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/truthConfig.py) (keys of the `truth_branches` dictionary).

!!! success "Registers history-dependent variables:"
    - in the format `history_MC_resonance_variable` (no systematics)

### [particleLevelConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/particleLevelConfig.py)

`useTruthElectrons`
:   whether to use electrons. The default is `True`.

`el_ptMin`
:   minimum electron $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`el_etaMax`
:   maximum electron $\vert\eta\vert$. The default is 2.5.

`el_notFromHadron`
:   whether to reject electrons originating from hadronic decays. The default is `True` (reject them).

`el_tauIsHadron`
:   whether to consider tauons as hadrons in the above rejection. The default is `False` (don't consider them as hadrons).

`useTruthMuons`
:   whether to use muons. The default is `True`.

`mu_ptMin`
:   minimum muon $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`mu_etaMax`
:   maximum muon $\vert\eta\vert$. The default is 2.5.

`mu_notFromHadron`
:   whether to reject muons originating from hadronic decays. The default is `True` (reject them).

`mu_tauIsHadron`
:   whether to consider tauons as hadrons in the above rejection. The default is `False` (don't consider them as hadrons).

`useTruthPhotons`
:   whether to use photons. The default is `False`.

`ph_ptMin`
:   minimum photon $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`ph_etaMax`
:   maximum photon $\vert\eta\vert$. The default is 2.5.

`ph_origin`
:   comma-separated list (string) of particle origin values as given by the `MCTruthClassifier`. See [possible values](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h). The default is `''` (empty string).

`ph_isolation`
:   space-separated isolation variable and isolation cut (string), i.e. in the format `var cut` where `var` is an isolation variable and `cut` is applied as `var / pt < cut`. The default is `''` (empty string).

`useTruthTaus`
:   whether to use taus. The default is `False.`

`tau_ptMin`
:   minimum tau $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`tau_etaMax`
:   maximum tau $\vert\eta\vert$. The default is 2.5.

`useTruthJets`
:   whether to use jets. The default is `True`.

`ph_ptMin`
:   minimum jet $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`ph_etaMax`
:   maximum jet $\vert\eta\vert$. The default is 2.5.

`useTruthLargeRJets`
:   whether to use large-R jets. The default is `True`.

`ljet_ptMin`
:   minimum large-R jet $p_\mathrm{T}$, in MeV. The default is 25 GeV.

`ljet_etaMax`
:   maximum large-R jet $\vert\eta\vert$. The default is 2.5.

`useTruthMET`
:   whether to use MET. The default is `True`.

`doOverlapRemoval`
:   whether to perform overlap removal. The default is `True`.

!!! success "Registers the following variables, depending on the object:"
    - `pt`: $p_\mathrm{T}$ (no systematics)
    - `eta`: $\eta$ (no systematics)
    - `phi`: $\phi$ (no systematics)
    - `e`: $E$ (no systematics)
    - `type`: particle type according to the [`MCTruthClassifier`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h) (no systematics)
    - `origin`: particle origin according to the [`MCTruthClassifier`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/MCTruthClassifier/MCTruthClassifier/MCTruthClassifierDefs.h) (no systematics)
    - `charge`: charge (no systematics)
    - `IsHadronicTau`: whether the tau decays hadronically (no systematics)
    - `nGhosts_bHadron`: number of ghost-matched b-hadrons in the jet (no systematics)
    - `nGhosts_cHadron`: number of ghost-matched c-hadrons in the jet (no systematics)

### [TtbarNNLORecursiveRewConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TtbarNNLORecursiveRewConfig.py)

`sampleID`
:   force the DSID (string) to be used to configure the reweighting. The default is `AutoConfig`, i.e. use the file metadata.

`reweightType`
:   the kind of reweighting to perform (string). Supported options are: `2D`, `3D`. The default is `2D`.

`reweightPath`
:   the path (string) to the directory holding the histograms for reweighting. The default is `dev/AnalysisTop/TTbarNNLOReweighter`.

`reweightSuffix`
:   the suffix (string) to use when looking for the histograms. The default is `_3iter_2023_LUX`.

!!! success "Registers the following variables:"
    - `NNLO_type_weight`: NNLO weight (overall normalised to 1), where `type` reflects the `reweightType` option

### [PartonToJetsMatchConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/PartonToJetsMatchConfig.py)

The algorithm matches jets with partons from ttbar lepton+jets topology. The output of the algorithm are four variables representing the indices (for the jets) of the b-jets from hadronically and semileptonically decaying tops, jets matched to the up-type and down-type quarks from the hadronic W decay. Finally, a flag is added for dilepton events.
The matching algorithm looks for the closest jets in $\Delta R$. For multiple matches (or for dilepton events) the multi-matched objects have index set to -1.

`jets`
:   jet collection name (string) for matching, can be reco jets or truth jets. The default is `AntiKt4TruthDressedWZJets`.

`eventSelection`
:   event selection (string) for matching. The default is `pass_ejets_%SYS%||pass_mujets_%SYS%`.

`criticalDR`
:   maximum $\Delta R$ (float) used for matching. The default is `0.3`.

`partonContainerName`
:   name of the parton container (string) used for matching. The default is `TopPartonHistoryTtbar_NOSYS`.

!!! success "Registers the following variables:"
    - `parton_truth_lep_b_index`: the detector-level jet index corresponding to the parton-level leptonic b-quark
    - `parton_truth_had_b_index`: the detector-level jet index corresponding to the parton-level hadronic b-quark
    - `parton_truth_up_index`: the detector-level jet index corresponding to the parton-level up-type-quark from the hadronic-W decay
    - `parton_truth_down_index`: the detector-level jet index corresponding to the parton-level down-type-quark from the hadronic-W decay
    - `event_is_dilepton`: flags whether the parton-level event is dileptonic

### [JetMatchingConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/JetMatchingConfig.py)

The algorithm adds three variables for reco jets: index of matched truth jet, $\Delta R$ to the closest reco jet and $\Delta R$ of the matched truth jet and its closest truth jet. The matching is based on looking for minimal $\Delta R$. The reco jets with no matched truth jet (no truth jet found with $\Delta R$ within the critical $\Delta R$) have the index set to -1. If multiple reco jets are matched to the same truth jet their index is also set to -1.

`criticalDR`
:   maximum $\Delta R$ (float) used for matching. The default is `0.3`.

`jets`
:   reco jets container name (string). The default is `AnaJets`.

`truthJets`
:   truth jets collection name (string). The default is `AntiKt4TruthDressedWZJets`.

`eventSelection`
:   event selection (string) to run the algorithm on. The default is ` ` (run over all events).

!!! success "Registers the following variables:"
    - `truth_jet_paired_index`: the index of the truth-level jets matched to the detector-level jets
    - `reco_to_reco_jet_closest_dR`: the minimum $\Delta R$ with respect to detector-level jets
    - `truth_to_truth_jet_closest_dR`: the minimum $\Delta R$ of the matched truth-level jet with respect to truth-level jets

### [IFFLeptonDecorationBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`containerName`
:   the name of the input electron or muon container.

`separateChargeFlipElectrons`
:   whether to consider charged-flip electrons as a separate class. The default is `True` (recommended).

`decoration`
:   the name (str) of the decoration set by the [IFF `TruthClassificationTool`](https://gitlab.cern.ch/atlas/athena/-/tree/21.2/PhysicsAnalysis/AnalysisCommon/TruthClassification). The default is `'IFFClass_%SYS%'`.

!!! success "Registers the following variables:"
    - `IFFClass`: the decision of the [IFF `TruthClassificationTool`](https://gitlab.cern.ch/atlas/athena/-/tree/21.2/PhysicsAnalysis/AnalysisCommon/TruthClassification)  (no systematics)