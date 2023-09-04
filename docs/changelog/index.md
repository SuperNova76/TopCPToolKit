# Changelog

## TopCPToolkit releases

### Upcoming release

- We run on AB 24.2.20
- [issue #26](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/issues/26): read MC campaign from FileMetaData

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