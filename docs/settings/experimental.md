## [EventSelectionTestConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/EventSelectionTestConfig.py)

Implements a lepton+jets $t\bar{t}$ selection. See [source code](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/Root/EventSelectionTestAlg.cxx).

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`.

`btagDecoration`
:   the full b-tagger and WP selection decoration, e.g. `ftag_select_DL1dv01_FixedCutBEff_77`.

!!! success "Registers the following variables:"
    - `event_pass`: the event-level decision of the full filter
    - `ejets_pass`: the event-level decision of the electron+jets selection
    - `mujets_pass`: the event-level decision of the muon+jets selection

## [ExtraParticleDecorationConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/ExtraParticleDecorationConfig.py)

Allows to add generic particle decorations and save them as output variables.

`particles`
:   the input particle container.

!!! success "Registers the following variables:"
    - `e`: object $E$

## [LeptonSFCalculatorConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/LeptonSFCalculatorConfig.py)

Computes the per-event lepton (electrons and muons) scale factors.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`lepton_postfix`
:   the common postfix for both electrons and muons, e.g. `'tight'`.

!!! success "Registers the following variables:"
    - `leptonSF`: the per-event lepton SF, the product of the electron reconstruction/ID/isolation SFs and the muon reconstruction/TTVA/isolation SFs