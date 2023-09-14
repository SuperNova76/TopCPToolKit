Whether you intend to run locally or on the Grid, you will need to get the [source code for TopCPToolkit](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit) and compile it against a suitable software environment.
Here we guide you through the necessary first steps.

## Getting the code

Get a local copy of the git repository with:

=== "Kerberos"
    ```sh
    git clone https://:@gitlab.cern.ch:8443/atlasphys-top/reco/TopCPToolkit.git
    ```
=== "SSH"
    ```sh
    git clone ssh://git@gitlab.cern.ch:7999/atlasphys-top/reco/TopCPToolkit.git
    ```
=== "HTML"
    ```sh
    git clone https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit.git
    ```

The actual code lives in the top-level `source` folder; everything else is needed for e.g. CI tests, GitLab features, powering this website, etc.
Create the additional folders where we will compile the code and run some examples:
```sh
mkdir -p build run
```

Note that you are now on the `main` branch, which is used for development. To access a [stable release](/changelog), you need to switch to the corresponding tag:
```sh
git fetch -a
git checkout tags/vX.Y.Z -b mybranch
```

## Setting up the environment

Assuming you are working on Lxplus or an equivalent setup with access to CVMFS, all you need is the following:
=== "Simple"
    ```sh
    setupATLAS
    cd build
    ```
=== "Development"
    ```sh
    setupATLAS
    lsetup git -q
    cd build
    ```

followed by a suitable choice of AnalysisBase release:
=== "New setup"
    ```sh
    asetup AnalysisBase,24.2.22
    ```
=== "Re-use existing setup"
    ```sh
    asetup --restore
    ```

!!! tip
    AnalysisBase releases in the 24.2.x series are [listed here](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/AnalysisBaseReleaseNotes24pt2), together with the changes that went into them. Those that affect CP algorithms are tagged with `CPAlgorithms`.

For a fresh compilation, or to include new files from the `source/` folder:
=== "Simple"
    ```sh
    cmake ../source
    ```
=== "Debugging"
    ```sh
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS='-g -O0' ../source
    ```

then compile and set up the new environment:
=== "Compile"
    ```sh
    make -j4
    source */setup.sh
    ```
=== "Re-use existing setup"
    ```sh
    source */setup.sh
    ```

And you're ready to go!

## Expert mode: compiling against Athena

!!! warning
    Only do this if you really have to... :slight_smile:
    
    Most common use cases: you need to run with a modified version of a tool/algorithm in [Athena](https://gitlab.cern.ch/atlas/athena/).

!!! tip
    This [cheatsheet](https://atlassoftwaredocs.web.cern.ch/gittutorial/GitCheatSheet.pdf) is very useful!

Set up a sparse-checkout of Athena, using the `main` branch or the relevant `release/24.2.x` tag.
The packages you might want to add probably live under [PhysicsAnalysis/Algorithms/](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/).
Then move `source/TopCPToolkit` to within the newly created `athena` folder.
From the `build` directory, you can now compile as:
=== "Simple"
    ```sh
    cmake ../athena/Projects/WorkDir
    make -j4
    source */setup.sh
    ```
=== "Debugging"
    ```sh
    cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS='-g -O0' ../athena/Projects/WorkDir
    make -j4
    source */setup.sh
    ```
