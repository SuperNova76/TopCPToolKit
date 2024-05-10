# Changelog

## TopCPToolkit releases

### Upcoming release
- [issue #94](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/94): add algorithm for NuFlows reconstruction
- [issue #125](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/125): Add a tutorial on deploying trained ML models for inference
- [issue #140](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/140): New algorithm for ttbar spin density matrix calculations

### 2.9.0 <small>May 10, 2024</small>
- We run on AB 25.2.10
- [issue #121](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/121): Make a HowToExtendAnalysisTop-like skeleton for TopCPToolkit
- [issue #129](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/129): Expose the option btagIgnoreOutOfValidityRange of BTaggingEfficiencyTool to KLFitterConfig
- [issue #130](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/130): Creating the ExtraPhotonDecorationAlg
- [issue #131](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/131): Document the new friendly systematics categories options
- [issue #133](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/133): Silence harmless warnings from hadd
- [issue #134](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/134): Fix BTagScoresConfig bugs
- [issue #137](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/137): Bugfix for new release 25.2.9
- [issue #138](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/138): Minor improvements to the docs and CI
- [issue #139](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/139): Better failure discovery on the Grid

### 2.8.0 <small>April 22, 2024</small>
- We run on AB 25.2.7
- [issue #93](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/93): prepare a tutorial
- [issue #101](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/101): adapt to the new btagging event-wise SF
- [issue #122](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/122): adding VGammaORTool as a new Algorithm
- [issue #123](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/123): Cmake export compile commands should be enabled by default
- [issue #124](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/124): Pass the bTaggingMethod option in KLFitterConfig to KLFitterAlg
- [issue #126](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/126): Add the option to run with EL::DirectDriver
- [issue #127](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/127): Add photon components to event-wise leptonSF
- [issue #128](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/128): Fix behaviour of Cutbookkeepers in the python version

### 2.7.0 <small>April 2, 2024</small>
- We run on AB 25.2.5
- [issue #90](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/90): reduce the large memory footprint
- [issue #100](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/100): deal with the correct ordering of JVT and OR
- [issue #105](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/105): sort KLFitter inputs by pT
- [issue #106](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/106): clearer error message when YAML config file is not found
- [issue #107](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/107): update to new JVT selection names
- [issue #108](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/108): more data tests for the CI
- [issue #109](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/109): new algorithm for FakeBkgTools
- [issue #110](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/110): various minor updates to the docs
- [issue #111](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/111): improve ONNX support
- [issue #112](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/112): new way to add custom blocks directly in the YAML config
- [issue #114](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/114): improvements to the global trigger config
- [issue #115](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/115): save information about e-tags in the output metadata
- [issue #116](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/116): move to central GRLs
- [issue #117](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/117): improve analysis at particle-level
- [issue #120](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/120): new algorithm for Jet Reclustering

### 2.6.2 <small>March 29, 2024</small>
- For internal use only!

### 2.6.1 <small>February 16, 2024</small>
- We run on AB 24.2.41
- [issue #99](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/99): update to ConfigFactory syntax
- [issue #104](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/104): start documenting best practices for analysis

### 2.6.0 <small>February 14, 2024</small>
- We run on AB 24.2.40
- [issue #96](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/96): fix for missing AF3 Egamma calibrations
- [issue #97](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/97): document the updated PRW interface
- [issue #98](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/98): document the declaration of blocks in YAML
- [issue #102](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/102): allow to run NNLO reweighting in nominal-only mode
- [issue #103](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/103): compatibility with AthAnalysis

### 2.5.0 <small>January 19, 2024</small>
- We run on AB 24.2.37
- [issue #61](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/61): event selectors based on large-R jets
- [issue #70](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/70): adapt to the TextConfig refactoring
- [issue #83](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/83): add the central IFF classification algorithm
- [issue #84](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/84): support multiple instances of KLFitter
- [issue #85](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/85): adapt to the new metadata handling
- [issue #86](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/86): document two new event selectors based on leptons
- [issue #87](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/87): further documentation improvements to selectors
- [issue #88](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/88): centralise the calculation of per-event SFs
- [issue #89](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/89): add the number of particle-level truth b/c-jets
- [issue #91](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/91): add a FAQ for experienced AnalysisTop users
- [issue #92](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/92): adding new algorithm to retrieve the secondary vertex mass

### 2.4.0 <small>December 21, 2023</small>
- We run on AB 24.2.34
- [issue #76](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/76): update the documentation for jet calibration
- [issue #77](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/77): adding new algorithm for jet-to-particle matching
- [issue #78](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/78): minor improvement to the installation instructions
- [issue #79](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/79): update the available jet config options
- [issue #80](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/80): document the extended settings for Overlap Removal
- [issue #81](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/81): allow to select electrons and photons based on cluster eta
- [issue #82](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/82): add JVT selection to the output ntuple

### 2.3.0 <small>December 1, 2023</small>
- We run on AB 24.2.32
- [issue #72](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/72): improve the documentation on the ntupling syntax
- [issue #73](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/73): fix the writing of metadata when running on the Grid
- [issue #74](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/74): remove legacy FTAG settings
- [issue #75](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/75): adding new algorithm for jet-to-parton assignment

### 2.2.0 <small>November 24, 2023</small>
- We run on AB 24.2.31
- [issue #68](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/68): reduce the verbosity of the CI tests
- [issue #69](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/69): simplify the event selection config and the PMG weights bookkeeper histograms
- [issue #71](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/71): add algorithm to write b-tagging score and p/c/u probabilities.

### 2.1.0 <small>November 17, 2023</small>
- We run on AB 24.2.30
- [issue #34](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/34): MMC algorithm for di-tau mass reconstruction
- [issue #51](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/51): update the event selection example
- [issue #56](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/56): minor updates to the docs, mention `FastFrames` for histogramming
- [issue #57](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/57): remove ONNX files from the repository (now stored on CVMFS instead)
- [issue #58](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/58): event selectors based on photons and tau-jets
- [issue #59](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/59): document the `SysListDumperAlg` for the text-based config
- [issue #60](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/60): update the documentation of the electron and photon config blocks
- [issue #62](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/62): allow the filtering of output branches
- [issue #63](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/63): list all relevant metadata flags at the start of the job
- [issue #64](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/64): parton history for the tZq topology
- [issue #65](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/65): parton history for the ttH topology
- [issue #66](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/66): bugfix, missing list of systematics in the text-based config mode
- [issue #67](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/67): allow to read configs from arbitrary locations

### 2.0.0 <small>November 1, 2023</small>
- We run on AB 24.2.28
- [issue #43](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/43): transition to the text-based config model
- [issue #54](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/54): adapt PRW configuration to use central config block
- [issue #55](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/55): rename `postfix` to `selectionName` in config blocks for object working points

### 1.7.0 <small>October 20, 2023</small>
- We run on AB 24.2.27
- [issue #42](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/42): migration of the bootstrapping algorithm to Athena
- [issue #44](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/44): MC-MC b-tagging SFs
- [issue #45](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/45): documentation for systematics filtering
- [issue #46](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/46): various user-friendly improvements
- [issue #47](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/47): switch metadata autoconfiguration to config flags
- [issue #48](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/48): improve the interface of the NNLO reweighter
- [issue #49](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/49): option to disable re-calibration on PHYSLITE
- [issue #50](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/50): document all the config blocks (not just make-methods!)
- [issue #52](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/52): simplify the output structure and store metadata
- [issue #53](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/53): adapt to single-file output also on the Grid

### 1.6.0 <small>October 10, 2023</small>
- We run on AB 24.2.25
- [issue #31](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/31): algorithm to generate statistical bootstraps
- [issue #38](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/38): migration of the event selection algorithms to Athena
- [issue #39](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/39): fix crash on new NSW recommendations for Run 3
- [issue #40](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/40): better error reporting on the Grid
- [issue #41](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/41): fix SPA-Net CI tests

### 1.5.0 <small>September 26, 2023</small>
- We run on AB 24.2.23
- [issue #30](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/30): object- and event-wise cutflows
- [issue #35](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/35): new model for SPA-Net, ttbar l+jets with neutrino regression
- [issue #37](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/37): more FAQ and documentation for cutflows/sum-of-weights

### 1.4.0 <small>September 17, 2023</small>
- We run on AB 24.2.22
- [issue #26](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/26): read MC campaign from FileMetaData
- [issue #27](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/27): allow running on PHYSLITE
- [issue #28](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/28): partially refactor SPA-Net, introducing an ONNX wrapper
- [issue #29](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/29): update the docs for overlap removal
- [issue #33](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/33): add the new `SelectionNameSvc`

### 1.3.0 <small>August 28, 2023</small>
- We run on AB 24.2.19
- [issue #18](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/18): minor update to docs (`noEffSF` option, MET)
- [issue #19](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/19): added text-based event selection
- [issue #20](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/20): now support MC23 for 2022 and 2023
- [issue #21](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/21): performance improvements for the CI
- [issue #23](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/23): update the docs for JVT algorithms
- [issue #24](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/24): improve the metadata autoconfiguration for MC and data
- [issue #25](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/25): add CI tests on data

### 1.2.0 <small>August 18, 2023</small>
- We run on AB 24.2.18
- [issue #5](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/5): refactor `EventInfo` variables, now relying on `addOutputVar`
- [issue #7](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/7): introduced continuous integration tests covering compilation and running of the code, as well as simple output validation
- [issue #17](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/17): centralised the event-level f/JVT SFs

### 1.1.0 <small>August 17, 2023</small>
- [issue #1](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/1): fixed memory leaks in TopPartons and TopParticleLevel
- [issue #2](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/2): completed the documentation for "Settings"
- [issue #3](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/3): added a FAQ about Run 3 muon trigger settings
- [issue #4](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/4): all properties of TopParticleLevel are now exposed to configuration
- [issue #6](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/6): TtbarAnalysisConfig cleaned up and refactored
- [issue #12](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/12): fixed the saving of MET variables in the particleLevel tree, now as floats rather than vectors of floats
- [issue #13](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/13): minor improvement, using `ANA_CHECK` and `ANA_MSG`

### 1.0.0 <small>August 11, 2023</small>
- First release for early testing