## [KLFitterConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/KLFitterConfig.py)

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`met`
:   the input MET container. The default is `''` (empty string).

`likelihoodType`
:   KLFitter likelihood, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`leptonType`
:   type of lepton to use (only relevant to certain likelihood types), if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`jetSelectionMode`
:   jet selection mode to use, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`btaggingMethod`
:   strategy to handle b-jets, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`bTagCDIFile`
:   CDI file to pass to the b-tagging efficiency tool. The default is `xAODBTaggingEfficiency/13TeV/2022-22-13TeV-MC20-CDI-2022-07-28_v1.root`.

`btagger`
:   b-tagging algorithm to use, if only one is needed. The default is `DL1dv00`.

`btagWP`
:   b-tagging efficiency WP to use, if only one is needed. The default is `FixedCutBEff_77`.

`selectionRegionsConfig`
:   string of the form `selectionName: sel1, optionA: opA, optionB: opB; selectionName: sel2, ...` where options can be `likelihoodType`, `leptonType`, `jetSelectionMode`, `btaggingMethod`, `btagger` or `btagWP`. The default is `''` (empty string).

`saveAllPermutations`
:   whether to save all permutations, or just the best one. The default is `False` (only save the best one).

!!! success "Registers the following variables:"
    - `eventProbability`: the event probability
    - `logLikelihood`: the log of the likelihood

!!! note
    The source code and documentation for KLFitter are available from [github](https://github.com/KLFitter/KLFitter).

## [TopSpaNetConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TopSpaNetConfig.py)

`btagger`
:   b-tagging algorithm to use, if only one is needed. The default is `DL1dv01`.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`met`
:   the input MET container. The default is `''` (empty string).

`eventSelection`
:   optional event filter to run on. The default is `''` (empty string), i.e. all events.

`topology`
:   the SPA-Net model to run. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopSpaNet/SpaNetEnums.h).

!!! success "Registers up to 4 types of topology-dependent variables:"
    - `index`: index within a given container of the relevant particle candidate
    - `assignment`: quality of the system reconstruction
    - `detection`: likelihood of the event containing all necessary decay products to reconstruct the system
    - `reg`: regressed kinematic properties