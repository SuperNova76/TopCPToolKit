# Running on the grid

Pretty much any analysis will need to run AnalysisTop on the grid simply due to the huge disk size of the derivations and the processing time required.

## Preparing for grid submission

In what follows we will use a mixture of the old `TOPQ1` and the new `DAOD_PHYS` termininology. This caveat will be updated in the future once we have created the necessary `DAOD_PHYS` files.

AnalysisTop contains a bunch of helper python scripts to ease the submission of grid jobs, which are located in the [TopExamples](https://gitlab.cern.ch/atlas/athena/-/blob/21.2//PhysicsAnalysis/TopPhys/xAOD/TopExamples) package. To obtain copies of these scripts for yourself:
```bash
cd run # go to the run sub-directory in the directory where you set things up
mkdir grid
cd grid
cp $AnalysisBase_DIR/bin/01SubmitToGrid_Tutorial.py .
cp $AnalysisBase_DIR/bin/Data_rel21.py .
cp $AnalysisBase_DIR/bin/MC16_TOPQ1.py .
cp $AnalysisBase_DIR/bin/DerivationTags.py .
cd ../
```
We assume you have a fresh shell opened with AnalysisTop set up. Additionally, we will need to setup:
```bash
lsetup rucio panda pyami
voms-proxy-init -voms atlas # set up grid proxy, enter password for your grid certificate, if asked
```

### Grid submission scripts configuration

Open the copied `01SubmitToGrid_Tutorial.py` and examine its contents. Firstly, the `config.settingsFile` option controls which AnalysisTop config file will be used for execution on grid, i.e.:
```python
config.settingsFile  = 'custom-saver-test.txt'
```
Whenever preparing a config file for grid jobs, there are some **important considerations** to keep in mind:

- Are you setting `NEvents` in config to a fixed value ? Perhaps you ran a local check with a few hundred events, but on grid you in general want to run over all events available in a dataset.
- Do you need to run systematic uncertainties or not ? Running with systematics takes order of magnitude longer, and the output is also typically order of magnitude larger, so consider if you need to run systematics or only some studies with nominal TTree.

Next, you should set the `config.gridUsername` to your CERN account (what you use for login to lxplus) name and `config.suffix` to something unique and understandable (e.g. put date or release into the suffix). Here the task at grid will have name composed of the dataset name and the suffix, and note that you cannot submit jobs with the same name multiple times.

One of the greatest difficulties with efficient running on grid is determining number of files a single job should process, since grid sites have limits on maximum job time, as well as memory and storage constraints. Panda tries to determine this automatically, but you do have the option to set an upper limit per job:
```python
config.maxNFilesPerJob = '10'
```
Internally, the grid submission scripts call the `prun` command for job submission to grid, so any other options relevant to the prun (e.g. see this [twiki](https://twiki.cern.ch/twiki/bin/view/PanDA/PandaRun)) can be supplied via:
```python
config.otherOptions = '' # anything that prun accepts
```

Next up, the submission script contains a list sample groups which will be submitted:
```python
names = ['TOPQ1_ttbar_PowPy8',
#    'Data16_TOPQ1',
] 

```
Each entry represents one group of samples defined in the `MC16_TOPQ1.py` and `DATA_rel21.py` files (for the later we don't yet have a R22 version), which we copied as well. You can create your own list as well based on these examples and import it in the grid submission script. For example, the `MC16_TOPQ1.py` list contains entries such as:
```python
TopExamples.grid.Add("TOPQ1_ttbar_PowPy8").datasets = [
    'mc16_13TeV.410501.PowhegPythia8EvtGen_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_TOPQ1.e5458_s3126_r9364_r9315_p3215',
    ]
```
where the `PHYS_ttbar_PowPy8` defines a group of datasets, and those are specified in the python list assigned.

Obviously, the files we copied are only how-to examples, you have to make sure to use up-to-date samples. Let's do a simple check, whether the sample above is a reasonable choice.
The first thing you notice that this is an old `DAOD_TOPQ1` sample. In `R22` we will use `DAOD_PHYS` so lets look instead for:
```bash
mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p4856
```

Type the following:
```bash
rucio list-dids mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p4856
```
The command above lists samples matching the search pattern:
```bash
+---------------------------------------------------------------------------------------------------------------+-------------------+
| SCOPE:NAME                                                                                                    | [DID TYPE]        |
|---------------------------------------------------------------------------------------------------------------+-------------------|
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p4856 | DIDType.CONTAINER |
+---------------------------------------------------------------------------------------------------------------+-------------------+
```
Note that the fact that a dataset container is listed by rucio does not mean the sample has not been deleted. To check that, do:
```bash
rucio list-files mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p4856
```
and you should get
```
+--------------+--------+-----------+------------+----------+
| SCOPE:NAME   | GUID   | ADLER32   | FILESIZE   | EVENTS   |
|--------------+--------+-----------+------------+----------|
+--------------+--------+-----------+------------+----------+
Total files : 0
Total size : 0.000 B
```
in other words, this derivation has been deleted -- not really surprising as this was a very old version (one can tell by the last 5 characters, the p-tag p4856, recent samples have >= p5xxx, for example for this tutorial we used p5226).

Each sub-group of the [Physics Modelling Group (PMG)](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/PhysicsModellingGroup) group maintains information about recommended MC samples, for example the PMG TopProcesses subgroup twiki [lists recomended top-related samples](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/PmgTopProcesses#Practical_information), here you can see that the DSID 410470 is the current recommended ttbar MC sample. If we don't know the full dataset name, it is usually possible to search it out via rucio following some assumptions. Let's assume that the derivation format we want is `DAOD_PHYS`, and the DSID is 410470. To obtain simulation for full Run-II dataset, we will need three samples corresponding to the 2015-16 (mc16a), 2017 (mc16d) and 2018 (mc16e) data-taking period. This can be distinguished based on the r-tag, which is 13167, r13144 and r13145, respectively. Let's search for the most up-to-date 410470 mc16d sample:
```bash
rucio list-dids 'mc20_13TeV.410470*deriv.DAOD_PHYS*r13145*' | grep CONTAINER
```
The output of the command above may still yield a long list of samples (most of which are obsolete) but the samples with highest p-tag listed should include:
```
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p4856                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p4926                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p4931                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5057                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5089                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5226                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5267                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5440                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5477                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5487                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5511                         | DIDType.CONTAINER |
| mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_r13145_p5631                         | DIDType.CONTAINER |
```

The MC20 campaign identifies the `DIGI` and `RECO` reprocessing in R22 of MC16 simulated samples.
For this reason the production starts from hits in the MC16 campaign. The sub-campaign of AODs and RDOs reprocessed in R22 will be mc20a/mc20d/mc20e, following the original sub-campaign of mc16 HITS.

In the following a short description of the individual tags is given.

#### Simulation

 * `s3681` for full simulation with Geant4 (this is the output of the re-simulation, which takes as input the original hits produced in R21 with tag `s3126` and re-simulate long-lived hadrons and tau leptons). The corresponding tag for full simulation with Geant4, simulating also long lived particles from the beginning is `s3797`.
 * `a899` for fast simulation samples, produced with Atlfast3. All Standard Model samples produced with Atlfast2 in mc16 has been re-simulated with Atlfast3, which provides improved modeling, in R22. Beyond Standard Model samples are produced on request.

Physics considerations need to be made here, which choice is feasible. Full-sim is generally preferred for physics description (e.g. for example for description of substructure of jets, since fast simulation performs approximations of calorimeter shower evolution), but is much more CPU-expensive to simulate, therefore for some processes there may not be any full-sim samples generated

#### Reconstruction:
The following default tags are used for MC20 physics:

 * `r13167` recon (overlay+trigger+reconstruction) for `MC20a`
 * `r13144` recon (overlay+trigger+reconstruction) for `MC20d`
 * `r13145` recon (overlay+trigger+reconstruction) for `MC20e`

Tags without pile-up:

 * `r13297` recon (digitization+trigger+reconstruction) for `MC20a`
 * `r13298` recon (digitization+trigger+reconstruction) for `MC20d`
 * `r13299` recon (digitization+trigger+reconstruction) for `MC20e`

#### Pile-up presampling:
 * `d1713` MC20a RDO production (mc20_13TeV.900149.PG_single_nu_Pt50.digit.RDO.e8307_s3482_s3136_d1713)
 * `d1714` MC20d RDO production (mc20_13TeV.900149.PG_single_nu_Pt50.digit.RDO.e8307_s3482_s3136_d1714)
 * `d1715` MC20e RDO production (mc20_13TeV.900149.PG_single_nu_Pt50.digit.RDO.e8307_s3482_s3136_d1715)

#### special tags:

 * `r13146` AOD merge
 * `p4836` NTUP_PILEUP creation
 * `p4837` NTUP_PILEUP merge 

More information on the `a,s,r` tags can be found in [AtlasProductionGroup twiki](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/AtlasProductionGroupMC20).

As for the various p-tags, typically the newer p-tag the better, and in general samples with older p-tags are obsoleted and deleted unless exceptions are requested. To find out what AthDerivation release was used to produce a given p-tag sample, and what are the changes in the release, refer to [DerivationProduction twiki](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/DerivationProductionTeam).

For R22 only `DAOD_PHYS` is supposed to be used. You can find more information on it [here](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/DerivationProductionTeam?topic=DAODPhys).

The following resources may prove invaluable when dealing with datasets:

- [This page](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopDerivationsRun3) provides information on the derivation production of the ATLAS top group.
- For data derivation lists, see [TopGroupDataDerivationList page](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/TopGroupDataDerivationList).
- [AMI website](https://ami.in2p3.fr/) for metadata relevant for various tags and samples.
- AMI information can be obtained also via command line tool ami (which we set up via `lsetup pyami`), see some documentation [here](https://ami.in2p3.fr/pyAMI/).

Finally, let's test actual dataset submission. We will not be actually running the sample on grid, only to check whether the submission command looks ok. For this purpose, in the submission script, set:
```python
config.gridUsername = <username>
```
where `<username>` is your `lxplus` username and
```python
config.noSubmit = True
```
Next, let's put an actual up-to-date sample in the `MC16_TOPQ1.py`:
```python
TopExamples.grid.Add("TOPQ1_ttbar_PowPy8_mc16a").datasets = [
    'mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p5226',
    ]
```

and in `01SubmitToGrid_Tutorial.py` we specify the list we want to run on:
```python
names = [
    'TOPQ1_ttbar_PowPy8_mc16a',
]
```

Finally, let's try to execute in shell:
```bash
python grid/01SubmitToGrid_Tutorial.py
```
You should see the following output:
``` bash
Analysis Settings:
 -Code:           top-xaod
 -CutsFile:       custom-saver-test.txt (exists)
 -Combine_outputFile:       None
 -Combine_prefixes:       None
Grid Settings:
 -GridUsername:   username 
 -Suffix:         04-05-23
 -ExcludedSites:  
 -ForceSite:      
 -NoSubmit:       True
 -MergeType:      Default out of (None, Default, xAOD)
 -memory:         2000 in MB
 -maxNFilesPerJob 
 -skipShowerCheck False
 -OtherOptions:   
 -nameShortener:  <bound method basicInDSNameShortener of <TopExamples.grid.Config object at 0x7efca2f8bdc0>>
 -reuseTarBall:   False
 -checkPRW:       False
 -DestSE          <not set>

None
/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/AnalysisTop/TopDataPreparation/XSection-MC16-13TeV.data
For these samples

Starting submission of 1 sample

Submitting 1 of 1
prun \
--inDS=mc20_13TeV:mc20_13TeV.410470.PhPy8EG_A14_ttbar_hdamp258p75_nonallhad.deriv.DAOD_PHYS.e6337_s3681_r13145_p5226 \
--outDS=user.username.410470.PhPy8EG.DAOD_PHYS.e6337_s3681_r13145_p5226.04-05-23 \
--useAthenaPackages --cmtConfig=x86_64-centos7-gcc11-opt \
--writeInputToTxt=IN:in.txt \
--outputs=output-modifiedSelection_CustomSaver_root:output-modifiedSelection_CustomSaver.root \
--exec="top-xaod custom-saver-test.txt in.txt" \
--outTarBall=top-xaod.tar.gz \
--noSubmit \
--mergeOutput \
--memory=2000 \
```
If you haven't specified your username you will see a corresponding error.

As you can see, what the script does is to list your settings and then put everything together in a `prun` command.

From `outDS` parameter, you can see the name that the output dataset will have (the dataset for the root files will be e.g. in this example above called `user.username.410470.PhPy8EG.DAOD_PHYS.e6337_s3681_r13145_p5226.04-05-2_output_root/`, the username and the suffix depending on what you specify in the submission script.

To make sure the jobs do not fail on the grid, the submission script will automatically check that the datasets that you want to run over have a valid shower type defined in the TopDataPreparation file (see [AnalysisTop basics](ATBasics.md#topdatapreparation) for more on TopDataPreparation).

### Handling external files during grid submission

In certain cases, external files are required for running AnalysisTop, typical examples include:

- own pileup-reweighting files for samples for which centrally-provided PRW files don't exist
- custom flavour composition file for JetUncertainties
- custom TopDataPreparation database for some experiments with b-tagging showering MC/MC scale factors

In all of these cases, the files usually must be properly specified in the grid submission scripts and correct path must be used in the configuration file for AnalysisTop.

Firstly, **panda often likes to skip external files**, especially `.root` files and files above certain size limit (the logic isn't entirely trivial). The files to be included must be specified via `--extFile argument`. In your grid submission python script, you need:
```python
config.otherOptions = '--extFile=file1,file2,...' # just the names of the files should be sufficient, but relative paths should also (probably) work
```

Secondly, **never use absolute paths**, e.g. `/afs.cern.ch/user/...` in AnalysisTop config files, as the directory structure on a grid site is different, the contents of the files sent to grid are extracted to some path on grid that you in general have no control over. There are two approaches usable here:

- If you use your own package with AnalysisTop, e.g. for custom event saver, the easiest thing is to put all files under `package/share/` directory (where `package` is the name of your package) and **do a full cmake rebuild** (needed to pick up the paths to the files). Suppose you have a .root file
```
package/share/foobar.root
```
In your AnalysisTop config, the path to the file should then be
```
package/foobar.root
```
Notice the missing `share` in the path, this approach levarages the `PathResolver` logic, which has its own set of (peculiar) rules for file paths.

- The other approach (not requiring a package) is to make sure to use relative paths with respect to the submission directory. Let's suppose you have the following structure, where **it is important to have the external files in the directory with submission scripts, or a sub-directory.**
```
run/
  -> grid/
       -> someDirectory/
            -> foobar.root
      -> 01SubmitToGrid.py
      -> MC16_TOPQ1.py
      -> my-cuts.txt
```
Then, it is possible to specify path to `foobar.root` inside the config file `my-cuts.txt` simply as
```
someDirectory/foobar.root
```

### Other useful features of the grid submission scripts

There are three extra settings supported in the grid submission scripts, that may prove usefull:

- To exclude sites which you don't want the jobs to run on (e.g. they may be problematic due to whatever reason):
```python
config.excludedSites = 'SITE1,SITE2' #comma-separeted list of site names
```
You can find site names on [bigpanda.cern.ch](https://bigpanda.cern.ch)

- To store grid job output at a specific destination (storage element) (see [https://rucio-ui.cern.ch/](https://rucio-ui.cern.ch/)):
```python
config.destSE = 'SOMESTORAGEELEMENT' (for example AGLT2_LOCALGROUPDISK)
```
**Note** Where you can store files (and how much in terms of size) is subject to permissions and grid quotas.

- To speed-up submission, you can re-use existing compressed `top-xaod.tar.gz` archive. **Beware** it is easy to forget about this if you change some files and forget to remove the `top-xaod.tar.gz`, hence your jobs will not be re-submitted with new input!
```python
config.reuseTarBall = True
```

## Monitoring and diagnosing issues with grid jobs

Usually within a few minutes since grid job submission, the jobs should start appearing on [bigpanda web page](https://bigpanda.cern.ch/user/). This web page allows one to check progress of jobs, retrieving logfiles (necessary for investigating failing jobs) and lot of other related stuff. Logs of jobs can be accesed by opening a panda task and then clicking the number of finished or failed jobs, and then scrolling down to individual PanDA IDs of the jobs. Clicking the ID yields the job page where logs and memory and IO plots (usefull for e.g. detecting memory leaks) can be accessed.

In addition, a command-line tool for managing running jobs is available, [pbook](https://twiki.cern.ch/twiki/bin/view/AtlasComputing/PandaBook), which allows for basic operations, such as retry and kill jobs specified by task ID number (reminder, it is setup via `lsetup panda`):
```python
retry(taskID)
kill(taskID)
kill([taskID1,taskID2]) # basically this is a python prompt so anything that yields a python array is valid
```

### Frequently-encountered issues

 The information above is a baseline that should be a starting point for investigating issues with jobs. We will try to expand on some typical issues when running on grid below. Note that this section is more like a short reference rather than an interactive tutorial (and yes, we are not kidding about the briefness of this section when considering how much stuff can go wrong on grid...)

- **I changed my code/scripts, submitted another task, but my changes are not reflected at grid!** Check if you have `config.reuseTarBall=True` option in the submission script. If yes, this means that if a compressed tarball that is sent to grid exists in the directory (`top-xaod.tar.gz`) it has been re-uploaded without actually updating with your changes! This option is very nice when submitting many jobs at once, but if you use it, make sure to always delete the `top-xaod.tar.gz` tarball before you submit new tasks with changes.

- **Jobs take forever to start.** This can be seen by large time to start of the job. This could be related to your priority (check the priority of the jobs running on the site). If this is not the case, the site may be busy (too many jobs in the site queues) or some other issue (in which case it may be advisable to ask the DAST experts -- see [DAST twiki](https://twiki.cern.ch/twiki/bin/viewauth/AtlasComputing/AtlasDAST) for more info, and for mailing lists for support).

- **Jobs crash.** In this case the error message displayed in the job list may or may not be helpfull, in any case it is useful to examine the log files. Log files can be accessed by opening the specific crashing job and examining log files (log files on panda), in particular the `athena_stdout.txt` or `payload_stdout.txt` log files, that include output from AnalysisTop run (or any other task you run on grid in general).

- **Jobs take forever to run or crash due to exceeding site walltime limit.** Check if the job is running long for the first time, or if it has been retried. If the latter, this may indicate some issue with the code (a crash perhaps, see point above), or some issue related to the grid site potentially. Note that all grid sites have a limit on maximum time of a job (walltime). Thus you may have an issue due to your job being simply too long -- either the time to process an event is on average very high and/or the number of events to process in a single job is very high. This can become an issue in particular, if you are processing many systematics and/or using CPU-intensive algorithms, such as complex kinematic reconstruction algorithms (e.g. KLFitter, NeutrinoWeighting, etc). In this case, lowering the number of files per job may be desired. When submitting a sample to grid, this can be achieved by the `config.maxNFilesPerJob` setting, limiting the maximum amount of files per job. Alternatively, if you are retrying a job via pbook, it is possible to use the `nFilesPerJob` option specifying exact number of files per job (note, that you cannot use maxNFilesPerJob in pbook):
```python
retry(taskID, newOpts={'nFilesPerJob':5})
```
Ideally, it is useful to download a single file from the offending sample and try to run it locally to get an idea how long does it take to process N events and guesstimate the number of files accordingly to fit into the site walltime. For full-systematics NTuple production with KLFitter for instance, it is not unexpected having to run with single file per job for signal samples (and any samples that have high event selection efficiency in general)!

- **Broken tasks.** Each task runs several (typically 10?) scout jobs, which are used to check if the task does not crash, if the site meets requirements such as sufficient memory, etc. If all of the scout jobs fail, the task is sent to broken state, and no further jobs of the task are executed. This calls for investigating why the jobs crashed and fixing the issue. Either your jobs have crashed due to your fault, or the crashes are site-related, in both cases you encounter an issue, where the job to be resubmitted needs a new unique name. It is possible to resubmit a job with identical name, by running the 01SubmitToGrid.py script with the specific sample and additional parameter (**DRAGONS AHEAD**):
```python
config.newOpts = ' --allowTaskDuplication'
```
**NOTE: When downloading output from grid from duplicated task, output of all duplicates will be downloaded!** In case of a broken task, where all jobs crashed, there is no output, so in such a case it is safe to use this option. Otherwise, prepare for duplicate events. Additionally, in case of site-related issues, it may be necessary to exclude it using the `config.excludedSites` option in the submission script.

- **Retrying failed task in pbook on a different site.** Sometimes, the only way to overcome a problem is to retry a job on a different site. This can be done using pbook:
```python
#to exclude sites XXX and YYY, where XXX and YYY must match the bigpanda name
retry(taskID, newOpts={'excludedSite':'XXX,YYY'})
```

- **Debugging memory-related problems on bigpanda.** Majority of the grid sites have a limit on memory for single-core jobs of 2GB. Unfortunately, for analyses using complex computations and many objects, and precision recommendations (looots of systematics), this becoming more and more commong of a problem. First, in case of memory leaks, typically panda will show warnings on the task details page about jobs consuming excessive amount of memory, or kill your jobs right away. It is possible to view the memory consumption and input/output (I/O) of job as a function of time in graphs in the detailed view of a specific job and opening the Memory and IO plots. There may be legitimate reasons for high memory consumption, as outlined below.


- **Large RAM consumption due to branch buffer optimization.** Another frequent issue in case of large NTuples (many systematics and or plenty of branches, and/or heavy branches, such as vectors) is the RAM consumption of the branch buffer optimization. This problem manifests itself by a sharp increase in RAM consumption after a certain amount of time, when output events were processed which are about to be written to file. By default TTree cache in memory and the output is written out every 1000 events. The easiest recommendation is to reduce the size of NTuples as much as possible and consider if some of the stored variables could be computed offline instead. Another option, if running with systematics, is to split systematics into multiple jobs. Finally, if that is not enough, it is possible to play with the following parameter in AT configuration file, but please mind that THIS MAY LEAD TO I/O PERFORMANCE ISSUES when reading the produced NTuples:
```
OutputFileBasketSizePrimitive 4096 # initial buffer size for bool, int, float, ...
OutputFileBasketSizeVector 40960 # initial buffer size for vector
OutputFileNEventAutoFlush 1000 # number of saved events after which buffer sizes are optimized
```
More realistic values for initial buffer sizes may reduce the amount of memory needed for the reoptimization and decreasing the `OutputFileNEventAutoFlush` value reduces the amount of cached events to be written out, but note that lowering the value does also reduce the I/O performance for the output files (meaning, offline analysis of these files will have slower read performance as well).

## Downloading grid output

To download output from grid, we use `rucio` tool, which can be set up via
```bash
lsetup rucio
```
**NOTE** It is advisable to setup rucio in a new shell. This is in particular true if you already have AnalysisBase set up in a shell, rucio has known compatibility issues with AB.

Downloading of a dataset:
```bash
rucio download output-dataset-name
```
where the output dataset name for analysistop jobs is typically of the format of user.USERNAME.DSID....tags.SUFFIX. Rucio accepts `*` wildcards, so you can batch download many samples at once, for example:
```bash
rucio download 'user.omajersk.*AT212173test'
```
where in the submission script, the `config.suffix` was set to `AT212173test`. **NOTE** Always encompass the download argument in *single quotes*, because otherwise your shell may attempt to interpret the `*` characters.

Tip: You may be interested in the how-to on replicating of datasets (including output) to various grid sites, described in [this part](Storage.md#replicating-datasets-on-the-top-grid-disks) of the tutorial.

Sometimes, if downloading file fails repeatedly, one potential trick is to make a temporary replica (see the link above) to a different grid site scratch disk and repeat the download. If this fails, contacting DAST mailing list (`hn-atlas-dist-analysis-help@cern.ch`) may be appropriate.
