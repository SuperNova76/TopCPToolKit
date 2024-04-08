<!---
## Make-methods

### [makeElectronCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)

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

`forceFullSimConfig`
:   whether to force the tool to use the configuration meant for full simulation samples. Only for testing purposes. The default is `False`.

!!! success "Registers the following variables:"
    - `pt`: electron $p_\mathrm{T}$
    - `eta`: electron $\eta$ (no systematics)
    - `phi`: electron $\phi$ (no systematics)
    - `charge`: electron charge (no systematics)

### [makeElectronWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`selectionName`
:   the name of the electron selection to define (e.g. `tight` or `loose`).

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as `selectionName` is used internally.

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

`forceFullSimConfig`
:   whether to force the tool to use the configuration meant for full simulation samples. Only for testing purposes. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the electron passes the ID and isolation cuts
    - `reco_effSF`: the per-electron reconstruction SF
    - `id_effSF`: the per-electron ID SF
    - `isol_effSF`: the per-electron isolation SF
--->

## Config blocks

### [ElectronCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)
Name in YAML: **Electrons**

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all electrons.

`crackVeto`
:   whether to perform LAr crack veto based on the cluster $\eta$, i.e. remove electrons within $1.37<\vert\eta\vert<1.52$. The default is `False`.

`ptSelectionOutput`
:   whether or not to apply a minimum $p_\mathrm{T}$ cut to calibrated electrons. The default is `False`.

`minPt`
:   the minimum $p_\mathrm{T}$ cut to apply to calibrated electrons. The default is 4.5 GeV.

`isolationCorrection`
:   whether or not to perform isolation corrections (leakage corrections), i.e. set up an instance of [`CP::EgammaIsolationCorrectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaIsolationCorrectionAlg.cxx).

`trackSelection`
:   whether or not to set up an instance of [`CP::AsgLeptonTrackSelectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/Root/AsgLeptonTrackSelectionAlg.cxx), with the recommended $d_0$ and $z_0\sin\theta$ cuts. The default is `True`.

`recalibratePhyslite`
:   whether to run the [`CP::EgammaCalibrationAndSmearingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaCalibrationAndSmearingAlg.cxx) on PHYSLITE derivations. The default is `True`.

`forceFullSimConfig`
:   whether to force the tool to use the configuration meant for full simulation samples. Only for testing purposes. The default is `False`.

!!! success "Registers the following variables:"
    - `pt`: electron $p_\mathrm{T}$
    - `eta`: electron $\eta$ (no systematics)
    - `phi`: electron $\phi$ (no systematics)
    - `charge`: electron charge (no systematics)

### [ElectronWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py)
Name in YAML: **Electrons.WorkingPoint**

`containerName`
:   the name of the input container.

`selectionName`
:   the name of the electron selection to define (e.g. `tight` or `loose`).

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as `selectionName` is used internally.

`likelihoodWP`
:   the ID WP (string) to use. Supported ID WPs: `TightLH`, `MediumLH`, `LooseBLayerLH`. 

`isolationWP`
:   the isolation WP (string) to use. Supported isolation WPs: `HighPtCaloOnly`, `Loose_VarRad`, `Tight_VarRad`, `TightTrackOnly_VarRad`, `TightTrackOnly_FixedRad`, `NonIso`.

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

`doFSRSelection`
:   whether to accept additional electrons close to muons for the purpose of FSR corrections to these muons. Expert feature requested by the H4l analysis running on PHYSLITE. The default is `False`.

`forceFullSimConfig`
:   whether to force the tool to use the configuration meant for full simulation samples. Only for testing purposes. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the electron passes the ID and isolation cuts
    - `reco_effSF`: the per-electron reconstruction SF
    - `id_effSF`: the per-electron ID SF
    - `isol_effSF`: the per-electron isolation SF