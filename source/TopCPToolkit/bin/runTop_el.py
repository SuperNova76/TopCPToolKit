#!/usr/bin/env python

from AthenaConfiguration.AllConfigFlags import initConfigFlags
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType
from argparse import ArgumentParser
from TopCPToolkit import metaConfig, bishop
import ROOT
import os, shutil

def parse_arguments():
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
                   help='Whether to run parton level')
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
    bishop.warn(args)

    return args

def move_with_symlink_handling(inputfile, outputfile):
    """
    this function allows to move a file that may also be
    just a symlink to a hard output (avoids overwriting symlinks)
    """
    real_source = os.path.realpath(inputfile)
    shutil.move(real_source, outputfile)
    return

def run_job(sample_handler, output_stream_name, level_name, args, flags):
    job = ROOT.EL.Job()
    job.sampleHandler(sample_handler)
    job.options().setBool(ROOT.EL.Job.optAlgorithmMemoryMonitor, False)
    job.options().setDouble(ROOT.EL.Job.optMaxEvents, args.max_events)
    job.options().setString(ROOT.EL.Job.optSubmitDirMode, 'overwrite')
    job.options().setString(ROOT.EL.Job.optFactoryPreload, 'libTopCPToolkitDict.so,top::preloadComponentFactories' )
    if args.text_config:
        from TopCPToolkit.commonAlgoConfig import makeTextBasedSequence
        algSeq = makeTextBasedSequence(args.text_config, level_name, flags,
                                       noSystematics=args.no_systematics)
    else:
        if level_name == 'reco':
            from TopCPToolkit.commonAlgoConfig import makeRecoSequence
            algSeq = makeRecoSequence(args.analysis, flags,
                                      noSystematics=args.no_systematics,
                                      noFilter=args.no_filter)
        elif level_name == 'particle':
            from TopCPToolkit.commonAlgoConfig import makeParticleLevelSequence
            algSeq = makeParticleLevelSequence(args.analysis, flags,
                                               noSystematics=args.no_systematics)
        elif level_name == 'parton':
            from TopCPToolkit.commonAlgoConfig import makeTruthSequence
            algSeq = makeTruthSequence(args.analysis, flags,
                                       noSystematics=args.no_systematics)
    print(algSeq)
    for alg in algSeq:
        job.algsAdd(alg)
    job.outputAdd(ROOT.EL.OutputStream(output_stream_name))
    driver.submit(job, args.output_name)

    return

if __name__ == '__main__':

    args = parse_arguments()

    ROOT.xAOD.Init().ignore()
    sh = ROOT.SH.SampleHandler()
    sh.setMetaString('nc_tree', 'CollectionTree')

    sample_name = 'output' # this thing is used by SampleHandler

    sample = ROOT.SH.SampleLocal(sample_name)
    files = metaConfig.parse_input_filelist(args.input_list)
    for f in files:
        sample.add(f)
    sh.add(sample)

    driver = ROOT.EL.ExecDriver()
    driver.options().setBool(ROOT.EL.Job.optGridReporting, True)

    # read FileMetadata
    flags = initConfigFlags()
    flags.Input.Files = files
    metaConfig.populate_config_flags(flags)
    flags.lock()
    metaConfig.pretty_print(flags)

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

    pid = os.fork()
    if pid:
        os.wait()
        move_with_symlink_handling(outfile, recofile)
        move_with_symlink_handling(histofile, 'only_reco_histograms.root')
    else:
        run_job(sh, outputStreamName, 'reco', args, flags)
    if args.particle:
        pid = os.fork()
        if pid:
            os.wait()
            move_with_symlink_handling(outfile, particlefile)
        else:
            run_job(sh, outputStreamName, 'particle', args, flags)
    if args.parton:
        pid = os.fork()
        if pid:
            os.wait()
            move_with_symlink_handling(outfile, partonfile)
        else:
            run_job(sh, outputStreamName, 'parton', args, flags)

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
