*The FAQ will be filled progressively as user questions come in!*

## General

??? question "Where can I ask questions about the code?"
    Check out the relevant [contact points](/#get-in-touch).

??? question "Who came up with the name 'TopCPToolkit'?"
    Our good friend ChatGPT :upside_down:. And DALL-E is responsible for the avatar of the project on GitLab.


## Warning messages

??? question "How do I fix 'The trigger you are looking for, year and mc are not consistent'?"
    If you see the following warning message repeatedly printed
    ```
    ToolSvc.MuonTrigEff      WARNING Could not find what you are looking for in the efficiency map. The trigger you are looking for, year and mc are not consistent, or the trigger is unavailable in this data period. Returning efficiency = 0.
    ```
    then it is likely that your muon trigger settings are wrong.
    One possible reason is a mismatch between Run 2 and Run 3 recommendations, i.e. you could be using an un-supported muon ID WP.
    See [MuonCP docs](https://atlas-mcp.docs.cern.ch/guidelines/release22/index.html#wps-for-run3).

??? question "How do I enable debugging printouts?"
    All algorithms and tools inherit the `OutputLevel` property, which you can set to 0 (info), 1 (verbose) or 2 (debug). See also [`MsgLevel`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Control/AthToolSupport/AsgMessaging/Root/MsgLevel.cxx).

    For an algorithm config in python, you can do something like
    ```python
    myAlgo = config.createAlgorithm( 'CP::SomethingAlg', 'someName' )
    myAlgo.OutputLevel = 2 # sets to DEBUG
    ```
    and `myAlgo` will printout messages wrapped with `ATH_MSG_DEBUG`. Any tool declared by `CP::SomethingAlg` can inherit the current message level (and therefore be driven entirely in python), by setting the corresponding property (in the C++ code):
    ```cpp
        ATH_CHECK( tool->setProperty("OutputLevel", msg().level()) );
    ```
    (or equivalently for our purposes, `ANA_CHECK`).


## Error messages

??? question "I get a crash on 'Exactly two leptons are required to check whether the event is OS or SS!'"
    This comes from your [event selection config](/settings/eventselection/#available-keywords).
    As the error message suggests, you are trying to use either the `OS` or `SS` keywords in an event selection that is not enforcing the presence of exactly two electrons or muons.
    Enforce it, and the error will go away.

??? question "I get a crash on 'Failed to retrieve NSW hits!'"
    It looks something like
    ```
    MuonSelectionAlg_loose...FATAL   /build1/atnight/localbuilds/nightlies/AnalysisBase/main/athena/PhysicsAnalysis/MuonID/MuonSelectorTools/Root/MuonSelectionTool.cxx:1390 (void CP::MuonSelectionTool::fillSummary(const Muon&, CP::MuonSelectionTool::hitSummary&) const): /build1/atnight/localbuilds/nightlies/AnalysisBase/main/athena/PhysicsAnalysis/MuonID/MuonSelectorTools/Root/MuonSelectionTool.cxx:1390 Failed to retrieve NSW hits!! If you're using DxAODs (with smart slimming for muons), you should use p-tags >= p5834. OR set ExcludeNSWFromPrecisionLayers to True before crashing if you want to technically be able to run on old DAODs, noting that this is allowed only for testing purposes

    ```
    As suggested, please update your Run 3 sample by choosing a more recent p-tag, or edit the `MuonSelectionTool` config.


## Derivation formats

??? question "Which derivation formats are currently supported?"
    We support PHYS and PHYSLITE. If you would like to use this framework for CP-specific derivation formats, or have observed a breakage in a supported format, please [open an issue](/contributing/).

??? question "Which p-tags are supported?"
    We always recommend using the [latest available p-tags](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/FullListOfPtagsAndPatternsR22).

??? question "How can I check the metadata present in my sample?"
    After setting up an AnalysisBase release, you can run
    ```
    meta-reader -m peeker --hideContentList --hideTrigger <file>
    ```
    on a given DxAOD file to printout the metadata that is available to TopCPToolkit.

## Unexpected output

??? question "No events pass the GRL selection in this MC sample!"
    This is because your MC sample is being treated as data. It has been observed on a few MC samples that some of the metadata is wrongly written, e.g. the `SimFlavour` field is missing in p5631 and the code is misled into defaulting to data.


## Analysis use-cases

??? question "I've been asked to run bootstraps on data/MC. What are those? Can I use TopCPToolkit to do it?"
    "Bootstrapping" means reweighting your dataset (whether actual data or MC simulations) so as to provide _replicas_ that, as an _ensemble_, describe the expected statistical fluctuations. Essentially, for each event a series of $k$ random numbers are generated following a Poisson distribution with central value 1. The standard deviation of these $k$ replicas then represents the statistical uncertainty. Moreover, by making sure that each event leads to a unique series of random numbers, multiple analyses with overlapping event selections can determine the overlap, as well as the statistical correlations needed for a combination.

    This is the recommendation of the ATLAS Statistical Forum for combinations and analysis preservation (you are requested to store the bootstrapped data to HEPdata), as detailed in [ATL-PHYS-PUB-2021-011](https://cds.cern.ch/record/2759945/files/ATL-PHYS-PUB-2021-011.pdf). A dedicated algorithm was developed with TopCPToolkit, see [`makeBootstrapGeneratorConfig`](/settings/others/#makebootstrapgeneratorconfig).