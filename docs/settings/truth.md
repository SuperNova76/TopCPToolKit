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