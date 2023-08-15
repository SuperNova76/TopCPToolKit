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

## [TtbarAnalysisConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TtbarAnalysisConfig.py)

This is an example config, setting up two simples algorithms: [`top::TtbarCPalgoAnalysis`](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/Root/TtbarCPalgoAnalysis.cxx), to apply energy decorations to muons and jets, and [`top::LeptonSFCalculator`](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/Root/LeptonSFCalculator.cxx), to turn the per-lepton SFs into a per-event SF.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`.

`lepton_postfix`
:   the common postfix used for both electrons and muons (e.g. `tight`).

!!! success "Registers the following variables:"
    - `leptonSF`: the event-level lepton SF