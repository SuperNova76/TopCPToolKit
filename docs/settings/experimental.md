<!---
## Make-methods

!!! warning
    No such method exist for experimental algorithms!
--->

## Config blocks

### [BTagScoresConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/BTagScoresConfig.py)
Name in YAML: **BTaggingScores**

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

### [SVMassAlg](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/SVMassConfig.py)
Name in YAML: **SVMass**

Decorates the output jets with the secondary vertex mass (SVMass).

`containerName`
:   the name of the output container after calibration.

`eventSelection`
:   optional event filter to run on. The default is `''` (empty string), i.e. all events.

!!! success "Registers the following variables:"
    - `SVMass`: the secondary vertex mass of every jet.

### [VGammaORConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/VGammaORConfig.py)
Name in YAML: **VGammaOR**

Adds a new event-level variable `in_vgamma_overlap` using the [VGammaORTool](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/VGammaORTool). The new variable can be used to remove to overlap between V+jets and Vy+jets samples.

`dR_lepton_photon_cuts`
:   list of cuts on dR between lepton and photon.

`photon_pT_cuts`
:   cuts of photon $p_\mathrm{T}$.

!!! success "Registers the following variables:"
    - `in_vgamma_overlap`: can either be 0 or 1 for an event. An event should be kept if it is 0 for V+jets samples or if it is 1 for V$\gamma$+jets samples.

### [IOStatsConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)
Name in YAML: **IOStats**

Print a list of branches that are read when processing input files using the [ReadStats](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Event/xAOD/xAODCore/xAODCore/tools/ReadStats.h) tool. The implementation follows the twiki page [here](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/DerivationFramework#Checking_What_Branches_an_Analys).

`printOption`
:   option to pass the standard ROOT printing function. Can be "Summary", "ByEntries" or "ByBytes". The default is "Summary".

### [ExtraParticleDecorationConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/v2.9.2/source/TopCPToolkit/python/ExtraParticleDecorationConfig.py) :no_entry:

**Deprecated since v2.10.0** ([issue #145](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/145))

!!! warning "User actions required for updating to version 2.10.0 or higher"

    Drop the following lines from YAML configs if applicable:
    ```
    ExtraParticleDecoration:
        - particles: 'AnaElectrons'
        - particles: 'AnaMuons'
        - particles: 'AnaJets
    ```
    The declaration of `ExtraParticleDecoration` under `AddConfigBlocks` also need to be removed.

Name in YAML: **ExtraParticleDecoration**

Allows to add generic particle decorations and save them as output variables.

`particles`
:   the input particle container.

!!! success "Registers the following variables:"
    - `e`: object $E$