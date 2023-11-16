## Make-methods

!!! warning
    No such method exist yet for event reconstruction algorithms!

## Config blocks

### [DiTauMassConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/DiTauMassConfig.py)

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`taus`
:   the input tau-jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`met`
:   the input MET container. The default is `''` (empty string).

`eventSelection`
:   optional event filter to run on. The default is `''` (empty string), i.e. all events.

`saveExtraVariables`
:   whether to save additional output information from the MMC. The default is `False`.

`floatStopCriterion`
:   whether to activate the floating stopping criterion. The default is `True`.

`calibration`
:   the calibration set (string) to use. The default is `'2019'` (recommended).

`nSigmaMet`
:   the number (int) of sigmas for the MET resolution scan. The default is `-1` (no scan).

`useTailCleanup`
:   whether to activate the tail cleanup feature. The default is ``.

`niterFit2`
:   the number of iterations for each MET scan loop. The default is ``.

`niterFit3`
:   the number of iterations for each Mnu loop. The default is ``.

`useTauProbability`
:   whether to apply tau probability (additional PDF term corresponding to the ratio of the neutrino momentum to the reconstructed tau momentum). The default is ``.

`useMnuProbability`
:   whether to apply $m_\nu$ probability (additional PDF term corresponding to the mass of the neutrino system per tau decay, only applied to leptonic tau decays). The default is ``.

`useDefaultSettings`
:   whether to take all default options from the tool itself. The default is ``.

`useEfficiencyRecovery`
:   whether to enable refitting for failed events, to improve efficiency. The default is ``.

`useMETdphiLL`
:   whether to parameterise the MET resolution using sumET and dphiLL (only for the lep-lep case). The default is ``.

`paramFilePath`
:   path (string) to the ROOT file used with `calibSet` ≥ 2019, containing the PDFs for the likelihood. The default is `'MMC_params_v1_fixed.root'` (recommended).

`nJetsMinPt`
:   minimum jet $p_\mathrm{T}$, in MeV. The default is 30 GeV.

!!! success "Registers the following variables:"
    - `mmc_fit_status`: the returned status of the MMC fit
    - `mmc_maxw_mass`: the mass of the di-tau resonance using the maximum-weight estimator
    - `mmc_mlm_mass`: the mass of the di-tau resonance using the maximum-likelihood estimator
    - `mmc_mlnu3p_mass`: the mass of the di-tau resonance using the best-fit neutrino kinematics

!!! success "Additional variables toggled by `saveExtraVariables`"
    - `mmc_mlnu3p_res_4vect`: four-vector of the di-tau resonance using the best-fit neutrino kinematics
    - `mmc_mlnu3p_nu1_4vect`: four-vector of the leading-$p_\mathrm{T}$ neutrino using the best-fit neutrino kinematics
    - `mmc_mlnu3p_nu2_4vect`: four-vector of the subleading-$p_\mathrm{T}$ neutrino using the best-fit neutrino kinematics
    - `mmc_mlnu3p_tau1_4vect`: four-vector of the leading-$p_\mathrm{T}$ tau-lepton using the best-fit neutrino kinematics
    - `mmc_mlnu3p_tau2_4vect`: four-vector of the subleading-$p_\mathrm{T}$ tau-lepton using the best-fit neutrino kinematics
    - `mmc_maxw_res_4vect`: four-vector of the di-tau resonance using the maximum-weight estimator
    - `mmc_maxw_nu1_4vect`: four-vector of the leading-$p_\mathrm{T}$ neutrino using the maximum-weight estimator
    - `mmc_maxw_nu2_4vect`: four-vector of the subleading-$p_\mathrm{T}$ neutrino using the maximum-weight estimator
    - `mmc_maxw_tau1_4vect`: four-vector of the leading-$p_\mathrm{T}$ tau-lepton using the maximum-weight estimator
    - `mmc_maxw_tau2_4vect`: four-vector of the subleading-$p_\mathrm{T}$ tau-lepton using the maximum-weight estimator

!!! abstract "Documentation"
    Further notes on the tool are available at [DiTauMassTools](https://gitlab.cern.ch/atlas/athena/-/tree/main/PhysicsAnalysis/TauID/DiTauMassTools). Usage in the ATLAS Run 2 $H\to\tau\tau$ analysis is documented in Section 10 of [ATL-COM-PHYS-2020-721](https://cds.cern.ch/record/2741326). A detailed description of the Missing Mass Calculator (MMC) method and its alternatives is given in Chapter 4 of [Michael Hübner's PhD thesis](https://bonndoc.ulb.uni-bonn.de/xmlui/bitstream/handle/20.500.11811/9734/6567.pdf).

!!! note
    The MMC method can be applied to had-had, had-lep and lep-lep di-tau decays. Based on the input collections given to the algorithm, the following priority ordering is made internally:

    1. $\tau$-had + $\tau$-had
    1. $\tau$-had + $\mu$
    1. $\tau$-had + e
    1. e + $\mu$
    1. $\mu$ + $\mu$
    1. e + e

    This means that if your event has 2 hadronic tau-jets and 1 electron, the MMC fit will be run under the assumption of a had-had event. To force the MMC fit to consider the 1 electron in a had-lep topology, you'd need to edit the C++ code. Alternatively, if you have determined that some objects should not be used as inputs (e.g. hadronic tau-jet already assigned to top reconstruction, pair of leptons assigned to a Z boson), you should decorate these objects with a flag and use the relevant `container.selection` options of the algorithm. In that way, the MMC fit will only be run on the "left-over" objects.

!!! warning
    The MMC method assumes that the MET in a given event originates mostly from the neutrinos associated to the decay of the di-tau system. If your topology has additional sources of MET (e.g. $t\bar{t}H(\to\tau\tau)$, $W(\to\ell\nu)H(\to\tau\tau)$), the MMC method is not recommended and will give nonsensical answers. See e.g. the ATLAS Run 2 search for BSM $VH(\to\tau\tau)$ in [ATL-COM-PHYS-2022-022](https://cds.cern.ch/record/2799543) where the MMC method is combined with alternatives. Additional neutrinos from the decay of B-hadrons typically do not lead to significant enough MET to be a problem, i.e. $t\bar{t}(\to\text{jets})H(\to\tau\tau)$ should be safe.

### [KLFitterConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/KLFitterConfig.py)

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`met`
:   the input MET container. The default is `''` (empty string).

`likelihoodType`
:   KLFitter likelihood, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`leptonType`
:   type of lepton to use (only relevant to certain likelihood types), if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`jetSelectionMode`
:   jet selection mode to use, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`btaggingMethod`
:   strategy to handle b-jets, if only one is needed. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopCPToolkit/KLFitterEnums.h). The default is `''` (empty string).

`bTagCDIFile`
:   CDI file to pass to the b-tagging efficiency tool. The default is `xAODBTaggingEfficiency/13TeV/2022-22-13TeV-MC20-CDI-2022-07-28_v1.root`.

`btagger`
:   b-tagging algorithm to use, if only one is needed. The default is `DL1dv00`.

`btagWP`
:   b-tagging efficiency WP to use, if only one is needed. The default is `FixedCutBEff_77`.

`selectionRegionsConfig`
:   string of the form `selectionName: sel1, optionA: opA, optionB: opB; selectionName: sel2, ...` where options can be `likelihoodType`, `leptonType`, `jetSelectionMode`, `btaggingMethod`, `btagger` or `btagWP`. The default is `''` (empty string).

`saveAllPermutations`
:   whether to save all permutations, or just the best one. The default is `False` (only save the best one).

!!! success "Registers the following variables:"
    - `eventProbability`: the event probability
    - `logLikelihood`: the log of the likelihood

!!! abstract "Documentation"
    The source code and documentation for KLFitter are available from [github](https://github.com/KLFitter/KLFitter).

### [TopSpaNetConfig](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/python/TopSpaNetConfig.py)

`btagger`
:   b-tagging algorithm to use, if only one is needed. The default is `DL1dv01`.

`electrons`
:   the input electron container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`muons`
:   the input muon container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`jets`
:   the input jet container, with a possible selection, in the format `container` or `container.selection`. The default is `''` (empty string).

`met`
:   the input MET container. The default is `''` (empty string).

`eventSelection`
:   optional event filter to run on. The default is `''` (empty string), i.e. all events.

`topology`
:   the SPA-Net model to run. See [possible values](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/TopSpaNet/SpaNetEnums.h).

!!! success "Registers up to 4 types of topology-dependent variables:"
    - `index`: index within a given container of the relevant particle candidate
    - `assignment`: quality of the system reconstruction
    - `detection`: likelihood of the event containing all necessary decay products to reconstruct the system
    - `reg`: regressed kinematic properties

!!! note "Documentation"
    See [arXiv:2106.03898](https://arxiv.org/abs/2106.03898) and [arXiv:2309.01886](https://arxiv.org/abs/2309.01886).