## [metaConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/metaConfig.py)

Loading this module enables the following methods to access the metadata:

`get_data_type( FileMetaData )`
:   returns the data type as a string, one of `'mc'`, `'afii'` or `'data'`.

`get_campaign( FileMetaData )`
:   returns the MC campaign as a `Campaigns.Utils.Campaign` object.

`isRun3( Campaigns.Utils.Campaign )`
:   returns `True` if the input MC campaign belongs to Run 3.

`get_LHCgeometry( Campaigns.Utils.Campaign )`
:   returns the LHC Run information as a `AthenaConfiguration.Enums.LHCPeriod` object.

`get_grl( Campaigns.Utils.Campaign )`
:   returns the list of GRL files (list of strings) corresponding to the input MC campaign.

`get_mc_run_number( FileMetaData )`
:   returns the MC runNumber.

`get_mc_channel_number( FileMetaData )`
:   returns the MC channelNumber.

## [commonAlgoConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/commonAlgoConfig.py)

This module contains the master sequencing functions `makeRecoSequence` / `makeTruthSequence` / `makeParticleLevelSequence`, as [explained earlier](/analysis#analysis-modules).
Loading the module also enables the following methods to easily set up very common algorithms:

`add_event_cleaning`
:   wraps around [`makeEventCleaningConfig`](#makeEventCleaningConfig), allowing to configure `runEventCleaning`. Automates the GRL settings

`add_mc_weights`
:   wraps around [`makeGeneratorAnalysisConfig`](#makeGeneratorAnalysisConfig), allowing to retrieve the correct output branches. Automates the MC runNumber retrieval.

`add_PRW`
:   wraps around [`makePileupReweightingConfig`](#makePileupReweightingConfig), allowing to retrieve the correct output branches. Automates the PRW settings.

## [makeEventCleaningConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/EventCleaningConfig.py)

`seq`
:   the config sequence.

`runPrimaryVertexSelection`
:   whether to run primary vertex selection. The default is `True`.

`runEventCleaning`
:   whether to run event cleaning (sets up an instance of [`CP::EventFlagSelectionAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/Root/EventFlagSelectionAlg.cxx)). The default is `False`.

`userGRLFiles`
:   a list of GRL files (list of strings) to select data from. The default is `[]` (empty list).

## [makeGeneratorAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

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

## [makePileupReweightingConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/AsgAnalysisAlgorithms/python/AsgAnalysisConfig.py)

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