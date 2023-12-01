#!/usr/bin/env python

from AthenaConfiguration.AllConfigFlags import initConfigFlags
from AthenaConfiguration.AutoConfigFlags import GetFileMD
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
from argparse import ArgumentParser
from TopCPToolkit import metaConfig
import ROOT
import os, shutil

p = ArgumentParser('Run EventLoop with CP algorithms in local input')
p.add_argument('-i', '--input-list', required=True,
               help='Path to text file with input DAOD files to process.')
p.add_argument('-o', '--output-name', required=True,
               help='Name of the output file (without .root)')
p.add_argument('-e', '--max-events', type=int, required=False, default=-1,
               help='Number of events to run over. Set to -1 to run over all events.')
p.add_argument('-a', '--analysis', type=str,
               default='TopCPToolkit.TtbarCPalgoConfigBlocksAnalysis',
               help='Name of reco analysis to run. Should be package.moduleName,'
                    'where module implements makeRecoConfiguration method')
p.add_argument('--parton', action='store_true',
               help='Wheter to run parton level')
p.add_argument('--particle', action='store_true',
               help='Whether to run particle level')
p.add_argument('--no-systematics', action='store_true',
               help='Configure the job to run with no systematics.')
p.add_argument('--no-filter', action='store_true',
               help='Skip filtering of events due to event selection (selection flags are still stored.)')
p.add_argument('-t', '--text-config', type=str,
               default=None,
               help='Name of the analysis to run. Should be a directory containing reco.yaml,'
               'and optionally particle.yaml and parton.yaml.')

args = p.parse_args()

ROOT.xAOD.Init().ignore()
sh = ROOT.SH.SampleHandler()
sh.setMetaString('nc_tree', 'CollectionTree')

sample_name = 'output' # this thing is used by SampleHandler

sample = ROOT.SH.SampleLocal(sample_name)
files = metaConfig.parse_input_filelist(args.input_list)
for f in files:
    sample.add(f)
sh.add(sample)

driver = ROOT.EL.DirectDriver()
driver.options().setBool(ROOT.EL.Job.optGridReporting, True)

# read FileMetadata
flags = initConfigFlags()
flags.Input.Files = files
metadata = GetFileMD(files)
metaConfig.populate_config_flags(flags, metadata)
flags.lock()
metaConfig.pretty_print(flags)

maxEvents = args.max_events

#output stream name in EventLoop
outputStreamName = 'ANALYSIS'
# outfile is the standard output file from EventLoop
outfile = f'{args.output_name}/data-{outputStreamName}/{sample_name}.root'
# these are temporary files to merge outputs from the reco, particle-level and parton sequences
recofile = f'{sample_name}_reco.root'
partonfile = f'{sample_name}_truth.root'
particlefile = f'{sample_name}_pl.root'
histofile = f'{args.output_name}/hist-{sample_name}.root'
# the final file to keep
finalfile = f'{args.output_name}.root'

job = ROOT.EL.Job()
job.sampleHandler(sh)
job.options().setDouble(ROOT.EL.Job.optMaxEvents, maxEvents)
job.options().setString(ROOT.EL.Job.optSubmitDirMode, 'overwrite')
if args.text_config:
    from TopCPToolkit.commonAlgoConfig import makeTextBasedSequence
    algSeq = makeTextBasedSequence(args.text_config, 'reco', flags,
                                   noSystematics=args.no_systematics)
else:
    from TopCPToolkit.commonAlgoConfig import makeRecoSequence
    algSeq = makeRecoSequence(args.analysis, flags,
                            noSystematics=args.no_systematics,
                            noFilter=args.no_filter)
print(algSeq)
for alg in algSeq:
    job.algsAdd(alg)
    pass
job.outputAdd(ROOT.EL.OutputStream(outputStreamName))
driver.submit(job, args.output_name)

shutil.move(outfile, recofile)
shutil.move(histofile, 'only_reco_histograms.root')

if args.parton:
    job = ROOT.EL.Job()
    job.sampleHandler(sh)
    job.options().setDouble(ROOT.EL.Job.optMaxEvents, maxEvents)
    job.options().setString(ROOT.EL.Job.optSubmitDirMode, 'overwrite')
    if args.text_config:
        from TopCPToolkit.commonAlgoConfig import makeTextBasedSequence
        algSeq = makeTextBasedSequence(args.text_config, 'parton', flags,
                                       noSystematics=args.no_systematics)
    else:
        from TopCPToolkit.commonAlgoConfig import makeTruthSequence
        algSeq = makeTruthSequence(args.analysis, flags,
                                   noSystematics=args.no_systematics)
    print(algSeq)
    for alg in algSeq:
        job.algsAdd(alg)
        pass
    job.outputAdd(ROOT.EL.OutputStream(outputStreamName))
    driver.submit(job, args.output_name)
    shutil.move(outfile, partonfile)

if args.particle:
    job = ROOT.EL.Job()
    job.sampleHandler(sh)
    job.options().setDouble(ROOT.EL.Job.optMaxEvents, maxEvents)
    job.options().setString(ROOT.EL.Job.optSubmitDirMode, 'overwrite')
    if args.text_config:
        from TopCPToolkit.commonAlgoConfig import makeTextBasedSequence
        algSeq = makeTextBasedSequence(args.text_config, 'particle', flags,
                                       noSystematics=args.no_systematics)
    else:
        from TopCPToolkit.commonAlgoConfig import makeParticleLevelSequence
        algSeq = makeParticleLevelSequence(args.analysis, flags,
                                           noSystematics=args.no_systematics)
    print(algSeq)
    for alg in algSeq:
        job.algsAdd(alg)
        pass
    job.outputAdd(ROOT.EL.OutputStream(outputStreamName))
    driver.submit(job, args.output_name)
    shutil.move(outfile, particlefile)

if args.parton and not args.particle:
    os.system(f'hadd -f {finalfile} only_reco_histograms.root {recofile} {partonfile}')
    os.system(f'rm {recofile} {partonfile} only_reco_histograms.root')
elif not args.parton and args.particle:
    os.system(f'hadd -f {finalfile} only_reco_histograms.root {recofile} {particlefile}')
    os.system(f'rm {recofile} {particlefile} only_reco_histograms.root')
elif args.parton and args.particle:
    os.system(f'hadd -f {finalfile} only_reco_histograms.root {recofile} {particlefile} {partonfile}')
    os.system(f'rm {recofile} {partonfile} {particlefile} only_reco_histograms.root')
else:
    os.system(f'hadd -f {finalfile} only_reco_histograms.root {recofile} ')
    os.system(f'rm {recofile} only_reco_histograms.root')
os.system(f'rm -rf {args.output_name}')

##############
## METADATA ##
##############

f = ROOT.TFile(f'{finalfile}', "UPDATE")
h_metadata = ROOT.TH1I('metadata', 'Sample metadata:Look at the bin labels:Number of files in this sample', 3, 0, 3)
h_metadata.GetXaxis().SetBinLabel( 1, str(flags.Input.DataType.value) )
if flags.Input.DataType != DataType.Data:
    campaign = str(flags.Input.MCCampaign.value)
else:
    campaign = str(flags.Input.DataYear)
h_metadata.GetXaxis().SetBinLabel( 2, campaign )
h_metadata.GetXaxis().SetBinLabel( 3, str(flags.Input.MCChannelNumber) )
h_metadata.Write()
f.Close()
