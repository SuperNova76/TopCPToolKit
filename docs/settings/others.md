## Make-methods

### [makeCommonServicesConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

_Returns an instance of [`CommonServicesConfig`](/settings/others/#commonservicesconfig), see the available options below._

### [makeEventCleaningConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/EventCleaningConfig.py)

`seq`
:   the config sequence.

`runPrimaryVertexSelection`
:   whether to run primary vertex selection. The default is `True`.

`runEventCleaning`
:   whether to run event cleaning (sets up an instance of [`CP::EventFlagSelectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/Root/EventFlagSelectionAlg.cxx)). The default is `False`.

`userGRLFiles`
:   a list of GRL files (list of strings) to select data from. The default is `[]` (empty list).

### [makeGeneratorAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

`saveCutBookkeepers`
:   whether to save the cut bookkeepers information into the output file. The default is `False`.

`runNumber`
:   the MC runNumber.

`cutBookkeepersSystematics`
:   whether to also save the cut bookkeepers systematics. The default is `False`.

!!! success "Registers the following variables:"
    - `generatorWeight`: the event-level PMG generator weight

### [makePileupReweightingConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`seq`
:   the config sequence.

`campaign`
:   the MC campaign for the PRW auto-configuration.

`files`
:   the input files being processed (list of strings). Alternative to auto-configuration.

`useDefaultConfig`
:   whether to use the central PRW files.

`userLumicalFiles`
:   user-provided lumicalc files (list of strings). Alternative to auto-configuration.

`userPileupConfigs`
:   user-provided PRW files. Alternative to auto-configuration.

### [makeBootstrapGeneratorConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/BootstrapGeneratorConfig.py)

`seq`
:   the config sequence.

`nReplicas`
:   the number (int) of bootstrap replicas to generate. The default is 1000.

`decoration`
:   the name of the output vector branch containing the bootstrapped weights. The default is `bootstrapWeights`.

`runOnMC`
:   toggle to force running on MC samples. The default is `False`, i.e. run only on data.

## Config blocks

### [CommonServicesConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`runSystematics`
:   whether to turn on the computation of systematic variations. The default is to run them on MC.

`filterSystematics`
:   a regexp string against which the systematics names will be matched. Only positive matches are retained and used in the evaluation of the various algorithms.

!!! tip
    See the [tutorial](/running_local/#filtering-systematics) on how to use the systematics filter.

### [EventCleaningBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/EventCleaningConfig.py)

`runPrimaryVertexSelection`
:   whether to run primary vertex selection. The default is `True`.

`runEventCleaning`
:   whether to run event cleaning (sets up an instance of [`CP::EventFlagSelectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/Root/EventFlagSelectionAlg.cxx)). The default is `False`.

`userGRLFiles`
:   a list of GRL files (list of strings) to select data from. The default is `[]` (empty list).

`minTracksPerVertex`
:   minimum number (integer) of tracks per vertex. The default is 2.

`selectionFlags`
:   flags (list of strings) to use for jet cleaning. The default is `['DFCommonJets_eventClean_LooseBad']`.

`invertFlags`
:   list of booleans determining whether to invert the cut of the above `selectionFlags`. The default is `[0]`.

!!! warning
    In AnalysisBase, vectors of bools cannot be handled properly. Instead, use 0/1 values.

### [GeneratorAnalysisBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`saveCutBookkeepers`
:   whether to save the cut bookkeepers information into the output file. The default is `False`.

`runNumber`
:   the MC runNumber.

`cutBookkeepersSystematics`
:   whether to also save the cut bookkeepers systematics. The default is `False`.

!!! success "Registers the following variables:"
    - `generatorWeight`: the event-level PMG generator weight

### [PileupReweightingBlock](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

`campaign`
:   the MC campaign for the PRW auto-configuration.

`files`
:   the input files being processed (list of strings). Alternative to auto-configuration.

`useDefaultConfig`
:   whether to use the central PRW files.

`userLumicalFiles`
:   user-provided lumicalc files (list of strings). Alternative to auto-configuration.

`userPileupConfigs`
:   user-provided PRW files. Alternative to auto-configuration.

### [BootstrapGeneratorConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/BootstrapGeneratorConfig.py)

`nReplicas`
:   the number (int) of bootstrap replicas to generate. The default is 1000.

`decoration`
:   the name of the output vector branch containing the bootstrapped weights. The default is `bootstrapWeights`.

`runOnMC`
:   toggle to force running on MC samples. The default is `False`, i.e. run only on data.

## TopCPToolkit modules

### [metaConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/metaConfig.py)

Loading this module enables the following methods to access the metadata:

`get_data_type( FileMetaData )`
:   returns the data type as a string, one of `'mc'`, `'afii'` or `'data'`.

`get_campaign( FileMetaData )`
:   returns the MC campaign as a `Campaigns.Utils.Campaign` object.

`get_data_year( FileMetaData )`
:   returns the year of data-taking based on runNumber reported from FileMetaData.

`isRun3( FileMetaData )`
:   returns `True` if the input MC campaign belongs to Run 3.

`get_LHCgeometry( FileMetaData )`
:   returns the LHC Run information as a `AthenaConfiguration.Enums.LHCPeriod` object.

`get_grl( FileMetaData )`
:   returns the list of GRL files (list of strings) corresponding to the year of data taking (determined from runNumber).

`get_run_number( FileMetaData )`
:   returns the runNumber of data sample or the per-sub-campaign constant runNumber for MC (e.g. 284500 for MC20a).

`get_mc_channel_number( FileMetaData )`
:   returns the MC channelNumber.

### [commonAlgoConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/commonAlgoConfig.py)

This module contains the master sequencing functions `makeRecoSequence` / `makeTruthSequence` / `makeParticleLevelSequence`, as [explained earlier](/analysis#analysis-modules).
Loading the module also enables the following methods to easily set up very common algorithms:

`add_event_cleaning`
:   wraps around [`makeEventCleaningConfig`](#makeEventCleaningConfig), allowing to configure `runEventCleaning`. Automates the GRL settings

`add_mc_weights`
:   wraps around [`makeGeneratorAnalysisConfig`](#makeGeneratorAnalysisConfig), allowing to retrieve the correct output branches. Automates the MC runNumber retrieval.

`add_PRW`
:   wraps around [`makePileupReweightingConfig`](#makePileupReweightingConfig), allowing to retrieve the correct output branches. Automates the PRW settings. 

!!! note
    The PRW tool setup is automatically skipped when we detect data instead of MC samples.
