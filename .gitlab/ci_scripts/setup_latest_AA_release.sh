#!/bin/bash
echo "-----------------------------------------------"
echo "    Setting up the latest release for 25.2   "
echo "-----------------------------------------------"
echo "    Entering Development directory...          "
echo "-----------------------------------------------"
thisDir=$PWD
echo "Export ATLAS_LOCAL_ROOT_BASE"
# Now run the enviroment setup
export ATLAS_LOCAL_ROOT_BASE='/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase'
env | grep ATLAS_LOCAL_ROOT_BASE
echo "Source setupATLAS"
source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh
echo "Sourced"
echo "Find latest tag"
echo "-----------------------------------------------"
echo "
import sys
all_rel = sys.argv[1:]
print(sorted(all_rel, key=lambda x : int(x.split(\".\")[-1]))[-1])
" > script.py
TAG=`python3 script.py \`ls /cvmfs/atlas.cern.ch/repo/sw/software/25.2/AthAnalysis | xargs\``
# Print info
echo "-> Setup release... $TAG"
echo "--------------------------------------------------------"
echo "-> Running command : asetup AthAnalysis,$TAG,here"
echo "--------------------------------------------------------"
asetup AthAnalysis,$TAG,here
echo " AthAnalysis,$TAG " > version.txt
cp $AthAnalysis_DIR/ReleaseData ReleaseData
