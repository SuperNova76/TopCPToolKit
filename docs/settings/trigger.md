## [makeTriggerAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/TriggerAnalysisAlgorithms/python/TriggerAnalysisConfig.py)

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
:   the input electron container.

`muons`
:   the input muon container.

`photons`
:   the input photon container.

`configName`
:   name of the block config, typically not needed here. The default is `Trigger`.

!!! success "Registers the following variables:"
    - `trigPassed`: whether a specific trigger is passed
    - `globalTriggerMatch`: whether the event passes trigger matching requirements
    - `globalTriggerEffSF`: the event-level global trigger efficiency SF

!!! tip
    Since variables attached to `EventInfo` cannot be added automatically from the config blocks at the moment, you need to add all of these to the output manually.