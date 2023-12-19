## Make-methods

### [makePtEtaSelectionConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since we tend apply a single set of $p_\mathrm{T}$ and $\eta$ cuts to a given type of object.

`minPt`
:   minimum $p_\mathrm{T}$ value to cut on, in MeV. No default value.

`maxEta`
:   maximum $\vert\eta\vert$ value to cut on. No default value.

`useClusterEta`
:   whether to use the cluster $\eta$ (`etaBE(2)`) instead of the object $\eta$ (for electrons and photons). The default is `False`.

`selectionDecoration`
:   the name of the decoration to set.

`selectionName`
:   the name of the selection to append this to. The default is `''` (empty string), meaning that the cuts are applied to every object within the container. Specifying a name (e.g. `loose`) applies the cut only to those object who also pass that selection.

### [makeOutputThinningConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`selection`
:   the name of an optional selection decoration to use.

`selectionName`
:   the name of the selection to append this to. The default is `''` (empty string), meaning that the cuts are applied to every object within the container. Specifying a name (e.g. `loose`) applies the cut only to those object who also pass that selection.

`outputName`
:   an optional name for the output container.

`configName`
:   name of the block config, typically not needed here. The default is `Thinning`.

### [makeObjectCutFlowConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`selectionName`
:   the name of the selection to perform the cutflow for. The default is `''` (empty string), meaning that the cutflow is performed for every object within the container. Specifying a name (e.g. `loose`) generates the cutflow only for those object that also pass that selection.

## Config blocks

### [PtEtaSelectionBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here since we tend apply a single set of $p_\mathrm{T}$ and $\eta$ cuts to a given type of object.

`minPt`
:   minimum $p_\mathrm{T}$ value to cut on, in MeV. No default value.

`maxEta`
:   maximum $\vert\eta\vert$ value to cut on. No default value.

`useClusterEta`
:   whether to use the cluster $\eta$ (`etaBE(2)`) instead of the object $\eta$ (for electrons and photons). The default is `False`.

`selectionDecoration`
:   the name of the decoration to set.

`selectionName`
:   the name of the selection to append this to. The default is `''` (empty string), meaning that the cuts are applied to every object within the container. Specifying a name (e.g. `loose`) applies the cut only to those object who also pass that selection.

### [OutputThinningBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`selection`
:   the name of an optional selection decoration to use.

`selectionName`
:   the name of the selection to append this to. The default is `''` (empty string), meaning that the cuts are applied to every object within the container. Specifying a name (e.g. `loose`) applies the cut only to those object who also pass that selection.

`outputName`
:   an optional name for the output container.

`configName`
:   name of the block config, e.g. `Thinning`.

### [ObjectCutFlowBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`containerName`
:   the name of the input container.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`selectionName`
:   the name of the selection to perform the cutflow for. The default is `''` (empty string), meaning that the cutflow is performed for every object within the container. Specifying a name (e.g. `loose`) generates the cutflow only for those object that also pass that selection.