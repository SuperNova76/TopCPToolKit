# TopCPToolKit

A comprehensive documentation is being built and will appear [here](https://topcptoolkit.docs.cern.ch/).

## Running the Code
You can run the code on a `DAOD_PHYS` sample as:

```bash
runTop_el.py -i input_sample.txt -o outputDir --parton --particle
```

## Submitting Jobs to the Grid
To submit jobs to the grid, use the following command:

```bash
python run/grid/submitToGrid.py
```

Before submitting, ensure that the option in the configuration file is set correctly:

```python
config.noSubmit = False  # Set to False to submit to the grid, True to only generate job files
```

### Modifying the Submission Configuration
The user must modify the file `run/grid/MC20_PHYS.py` appropriately to specify the samples they want to submit to the grid.

### Configuration File
The main configuration file is located at:

```
source/TopCPToolkit/share/configs/tWZ_test/reco.yaml
```

Users need to modify this file as needed for their analysis before submission.

### Special Case for Diboson (ZZ) Samples
Diboson (ZZ) samples require a specific generator and must be submitted separately. Ensure that the `reco.yaml` file includes the following modification:

```yaml
generator: 'Sherpa2212'
```

This ensures proper handling of the Diboson (ZZ) samples during grid submission.

---
This README provides a quick reference for running the code and submitting jobs to the grid. For further details, refer to the official [documentation](https://topcptoolkit.docs.cern.ch/).

