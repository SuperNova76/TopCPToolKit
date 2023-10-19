## Make-methods

### [makePhotonCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/PhotonAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all photons.

`crackVeto`
:   whether to perform LAr crack veto, i.e. remove photons within $1.37<\vert\eta\vert<1.52$. The default is `False`.

`enableCleaning`
:   whether to enable photon cleaning (`DFCommonPhotonsCleaning`). The default is `True`.

`cleaningAllowLate`
:   whether to ignore timing information in cleaning (`DFCommonPhotonsCleaningNoTime`). The default is `False`.

`recomputeIsEM`
:   whether to recompute the photon shower shape fudge corrections (sets up an instance of [`CP::PhotonShowerShapeFudgeAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/PhotonShowerShapeFudgeAlg.cxx)). The default is `False`, i.e. to use derivation variables.

`ptSelectionOutput`
:  whether or not to apply the default $p_\mathrm{T} > 10$ GeV cut to calibrated photons. The default is `False`.

!!! success "Registers the following variables:"
    - `pt`: photon $p_\mathrm{T}$
    - `eta`: photon $\eta$ (no systematics)
    - `phi`: photon $\phi$ (no systematics)


### [makePhotonWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/PhotonAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different photon definitions.

`workingPoint`
:   the ID and isolation WPs to use. Pass them in the format `quality.isolation`. Supported ID WPs: `Tight`, `Loose`. Supported isolation WPs: `FixedCutLoose`, `FixedCutTight`, `TightCaloOnly`, `NonIso`.

`recomputeIsEM`
:   whether to rerun the cut-based selection. The default is `False`, i.e. to use derivation flags.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the photon passes the ID and isolation cuts
    - `id_effSF`: the per-photon ID SF
    - `isol_effSF`: the per-photon isolation SF

## Config blocks

### [PhotonCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/PhotonAnalysisConfig.py)

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all photons.

`crackVeto`
:   whether to perform LAr crack veto, i.e. remove photons within $1.37<\vert\eta\vert<1.52$. The default is `False`.

`enableCleaning`
:   whether to enable photon cleaning (`DFCommonPhotonsCleaning`). The default is `True`.

`cleaningAllowLate`
:   whether to ignore timing information in cleaning (`DFCommonPhotonsCleaningNoTime`). The default is `False`.

`recomputeIsEM`
:   whether to recompute the photon shower shape fudge corrections (sets up an instance of [`CP::PhotonShowerShapeFudgeAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/PhotonShowerShapeFudgeAlg.cxx)). The default is `False`, i.e. to use derivation variables.

`ptSelectionOutput`
:  whether or not to apply the default $p_\mathrm{T} > 10$ GeV cut to calibrated photons. The default is `False`.

`recalibratePhyslite`
:   whether to run the [`CP::EgammaCalibrationAndSmearingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaCalibrationAndSmearingAlg.cxx) on PHYSLITE derivations. The default is `True`.

!!! success "Registers the following variables:"
    - `pt`: photon $p_\mathrm{T}$
    - `eta`: photon $\eta$ (no systematics)
    - `phi`: photon $\phi$ (no systematics)

### [PhotonWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/PhotonAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Useful here to distinguish between different photon definitions.

`qualityWP`
:   the ID WP (string) to use. Supported ID WPs: `Tight`, `Loose`.

`isolationWP`
:   the ID WP (string) to use. Supported isolation WPs: `FixedCutLoose`, `FixedCutTight`, `TightCaloOnly`, `NonIso`.

`recomputeIsEM`
:   whether to rerun the cut-based selection. The default is `False`, i.e. to use derivation flags.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the photon passes the ID and isolation cuts
    - `id_effSF`: the per-photon ID SF
    - `isol_effSF`: the per-photon isolation SF