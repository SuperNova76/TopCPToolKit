## [OutputAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/OutputAnalysisConfig.py)

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`vars`
:   a list of mappings (list of strings) between containers and decorations to output branches. The default is `[]` (empty list).

!!! tip
    Since variables attached to `EventInfo` cannot be added automatically from the config blocks at the moment, you need to add all of these to the output manually through `vars`. This is also the case for any variable not attached with `config.addOutputVariable`.

`metVars`
:   a list of mappings (list of strings) between containers and decorations to output branches. Specficially for MET variables, where only the final MET term is retained. The default is `[]` (empty list).

`containers`
:   a dictionary mapping prefixes (key) to container names (values) to be used when saving to the output tree. Branches are then of the form `prefix_decoration`.

`treeName`
:   name of the output TTree to save. The default is `analysis`.

`metTermName`
:   the name (string) of the MET term to save, turning the MET container into a single object. The default is `'Final'`.

!!! tip
    For a particle-level truth analysis, you likely want to recover `'NonInt'` instead. See [MET_Truth](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/Run2xAODMissingET#MET_Truth).