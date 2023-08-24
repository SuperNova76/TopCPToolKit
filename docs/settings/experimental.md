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