# The name of the package:
atlas_subdir(TopCPToolkit)

# Find KLFitter package in atlasexternals,
# source from https://www.github.com/KLFitter/KLFitter
find_package(KLFitter)
find_package(onnxruntime)

# Add the shared library:
atlas_add_library(
  TopCPToolkitLib
  TopCPToolkit/*.h
  TopPartons/*.h
  TopParticleLevel/*.h
  TopSpaNet/*.h
  TopNNLOReweighter/*.h
  TopEventSelection/*.h
  Root/*.cxx
  INCLUDE_DIRS
  ${KLFITTER_INCLUDE_DIRS}
  ${ONNXRUNTIME_INCLUDE_DIRS}
  PUBLIC_HEADERS
  TopCPToolkit
  TopEventSelection
  TopPartons
  TopParticleLevel
  TopSpaNet
  TopNNLOReweighter
  LINK_LIBRARIES
  ${KLFITTER_LIBRARIES}
  ${ONNXRUNTIME_LIBRARIES}
  AnaAlgorithmLib
  xAODMissingET
  xAODJet
  xAODEgamma
  xAODMuon
  xAODTruth
  xAODCore
  PathResolver
  FourMomUtils
  FTagAnalysisInterfacesLib
  SystematicsHandlesLib
  SelectionHelpersLib
  MCTruthClassifierLib
)

# if (XAOD_STANDALONE) Add the dictionary (for AnalysisBase only):
atlas_add_dictionary(
  TopCPToolkitDict TopCPToolkit/TopCPToolkitDict.h
  TopCPToolkit/selection.xml LINK_LIBRARIES TopCPToolkitLib
)
# endif ()
#
# if (NOT XAOD_STANDALONE) # Add a component library for AthAnalysis only:
# atlas_add_component (TopCPToolkit src/components/*.cxx LINK_LIBRARIES
# TopCPToolkitLib) endif ()

# Install files from the package:
atlas_install_joboptions(share/*.py)
atlas_install_python_modules(python/*.py)
atlas_install_scripts(share/runTop_el.py)
atlas_install_data(share/*)
