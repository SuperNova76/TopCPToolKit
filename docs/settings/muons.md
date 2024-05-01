<!---
## Make-methods

### [makeMuonCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/MuonAnalysisAlgorithms/python/MuonAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all muons.

`ptSelectionOutput`
:   $p_\mathrm{T}$ cut to apply to calibrated muons, in MeV. The default is 3.0 GeV.

!!! success "Registers the following variables:"
    - `pt`: muon $p_\mathrm{T}$
    - `eta`: muon $\eta$ (no systematics)
    - `phi`: muon $\phi$ (no systematics)
    - `charge`: muon charge (no systematics)

### [makeMuonWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/MuonAnalysisAlgorithms/python/MuonAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`selectionName`
:   the name of the muon selection to define (e.g. `tight` or `loose`).

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as `selectionName` is used internally.

`workingPoint`
:   the ID and isolation WPs to use. Pass them in the format `quality.isolation`. Supported ID WPs: `Tight`, `Medium`, `Loose`, `LowPt`, `HighPt`. Supported isolation WPs: `PflowLoose_VarRad`, `PflowTight_VarRad`, `Loose_VarRad`, `Tight_VarRad`, `NonIso`.

`qualitySelectionOutput`
:   whether to retain only muons satisfying the quality requirements (bad muon veto). The default is `True`.

`systematicBreakdown`
:   enables the full breakdown of efficiency SF systematics (1 NP per uncertainty source, instead of 1 NP in total). The default is `False`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

`onlyRecoEffSF`
:   same as `noEffSF`, but retains the ID scale factor. Experimental! only useful for CI tests. The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the muon passes the quality and isolation cuts
    - `reco_effSF`: the per-muon reconstruction SF
    - `BadMuonVeto_effSF`: the dedicated "bad muon veto" SF, only with quality `HighPt`
    - `isol_effSF`: the per-muon isolation SF
    - `TTVA_effSF`: the per-muon track-to-vertex-association SF
--->

## Config blocks

### [MuonCalibrationConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/MuonAnalysisAlgorithms/python/MuonAnalysisConfig.py)
Name in YAML: **Muons**

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since the calibration is common to all muons.

`ptSelectionOutput`
:   $p_\mathrm{T}$ cut to apply to calibrated muons, in MeV. The default is 3.0 GeV.

`trackSelection`
:   whether or not to set up an instance of [`CP::AsgLeptonTrackSelectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/Root/AsgLeptonTrackSelectionAlg.cxx), with the recommended $d_0$ and $z_0\sin\theta$ cuts. The default is `True`.

`recalibratePhyslite`
:   whether to run the [`CP::EgammaCalibrationAndSmearingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaCalibrationAndSmearingAlg.cxx) on PHYSLITE derivations. The default is `True`.

`maxEta`
:   maximum muon $\vert\eta\vert$ (float). The default is 2.7.

`excludeNSWFromPrecisionLayers`
:   whether to ignore NSW hits. Expert option, for testing purposes or to fix a crash with older derivations (p-tag < p5834). The default is `False`.

!!! success "Registers the following variables:"
    - `pt`: muon $p_\mathrm{T}$
    - `eta`: muon $\eta$ (no systematics)
    - `phi`: muon $\phi$ (no systematics)
    - `charge`: muon charge (no systematics)

### [MuonWorkingPointConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/MuonAnalysisAlgorithms/python/MuonAnalysisConfig.py)
Name in YAML: **Muons.WorkingPoint**

`containerName`
:   the name of the input container.

`selectionName`
:   the name of the muon selection to define (e.g. `tight` or `loose`).

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here as `selectionName` is used internally.

`quality`
:   the ID WP (string) to use. Supported ID WPs: `Tight`, `Medium`, `Loose`, `LowPt`, `HighPt`.

`isolation`
:   the isolation WP (string) to use. Supported isolation WPs: `PflowLoose_VarRad`, `PflowTight_VarRad`, `Loose_VarRad`, `Tight_VarRad`, `NonIso`.

`qualitySelectionOutput`
:   whether to retain only muons satisfying the quality requirements (bad muon veto). The default is `True`.

`systematicBreakdown`
:   enables the full breakdown of efficiency SF systematics (1 NP per uncertainty source, instead of 1 NP in total). The default is `False`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. The default is `False`.

`onlyRecoEffSF`
:   same as `noEffSF`, but retains the ID scale factor. Experimental! only useful for CI tests. The default is `False`.

`excludeNSWFromPrecisionLayers`
:   whether to ignore NSW hits. Expert option, for testing purposes or to fix a crash with older derivations (p-tag < p5834). The default is `False`.

!!! success "Registers the following variables:"
    - `select`: whether the muon passes the quality and isolation cuts
    - `reco_effSF`: the per-muon reconstruction SF
    - `BadMuonVeto_effSF`: the dedicated "bad muon veto" SF, only with quality `HighPt`
    - `isol_effSF`: the per-muon isolation SF
    - `TTVA_effSF`: the per-muon track-to-vertex-association SF