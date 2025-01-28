#!/usr/bin/env python

# Copyright (C) 2002-2023 CERN for the benefit of the ATLAS collaboration
import GridSubmission.grid
import MC20_PHYS

config = GridSubmission.grid.Config()
config.code          = 'runTop_el.py --no-systematics --reco --particle'  # run nominal only with parton and particle level
config.outputName    = 'tWZ_test' # output directory from EventLoop
config.gridUsername  = 'nsangwen' # use e.g. phys-top or phys-higgs for group production
config.suffix        = '08-Dec-mc20'
config.excludedSites = ''
config.noSubmit      = True # set to True if you just want to test the submission
config.mergeType     = 'Default' #'None', 'Default' or 'xAOD'
config.destSE        = '' #This is the default (anywhere), or try e.g. 'UKI-SOUTHGRID-BHAM-HEP_LOCALGROUPDISK'
# by default the requested memory is set to 2GB, if you need to increase this, see the option below
# config.memory = '4000' # NOTE grid sites with 4GB for single-core user jobs
# are rare
# config.otherOptions = '' # use this to pass any other arguments to prun

names = ['PHYS_tWZ_test_mc20a']
samples = GridSubmission.grid.Samples(names)
GridSubmission.ami.check_sample_status(samples)  # Call with (samples, True) to halt on error
GridSubmission.grid.submit(config, samples)
