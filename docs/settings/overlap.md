## [makeOverlapAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/OverlapAnalysisConfig.py)

`seq`
:   the config sequence.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`inputLabel`
:   any possible label used to pick up the selected objects with. This should not be a label already used elsewhere, e.g. `preselectOR`.

`outputLabel`
:   decoration applied (internally) to the output objects, e.g. `passesOR`.

`linkOverlapObjects`
:   whether to set up an element link between overlapping objects. The default is `False`.

`doEleEleOR`
:   whether to set up the electron-electron overlap removal (instance of [`ORUtils::EleEleOverlapTool`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/AnalysisCommon/AssociationUtils/Root/EleEleOverlapTool.cxx)). The default is `False`.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`.

`taus`
:   the input tau container, with a possible selection, in the format `container` or `container.selection`.

`photons`
:   the input photon containe, with a possible selection, in the format `container` or `container.selection`r.

`fatJets`
:   the input large-R jet container, with a possible selection, in the format `container` or `container.selection`.

`enableUserPriority`
:   whether to use the user's custom priority ranking, instead of the recommended one. If set to `True`, will respect the priorities set with `inputLabel` (e.g. in SUSYTools, every object gets priority 2, but pre-selected jets get priority 1). The default is `False`.

`bJetLabel`
:   flag to select b-jets with. If left empty, no b-jets are used in the overlap removal. The default is `''` (empty string).

`boostedLeptons`
:   whether to enable boosted lepton overlap removal (toggles on the property `UseSlidingDR` of the [`ORUtils::EleJetOverlapTool`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/AnalysisCommon/AssociationUtils/Root/EleJetOverlapTool.cxx) and [`ORUtils::MuJetOverlapTool`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/AnalysisCommon/AssociationUtils/Root/MuJetOverlapTool.cxx) tools). The default is `False`.

`configName`
:   name of the block config, useful to distinguish the various blocks if different overlap removal strategies are set up. The default is `OverlapRemoval`.

!!! success "Registers the following variables:"
    - `select_or`: the per-object overlap removal decision

