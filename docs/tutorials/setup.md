All the tutorials listed here can be run within the same software environment.
Let's set it up now: **please make sure you are working in a clean shell**.

## Getting the code

We need to get a local copy of the [source code for TopCPToolkit](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit).
Download it with:

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

and move into the `TopCPToolkit` directory with:
```
cd TopCPToolkit
```

The actual code lives in the top-level `source` folder; everything else is needed for e.g. CI tests, GitLab features, powering this website, etc.
Create the additional folders where we will compile the code and run some examples:
```sh
mkdir -p build run
```

Note that we are now on the `main` branch, which is used for development.
For the purposes of this tutorial, we will use a [stable release](../changelog/index.md) instead:
```sh
git fetch -a
git checkout tags/v2.5.0 -b mytutorial
```

## Setting up the environment

Assuming you are working on Lxplus or an equivalent setup with access to CVMFS, all you need is the following:
```sh
setupATLAS
cd build
asetup AnalysisBase,24.2.38
cmake ../source
make -j4
source */setup.sh
```

??? tip "Re-using an existing setup"
    You may want to come back to the tutorial at a later time, or start again from a clean shell. You don't have to recompile everything from scratch! Simply run
    ```sh
    setupATLAS
    cd build
    asetup --restore
    source */setup.sh
    ```
    and you will recover your working environment.

??? tip "Modifying files"
    Throughout the tutorials, you will be invited to make modifications to the package. If these modifications are made on files that need compiling (e.g. `.cxx` or `.h`), you will need to go back to your `build` directory and run again
    ```sh
    make -j4
    source */setup.sh
    ```

??? tip "Creating new files"
    As above, we need to recompile the package, but also tell CMake to discover these new files. In your `build` directory:
    ```sh
    cmake ../source
    make -j4
    source */setup.sh
    ```
    When the changes are significant, it may sometimes be necessary to clear the `build` directory altogether and compile again from scratch.
