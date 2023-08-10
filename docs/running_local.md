After a successful compilation, you now have access to `runTop_el.py` on the command line: it's [this script](https://gitlab.cern.ch/atlasphys-top/reco/TopCPToolkit/-/blob/main/source/TopCPToolkit/share/runTop_el.py).
It's recommended to run the code in a dedicated directory, such as the top-level `run` folder we created earlier.

## Running locally

You can run the event loop on a `DAOD_PHYS` sample (one or multiple files).
Put the absolute or relative path to the file(s) in a text file, which we'll assume from now on you called `inputs.txt`.
Everything else is configured from arguments to the command line, and we'll go over the most important ones.

!!! note
    The code expects to run over **a single sample** at a time, i.e. you shouldn't list multiple DSIDs or MC campaigns in the same input text file.
    For that, you always have to write your own script.

The minimal working command you can issue, using all default settings, is:
```sh
runTop_el.py -i inputs.txt -o output
```

which will **process the entire sample** with the **default analysis** setup, at **detector-level only**, and **including all systematics and event filters**.
This may not be what you want to do, so read on below to see what you can change.

The output ntuple file is saved under `output/data-ANALYSIS/output.root`.
The CutBookkeeper histograms are available in `output/hist-output.root`.

## Command line options

Only the text file with the input samples and the location of the output directory are required to run `runTop_el.py`.
All other flags are optional and listed in the table below. You can also run
```sh
runTop_el.py -h
```

| **Option** | **Default** | **Usage** |
| ---------- | ----------- | --------- |
| `--max-events`<br>`-e`  | -1                                             | Specify the number of events to run over. |
| `--analysis`<br>`-a`    | `TopCPToolkit.TtbarCPalgoConfigBlocksAnalysis` | Specify the analysis module to run as `package.moduleName`. |
| `--parton`              | False                                          | Toggles the parton-level analysis. |
| `--particle`            | False                                          | Toggles the particle-level analysis. |
| `--no-systematics`      | False                                          | Toggles off the computation of systematics. |
| `--no-debug-histograms` | False                                          | Toggles off the saving of debugging histograms. |
| `--no-filter`           | False                                          | Save all events regardless of analysis filters (still saves the decision). |

Here are a few use cases:
=== "Typical analysis"
    ```sh
    runTop_el.py -i inputs.txt -o output --parton --particle --no-debug-histograms -a TopCPToolkit.MyCustomAnalysis
    ```
=== "Developer, no systs"
    ```sh
    runTop_el.py -i inputs.txt -o output --no-systematics -e 100
    ```