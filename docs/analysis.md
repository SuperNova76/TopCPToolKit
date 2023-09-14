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

- create `AnaAlgSequence` and `ConfigSequence` objects, a (blank) chain of algorithms to be executed;
- initialise the [`CommonServicesConfig`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py), which
    - checks whether we are running on data: if we are, we do not need to consider systematics or truth information!
    - creates an instance of the `CP::SystematicsSvc`, which will record and handle all the systematics that we need, based on the objects that we deal with;
    - creates an instance of the `CP::SelectionNameSvc`, to handle cutflows;
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

def makeRecoConfiguration(metadata, algSeq, configSeq, debugHistograms, noFilter=False):

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

### Running ML inference

In case one wishes to run ML inference on trained models and store the model predictions to the output ntuple, a config block can be added to the algorithm sequence of your analysis module. One example can be founded here [TopSpaNetConfig.py](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TopSpaNetConfig.py). This config block loads an algorithm `RunSpaNetAlg` defined in [RunSpaNetAlg.h](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/RunSpaNetAlg.h). To run ML inference on custom models, a similar algorithm e.g. `RunCustomNNAlg` need to be added. This algorithm is responsible for:

* applying event and object selections
* computing input tensors for the models from selected objects
* loading models and running inference
* retrieving the model outputs and storing them into ntuple branches.

The model inference is done using [ONNX runtime](https://onnxruntime.ai/) C++ interface. Models trained in any framework are expected to be already converted to the ONNX format. A `top::ONNXWrapper` [class](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/ONNXWrapper.h) is provided that hides most of the ONNX runtime APIs calls behind more convenient interfaces. The user algorithm `RunCustomNNAlg` needs to contain an instance of `top::ONNXWrapper` (or an instance of a class that inherits from `top::ONNXWrapper`) for the purpose of loading models, setting inputs, running inference, and retrieving outputs. Below is a code skeleton that shows an example of using the `top::ONNXWrapper` interface for running ML inference.
```
namespace top {

    class RunCustomNNAlg : public EL::AnaAlgorithm {

        // An ONNXWrapper object
        std::unique_ptr<ONNXWrapper> m_NN;

        // Input handlers
        CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle {
            this, "jets", "", "the jet container to use"
	    };
        CP::SysReadSelectionHandle m_jetSelection {
            this, "jetSelection", "", "the selection on the input jets"
	    };

        ...

        // Output handlers
        CP::SysWriteDecorHandle<float> m_model_pred0 {
            this, "my_model_pred1", "my_model_pred1_%SYS%", "One of my model predictions"
	    };

        ...

        // Systematics
        CP::SysListHandle m_systematicsList {this};

        // Execute
        StatusCode execute_syst(const CP::SystematicSet &sys) {

            ...

            // Retrieve objects from containers and apply selections
            const xAOD::JetContainer *jets = nullptr;
            ANA_CHECK(m_jetsHandle.retrieve(jets, sys));

            ConstDataVector<xAOD::JetContainer> selected_jets(SG::VIEW_ELEMENTS);
            for (const xAOD::Jet *jet : *jets) {
                if (m_jetSelection.getBool(*jet, sys))
                    selected_jets.push_back(jet);
            }

            ...

            // Compute inputs from the selected objects
            std::vector<float> input_vec = compute_inputs_from(selected_jets, ...);

            // Define input shapes
            std::vector<int64_t> input_vec = {LENGTH, WIDTH, ...};

            // Add inputs and convert to tensors via the ONNXWrapper interface
            m_NN -> clearInputs();
            m_NN -> addInputs(input_vec, input_dims);

            // Pick the right model based on eventNumber
            // This is for avoiding evaluating the same events that are used for training. For example, the model trained using events with odd event numbers should be used for inference only on events with even event numbers.
            unsigned imodel = getSessionIndex(eventNumber);

            // run inference
            m_NN -> evaluate(imodel);

            // get model predictions
            float* out_p = m_NN -> getOutputs<float>("my_model_output_name");

            // write output to ntuple
            m_model_pred0 = out_p[0];

        }

    public:

        RunCustomNNAlg(const std::string &name, ISvcLocator *pSvcLocator) {
            // do constructor stuff
        }

        virtual StatusCode initialize() override {

            // initialize inputs
            ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));
            ANA_CHECK(m_jetSelection.initialize(m_systematicsList, m_jetsHandle, SG::AllowEmpty));

            ...

            // initialize outputs
            ANA_CHECK(m_model_pred0.initialize(m_systematicsList, m_eventInfoHandle));

            ...

            // initialize and load models
            m_NN = std::make_unique<ONNXWrapper>("MyFavouriteNN", <filepahts_to_trained_models.onnx>, ...);

            // Other initialization and configuration
            ...

            return StatusCode::SUCCESS;
        }

        virtual StatusCode execute() override {
            for (const auto &sys : m_systematicsList.systematicsVector()) {
                ANA_CHECK(execute_syst(sys));
            }
            return StatusCode::SUCCESS;
        }

        virtual StatusCode finalize() override {
            return StatusCode::SUCCESS;
        }

    };
} // namespace top
```