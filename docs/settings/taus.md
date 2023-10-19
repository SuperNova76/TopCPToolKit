## Make-methods

### [makeTauCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/python/TauAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all taus.

`rerunTruthMatching`
:   whether to rerun truth matching (sets up an instance of [`CP::TauTruthMatchingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/Root/TauTruthMatchingAlg.cxx)). The default is `True`.

!!! success "Registers the following variables:"
    - `pt`: tau $p_\mathrm{T}$
    - `eta`: tau $\eta$ (no systematics)
    - `phi`: tau $\phi$ (no systematics)
    - `charge`: tau charge (no systematics)

### [makeTauWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/python/TauAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different tau definitions.

`workingPoint`
:   the ID WP to use (single string). Supported ID WPs: `Tight`, `Medium`, `Loose`, `VeryLoose`, `NoID`.

`legacyRecommendations`
:   whether to use legacy tau BDT and electron veto recommendations. The default is `False`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the tau passes the ID cuts
    - `effSF`: the per-tau reconstruction SF

## Config blocks

### [TauCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/python/TauAnalysisConfig.py)

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all taus.

`rerunTruthMatching`
:   whether to rerun truth matching (sets up an instance of [`CP::TauTruthMatchingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/Root/TauTruthMatchingAlg.cxx)). The default is `True`.

!!! success "Registers the following variables:"
    - `pt`: tau $p_\mathrm{T}$
    - `eta`: tau $\eta$ (no systematics)
    - `phi`: tau $\phi$ (no systematics)
    - `charge`: tau charge (no systematics)

### [TauWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TauAnalysisAlgorithms/python/TauAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different tau definitions.

`quality`
:   the ID WP (string) to use. Supported ID WPs: `Tight`, `Medium`, `Loose`, `VeryLoose`, `NoID`.

`legacyRecommendations`
:   whether to use legacy tau BDT and electron veto recommendations. The default is `False`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the tau passes the ID cuts
    - `effSF`: the per-tau reconstruction SF