## Make-methods

!!! warning
    No such method exist for experimental algorithms!

## Config blocks

### [ExtraParticleDecorationConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/ExtraParticleDecorationConfig.py)

Allows to add generic particle decorations and save them as output variables.

`particles`
:   the input particle container.

!!! success "Registers the following variables:"
    - `e`: object $E$

### [LeptonSFCalculatorConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/LeptonSFCalculatorConfig.py)

Computes the per-event lepton (electrons and muons) scale factors.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`lepton_postfix`
:   the common postfix for both electrons and muons, e.g. `'tight'`.

!!! success "Registers the following variables:"
    - `leptonSF`: the per-event lepton SF, the product of the electron reconstruction/ID/isolation SFs and the muon reconstruction/TTVA/isolation SFs


### [BTagScoresConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/BTagScoresConfig.py)

Computes per-jet b-tagging score and jet origin (bottom/charm/light) probabilities.

`minPt`
:   minimum jet $p_\mathrm{T}$ used in the configuration of the b-tagging selection tool. 

`bTagCalibFile`
:   path (string) to a custom b-tagging CDI file. The default is `None`, which uses the latest available recommendations.

`taggerName`
:   the flavour tagging algorithm: `DL1dv01`, `GN2v00LegacyWP`. The default is `GN2v00LegacyWP`.

`eventSelection`
:   optional event filter to run on. The default is `''` (empty string), i.e. all events.

`saveAllProbabilities`
:   this bool controls whether only the b-tag score is saved or all the probabilities are also saved. The default value is `True`.

!!! success "Registers the following variables:"
    - `btagScores`: the per-jet b-tagging score. This is a combination of the jet origin probabilities.
    - `prob_pb`: the probability of the jet origin being related to a bottom quark.
    - `prob_pc`: the probability of the jet origin being related to a charm quark.
    - `prob_pl`: the probability of the jet origin being related to a light quark.