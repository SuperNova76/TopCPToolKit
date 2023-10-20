# Changelog

## TopCPToolkit releases

### Upcoming release

- [issue #34](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/34): MMC algorithm for di-tau mass reconstruction
- [issue #42](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/42): migration of the bootstrapping algorithm to Athena
- [issue #47](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/47): switch metadata autoconfiguration to config flags

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