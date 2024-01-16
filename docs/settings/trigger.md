## Make-methods

### [makeTriggerAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TriggerAnalysisAlgorithms/python/TriggerAnalysisConfig.py)

`seq`
:   the config sequence.

`triggerChainsPerYear`
:   a dictionary with key (string) the year and value (list of strings) the trigger chains. You can also use `||` within a string to enforce an OR of triggers without looking up the individual triggers. Used for both trigger selection and SFs. The default is `{}` (empty dictionary).

`triggerChainsForSelection`
:   a list of trigger chains (list of strings) to be used for trigger selection. Only set it if you need a different setup than for trigger SFs.
The default is `[]` (empty list).

`prescaleLumiCalcFiles`
:   a list of lumical files (list of strings) to calculate trigger prescales. The default is `[]` (empty list).

`noFilter`
:   do not apply an event filter. The default is `False`, i.e. remove events not passing trigger selection and matching.

`electronWorkingPoint`
:   the electron ID and isolation WPs to use. Pass them in the format `likelihood.isolation`.

`muonWorkingPoint`
:   the muon quality and isolation WPs to use. Pass them in the format `quality.isolation`.

    !!! note
        Only the muon quality is really needed. Passing e.g. `Tight.None` is therefore correct.

`photonWorkingPoint`
:   the photon quality and isolation WPs to use. Pass them in the format `quality.isolation`.

    !!! note
        Only the photon isolation is really needed. Passing e.g. `None.TightCaloOnly` is therefore correct.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`.

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`.

`photons`
:   the input photon container, with a possible selection, in the format `container` or `container.selection`.

`configName`
:   name of the block config, typically not needed here. The default is `Trigger`.

`noEffSF`
:   disables the calculation of efficiencies and scale factors. Experimental! only useful to test a new WP for which scale factors are not available. Still performs the global trigger matching (same behaviour as on data). The default is `False`.

!!! success "Registers the following variables:"
    - `trigPassed`: whether a specific trigger is passed
    - `globalTriggerMatch`: whether the event passes trigger matching requirements
    - `globalTriggerEffSF`: the event-level global trigger efficiency SF

## Config blocks

### [TriggerAnalysisBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TriggerAnalysisAlgorithms/python/TriggerAnalysisConfig.py)

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

!!! success "Registers the following variables:"
    - `trigPassed`: whether a specific trigger is passed
    - `globalTriggerMatch`: whether the event passes trigger matching requirements
    - `globalTriggerEffSF`: the event-level global trigger efficiency SF