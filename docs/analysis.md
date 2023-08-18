To understand how to write a custom analysis configuration, it's instructive to first take a look at [`runTop_el.py`](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/share/runTop_el.py).
There, we find calls such as
```python
from TopCPToolkit.commonAlgoConfig import makeRecoSequence
algSeq = makeRecoSequence(args.analysis, metadata,
                          noSystematics=args.no_systematics,
                          debugHistograms=not args.no_debug_histograms,
                          noFilter=args.no_filter)
```
and similarly to `makeTruthSequence` and `makeParticleLevelSequence`.

These methods are defined in [commonAlgoConfig.py](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/commonAlgoConfig.py), and you can see that they perform the following actions:

- create an `AnaAlgSequence` object, a (blank) chain of algorithms to be executed;
- check whether we are running on data: if we are, we do not need to consider systematics or truth information!
- create an instance of the `CP::SystematicsSvc`, which will record and handle all the systematics that we need, based on the objects that we deal with;
- set up the very first algorithm, the `CP::VertexSelectionAlg`, to retain only events with a reconstructed primary vertex;
- **load and configure the requested analysis algorithms**;
- add a final algorithm, the `CP::SysListDumperAlg`, helpful to monitor which systematics were collected.

It's the statement in bold that is of interest to us: we need to define an *analysis module*, and equip it with the necessary `makeRecoConfiguration` (equivalently, `makeTruthConfiguration` or `makeParticleLevelConfiguration`) method.

## Analysis modules

Analysis modules are python files whose role is to define a `makeRecoConfiguration` method that can be overloaded by [commonAlgoConfig.py](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/commonAlgoConfig.py).
A good place to start, is the [example analysis module](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TtbarCPalgoConfigBlocksAnalysis.py).
Schematically, it looks like this:
```python
from AnalysisAlgorithmsConfig.ConfigSequence import ConfigSequence
from AnalysisAlgorithmsConfig.ConfigAccumulator import ConfigAccumulator
from TopCPToolkit import metaConfig, commonAlgoConfig

def makeRecoConfiguration(metadata, algSeq, debugHistograms, noFilter=False):
    configSeq = ConfigSequence()

    # ... everything you need goes here ...

    configAccumulator = ConfigAccumulator(dataType, algSeq)
    configSeq.fullConfigure(configAccumulator)

    return
```

### Understanding the skeleton

The first import allow us to define a `ConfigSequence` object, which we will pass to all subsequent config blocks we require.
For instance, when we we request to calibrate a new electron collection "AnaElectrons":
```python
makeElectronCalibrationConfig(configSeq, 'AnaElectrons')
```
This particular config block is defined in [ElectronAnalyisConfig.py](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/python/ElectronAnalysisConfig.py), and sets up the various algorithms necessary to reconstructing and calibrating electrons: a $p_\mathrm{T}$/$\eta$ selection, a track selection, an Egamma quality cut, the `ElectronCalibrationAndSmearingAlg` itself, etc.

The second import creates an instance of `ConfigAccumulator`, which (as the name suggests) will read the chain of config blocks and accumulate it into a sequence of algorithms.
It communicates all the relevant metadata between blocks during the configuration, and keeps track of all the input and output containers needed at each stage.

The two imports from TopCPToolkit are generally quite useful: `metaConfig` allows easy access to metadata (such as data type or MC campaign), while `commonAlgoConfig` contains standard calls for event cleaning, PMG MC weights or automatic PRW settings.

### Creating the output ntuple

A very special config block is set up at the very end of our sequence: the [OutputAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/OutputAnalysisConfig.py).
It is responsible for creating the tree we will save, with all the branches we've declared in our successive config blocks, and eventually for filling said tree.
It is set up as follows:
```python
from AsgAnalysisAlgorithms.OutputAnalysisConfig import OutputAnalysisConfig
cfg = OutputAnalysisConfig('reco')
cfg.setOptionValue('treeName', 'reco')
cfg.setOptionValue('vars', reco_branches)
cfg.setOptionValue('metVars', met_branches)
cfg.setOptionValue('containers', outputContainers)
configSeq.append(cfg)
```

While `treeName` is straightforwardly the desired name of the output tree, some explanations are needed for the three other options.

- `'vars'`: while output branches should be declared within each config block, we may want to add to this collection by passing a list of mappings of the form `'Container.inputname -> outputname'`.
- `'metVars'`: same as above, but specifically for the MET container, which contains different levels of MET. By default, the ["Final" MET term](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/AsgAnalysisAlgorithms/AsgxAODMetNTupleMakerAlg.h) is selected.
- `'containers'`: a dictionary that maps the object containers we want to write out to some prefix used in naming branches. For instance, `{'jet_':'OutJets'}` will result in all the variables we save from the `OutJets` container being saved as `jet_something`.


