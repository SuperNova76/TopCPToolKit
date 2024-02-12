!!! abstract "In this session you will..."
    - understand the differences between a CP tool and a CP algorithm
    - write a simple algorithm to perform a piece of analysis
    - create new output variables (both event-wise and object-wise)
    - make your algorithm configurable in YAML and useable by others

_For this part, we assume you're already familiar with the contents of ["Your first config"](write_config.md) and have followed the ["Initial setup"](setup.md) instructions._

## The necessary basics

We have alluded to CP tools and algorithms in many places so far, let's try to clarify these concepts a little bit: what exactly are we talking about?

!!! tip
    The [ATLAS Software tutorials](https://atlassoftwaredocs.web.cern.ch/ABtutorial/alg_basic_intro/) are also very relevant to this session!

    If you already feel confident with these topics, you may skip this section :student:

### CP tools

First and foremost: "CP" stands for "Combined Performance", and refers to the centralised and essential aspects of any ATLAS analysis such as object reconstruction and calibration.
In ATLAS, there are CP groups for electrons/photons, muons, taus, jets/missing energy, etc.
The relevant tools they provide are the official "CP tools".

!!! note
    Technically, "CP tools" all derive in a more or less complicated way from the [`AsgTool`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Control/AthToolSupport/AsgTools/AsgTools/AsgTool.h) class.

Let's take a look at one example of a CP Tool: the [`EgammaCalibrationAndSmearingTool`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/ElectronPhotonID/ElectronPhotonFourMomentumCorrection/Root/EgammaCalibrationAndSmearingTool.cxx#0265), which (unsurprisingly) is used to calibrate and smear "Egamma" objects (i.e. electrons and photons).

We want to highlight the following features:

- the tool exposes a number of **properties** (here with `declareProperty`)
- the tool has an `initialize()` method and a `finalize()` method, to be run before and after the event loop
- the tool can have as many other methods as necessary, and in this particular case we find two interesting ones:
    - `setupSystematics()`: **the tool generates its own relevant list of systematics!**
    - `applyCorrection(xAOD::Egamma & input)`: this is how the tool will act on each individual electron (to calibrate it)

!!! note
    Depending on the purpose of the tool, it may act on individual objects or entire collections. It can even run solely on `EventInfo`. The tool doesn't know anything about the "event".

### CP algorithms

Since CP tools need to be configured in specific ways and applied onto relevant objects, we need something to take care of that: it's exactly what algorithms are for.

Let's take the example of electron calibration again: we want to use the latest recommendations from the Egamma CP group and calibrate our electron momenta.
Not only that, we know that there are uncertainties related to this calibration that we need to take into account in our analysis, so we want to obtain not just one calibrated collection of electrons for each event, but a series of them, corresponding to these systematically-varied calibration options.
This is what the [`EgammaCalibrationAndSmearingAlg`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaCalibrationAndSmearingAlg.cxx) does.

Let's inspect the (much shorter!) code here:

- the algorithm can also **expose configurable properties** (here again with `declareProperty`)
- the algorithm also has `initialize()` and `finalize()` methods, and a new `execute()` one
    - in the `initialize()` step, we recognise that an instance of the calibration tool is being initialised itself. We also see a `m_systematicsList` object be initialised.
    - the `finalize()` method here doesn't need to do anything, so it's actually omitted (this is often, but not always, the case!)
    - in `execute()`, we loop over all relevant systematics, retrieve the electron container, apply the systematic variation in our tool and use it to calibrate the electrons.

You will find very similar flows in all the CP algorithms.
There is still a bit of a mystery remaining... how does the algorithm know which input/output containers to get, and what is this `m_systematicsList`?
The answer to both lies in a third concept we need to discuss.

### How to connect everything together: handles

Much like for real tools, it's a useful idea to give our CP tools and object containers various types of "handles" such that they know what to run on.
Handles in this context are "proxy objects" - we can use them to define tools and containers without having to specify exactly which tool or container to read in or write out.
This is left for later, when we have a full configuration of our analysis sequence in place.

Let's look at the [header file](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/EgammaAnalysisAlgorithms/EgammaCalibrationAndSmearingAlg.h) for our electron calibration algorithm.
We find the following declarations:

```cpp
SysCopyHandle<xAOD::EgammaContainer> m_egammaHandle {
    this, "egammas", "Electrons", "the egamma collection to run on"};
```

This particular handle is used to generate systematicall-varied copies of `xAOD::EgammaContainer` - exactly what we need to define our newly calibrated electron collections!
It can be configured via a property named `egammas`, which is by default set to "Electrons" (which is indeed the name we use in DAOD PHYS).
The last part is obviously an info-string.

```cpp
ToolHandle<CP::IEgammaCalibrationAndSmearingTool> m_calibrationAndSmearingTool;
```

This is a much more succinct type of handle, used to pass a tool (here the calibration tool itself).

```cpp
SysListHandle m_systematicsList {this};
```

This final and very particular handle registers a list of systematics.

Let's now go back to the [main code of the algorithm](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/EgammaAnalysisAlgorithms/Root/EgammaCalibrationAndSmearingAlg.cxx) and explain the "mystery behaviours" we anticipated earlier.

```cpp
ANA_CHECK (m_egammaHandle.initialize (m_systematicsList));
```

Here we take the electron handle and initialise it to be connected to the "Electrons" container in the DAOD.
In case that container came with systematics of its own (here it doesn't), these systematics are added to the handle.

```cpp
ANA_CHECK (m_systematicsList.addSystematics (*m_calibrationAndSmearingTool));
```

Now we fill the systematics handle with the systematics that are being generated by the calibration tool.
At this point, we have all the systematics that we need, so we lock them in the handle:

```cpp
ANA_CHECK (m_systematicsList.initialize());
```

The loop over systematics that takes place in `execute()` is then **exclusively over the relevant systematics** (that we have just registered!).
We use our electron handle to retrieve the proper container for each systematic:

```cpp
xAOD::EgammaContainer *egammas = nullptr;
ANA_CHECK (m_egammaHandle.getCopy (egammas, sys));
```

### CP algorithms: the flow

We will soon attempt to write our own CP algorithm, so let's summarise the key points:

- we can set configurable properties to drive the behaviour of the algorithm
- we can pass any tool we need
- we use handles to read in and write out any container
- this allows us to automatically deal with systematics without ever having to know what they are

### A list of useful handles

The following handles are commonly used in CP and analysis algorithms.
We'll use some of them ourselves in this tutorial!
For container handles, any `xAOD::` container can be used; for decoration handles, all the standard types are supported (even `TLorentzVector` and `std::vector`!).
It is also possible to make arrays of handles, to be configured by the user.

- [`SysListHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysListHandle.h): used exclusively for the systematics list
- [`SysCopyHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysCopyHandle.h): make systematically-varied copies of an input collection (used in CP cases for calibration, rarely used in analysis)
- [`SysReadHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysReadHandle.h): retrieve systematically-varied collections (that's the one you want for analysis!)
- [`SysWriteHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysWriteHandle.h): register a new systematically-varied collection (rarely used in analysis)
- [`SysReadSelectionHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SelectionHelpers/SelectionHelpers/SysReadSelectionHandle.h): read an input systematically-varied selection cut
- [`SysWriteSelectionHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SelectionHelpers/SelectionHelpers/SysWriteSelectionHandle.h): register your new systematically-varied selection cut
- [`SysReadDecorHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysReadDecorHandle.h): read an input systematically-varied decoration
- [`SysWriteDecorHandle`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/SystematicsHandles/SystematicsHandles/SysWriteDecorHandle.h): register your new systematically-varied decoration

!!! note
    We use **_selections_** to be able to **filter out events and objects**. We use **_decorations_** to store additional information that can either be retrieved in another algorithm, or **saved as a branch** in the output ntuple.