## [makeElectronCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all electrons.

`crackVeto`
:   whether to perform LAr crack veto, i.e. remove electrons within $1.37<\vert\eta\vert<1.52$. The default is `False`.

`ptSelectionOutput`
:   whether or not to apply the default $p_\mathrm{T} > 4.5$ GeV cut to calibrated electrons. The default is `False`.

`isolationCorrection`
:   whether or not to perform isolation corrections (leakage corrections), i.e. set up an instance of [`CP::EgammaIsolationCorrectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaIsolationCorrectionAlg.cxx).

!!! success "Registers the following variables:"
    - `pt`: electron $p_\mathrm{T}$
    - `eta`: electron $\eta$ (no systematics)
    - `phi`: electron $\phi$ (no systematics)
    - `charge`: electron charge (no systematics)

## [makeElectronWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different electron definitions.

`workingPoint`
:   the ID and isolation WPs to use. Pass them in the format `likelihood.isolation`. Supported ID WPs: `TightLH`, `MediumLH`, `LooseBLayerLH`. Supported isolation WPs: `HighPtCaloOnly`, `Loose_VarRad`, `Tight_VarRad`, `TightTrackOnly_VarRad`, `TightTrackOnly_FixedRad`, `NonIso`.

`recomputeLikelihood`
:   whether to rerun the LH. The default is `False`, i.e. to use derivation flags.

!!! warning
    The only way to get the DNN ID at the moment is to recompute the likelihood, as it's not stored in derivations.

`chargeIDSelection`
:   whether to run the [ECIDS tool](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/ElectronPhotonID/ElectronPhotonSelectorTools/Root/AsgElectronChargeIDSelectorTool.cxx?v=21.2). The default is `False`.

!!! warning
    ECIDS is actually not supported in release 24. It will likely become part of the DNN ID.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the electron passes the ID and isolation cuts
    - `reco_effSF`: the per-electron reconstruction SF
    - `id_effSF`: the per-electron ID SF
    - `isol_effSF`: the per-electron isolation SF
