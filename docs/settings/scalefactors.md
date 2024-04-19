Various scale factors are computed by the respective CP algorithms. The default approach is that the relevant object blocks compute and decorate per-object SFs, and some of them also by default store these per-object SFs as vectors of floats in the output NTuple. Please refer to the documentation of the relevant objects under [Settings](index.md).

!!! tip
    To disable the per-object SFs, use the branch filtering feature of [`OutputAnalysisConfig``](ntupling.md/#outputanalysisconfig).

<!---
## Make-methods

!!! warning
    No such method exist yet for event-level scale factor algorithms!
--->

## Config blocks

### [PerEventSFBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)
Name in YAML: **PerEventSF**

Calculates a per-event SF which is the product of per-object SFs, for objects passing an optional selection.

`algoName`
:   unique name given to the underlying algorithm computing the per-event scale factors

`particles`
:   the input object container, with a possible selection, in the format `container` or `container.selection`.

`objectSF`
:   the name of the per-object SF decoration to be used.

`eventSF`
:   the name of the per-event SF decoration.

!!! success "Registers the following variables:"
    - The name of the output variable is the same as the one specified in the `eventSF` option.

### [LeptonSFCalculatorConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/LeptonSFCalculatorConfig.py)
Name in YAML: **LeptonSF**

Computes the per-event lepton SF, i.e. a product over the individual reconstruction, identification and isolation SFs for all electrons, muons or photons in the event.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`photons`
:   the input photon container, with a possible selection, in the format `container` or `container.selection`.

`lepton_postfix`
:   the common postfix for both electrons and muons, e.g. `'tight'`.

!!! success "Registers the following variables:"
    - `leptonSF`: the per-event lepton SF, the product of the electron reconstruction/ID/isolation SFs, the muon reconstruction/TTVA/isolation SFs, and the photon ID/isolation SFs

### [FTagEventSFConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/FTagAnalysisAlgorithms/python/FTagEventSFAnalysisConfig.py)
Name in YAML: **FlavourTaggingEventSF**

Computes the per-event b-tagging SF, i.e. a product of b-tagging efficiency/inefficiency SFs over all jets in the specified jet container, which are within the region of validity of the FTAG calibrations. See the `containerName` argument below for passing jets with specific selection. The per-event scale factor `weight_ftag_effSF_<selectionName>` is decorated to EventInfo object (see `selectionName` below).

`containerName`
:   the input jet container with a possible selection, in the format `container` or `container.selection`. The default recommendation is to pass `container.baselineJvt` selection, e.g. if the calibrated jets container is `AnaJets`, the recommendation is to pass `AnaJet.baselineJvt`.

`selectionName`
:   the postfix to apply to the scale factor decoration. By default not needed, since the default selectionName used is `<btagger>_<btagWP>`.

`btagger`
:   the flavour tagging algorithm: `DL1dv01`, `GN2v00`.

`btagWP`
:   the flavour tagging WP. The default is `FixedCutBEff_77`.
