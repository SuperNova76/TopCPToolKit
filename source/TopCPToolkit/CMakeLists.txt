# The name of the package:
atlas_subdir(TopCPToolkit)

# Find KLFitter package in atlasexternals,
# source from https://www.github.com/KLFitter/KLFitter
find_package(KLFitter)
find_package(onnxruntime)

# Add the shared library:
if( XAOD_STANDALONE )
  atlas_add_library(
    TopCPToolkitLib
    TopCPToolkit/*.h TopPartons/*.h TopParticleLevel/*.h TopSpaNet/*.h TopNNLOReweighter/*.h
    Root/*.cxx Root/preloader/*.cxx
    INCLUDE_DIRS ${KLFITTER_INCLUDE_DIRS} ${ONNXRUNTIME_INCLUDE_DIRS}
    PUBLIC_HEADERS TopCPToolkit TopPartons TopParticleLevel TopSpaNet TopNNLOReweighter
    LINK_LIBRARIES ${KLFITTER_LIBRARIES} ${ONNXRUNTIME_LIBRARIES}
    AnaAlgorithmLib AsgAnalysisAlgorithmsLib xAODMissingET xAODJet xAODBTagging xAODEgamma xAODMuon xAODTau xAODTruth xAODCore PathResolver FourMomUtils DiTauMassToolsLib FTagAnalysisInterfacesLib SystematicsHandlesLib SelectionHelpersLib MCTruthClassifierLib FakeBkgToolsLib
    # THE FOLLOWING ARE NEEDED FOR THE COMPONENT PRELOADER:
    EgammaAnalysisAlgorithmsLib ElectronPhotonFourMomentumCorrectionLib MuonEfficiencyCorrectionsLib ElectronPhotonSelectorToolsLib TrackingAnalysisAlgorithmsLib TruthClassificationLib PMGToolsLib EventSelectionAlgorithmsLib xAODBTaggingEfficiencyLib JetAnalysisAlgorithmsLib JetJvtEfficiencyLib ElectronEfficiencyCorrectionLib JetUncertaintiesLib MuonAnalysisAlgorithmsLib FTagAnalysisAlgorithmsLib TrigGlobalEfficiencyCorrectionLib MuonSelectorToolsLib MuonMomentumCorrectionsLib METUtilitiesLib ParticleJetToolsLib PileupReweightingLib egammaMVACalibLib MetAnalysisAlgorithmsLib GoodRunsListsLib TauAnalysisAlgorithmsLib TriggerAnalysisAlgorithmsLib TrigConfxAODLib AssociationUtilsLib
    # END OF COMPONENT PRELOADER
    )
else ()
  atlas_add_library(
    TopCPToolkitLib
    TopCPToolkit/*.h TopPartons/*.h TopParticleLevel/*.h TopSpaNet/*.h TopNNLOReweighter/*.h
    Root/*.cxx
    INCLUDE_DIRS ${KLFITTER_INCLUDE_DIRS} ${ONNXRUNTIME_INCLUDE_DIRS}
    PUBLIC_HEADERS TopCPToolkit TopPartons TopParticleLevel TopSpaNet TopNNLOReweighter
    LINK_LIBRARIES ${KLFITTER_LIBRARIES} ${ONNXRUNTIME_LIBRARIES}
    AnaAlgorithmLib AsgAnalysisAlgorithmsLib xAODMissingET xAODJet xAODBTagging xAODEgamma xAODMuon xAODTau xAODTruth xAODCore PathResolver FourMomUtils DiTauMassToolsLib FTagAnalysisInterfacesLib SystematicsHandlesLib SelectionHelpersLib MCTruthClassifierLib
    )
endif ()

if ( XAOD_STANDALONE ) #Add the dictionary (for AnalysisBase only):
  atlas_add_dictionary(
    TopCPToolkitDict TopCPToolkit/TopCPToolkitDict.h
    TopCPToolkit/selection.xml LINK_LIBRARIES TopCPToolkitLib
    )
else () # Add a component library for AthAnalysis only:
  atlas_add_component (
    TopCPToolkit src/components/*.cxx LINK_LIBRARIES
    TopCPToolkitLib
    )
endif ()

# Install files from the package:
atlas_install_python_modules(python/*.py)
atlas_install_joboptions(bin/*.py)
atlas_install_scripts(bin/runTop_el.py)
atlas_install_data(share/*)
