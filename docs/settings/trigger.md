## Config blocks

### [TriggerAnalysisBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TriggerAnalysisAlgorithms/python/TriggerAnalysisConfig.py)
Name in YAML: **Trigger**

`configName`
:   name of the block config, e.g. `Trigger`.

`triggerChainsPerYear`
:   a dictionary with key (string) the year and value (list of strings) the trigger chains. You can also use `||` within a string to enforce an OR of triggers without looking up the individual triggers. Used for both trigger selection and SFs. The default is `{}` (empty dictionary).

`triggerChainsForSelection`
:   a list of trigger chains (list of strings) to be used for trigger selection. Only set it if you need a different setup than for trigger SFs.
The default is `[]` (empty list).

`prescaleLumiCalcFiles`
:   a list of lumical files (list of strings) to calculate trigger prescales. The default is `[]` (empty list).

`noFilter`
:   do not apply an event filter. The default is `False`, i.e. remove events not passing trigger selection and matching.

`electronID`
:   the electron ID WP (string) to use.

`electronIsol`
:   the electron isolation WP (string) to use.

`muonID`
:   the muon quality WP (string) to use.

`photonIsol`
:   the photon isolation WP (string) to use.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`photons`
:   the input photon container, with a possible selection, in the format `container` or `container.selection`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. Still performs the global trigger matching (same behaviour as on data). The default is `False`.

`noGlobalTriggerEff`
:   disables the global trigger efficiency tool (including matching), which is only suited for electron/muon/photon trigger legs. The default is `False`.

!!! success "Registers the following variables:"
    - `trigPassed`: whether a specific trigger is passed (no systematics)
    - `globalTriggerMatch`: whether the event passes trigger matching requirements
    - `globalTriggerEffSF`: the event-level global trigger efficiency SF