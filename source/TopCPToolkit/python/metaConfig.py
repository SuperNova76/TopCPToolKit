from Campaigns.Utils import Campaign
from AthenaConfiguration.Enums import LHCPeriod

_campaigns_AMITag = {
    Campaign.MC20a: 'r13167',
    Campaign.MC20d: 'r13144',
    Campaign.MC20e: 'r13145',
    Campaign.MC21a: 'r13829',
    Campaign.MC23a: 'r14622',
    Campaign.MC23c: 'r14799',
}

_campaigns_R2 = [
    Campaign.MC20a, Campaign.MC20d, Campaign.MC20e
]

_campaigns_R3 = [
    Campaign.MC21a, Campaign.MC23a, Campaign.MC23c
]

_campaign_GRL = {
    Campaign.MC20a: [
        'GoodRunsLists/data15_13TeV/20170619/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml',
        'GoodRunsLists/data16_13TeV/20180129/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml'
    ],
    Campaign.MC20d: ['GoodRunsLists/data17_13TeV/20180619/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml'],
    Campaign.MC20e: ['GoodRunsLists/data18_13TeV/20190318/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml'],
    Campaign.MC21a: ['GoodRunsLists/data22_13p6TeV/20221123/data22_13p6TeV.periodFH_DetStatus-v108-pro28-01_MERGED_PHYS_StandardGRL_All_Good_25ns.xml'],
    Campaign.MC23a: ['GoodRunsLists/data22_13p6TeV/20221123/data22_13p6TeV.periodFH_DetStatus-v108-pro28-01_MERGED_PHYS_StandardGRL_All_Good_25ns.xml'],
    Campaign.MC23c: ['GoodRunsLists/data23_13p6TeV/20230712/data23_13p6TeV.periodAllYear_DetStatus-v110-pro31-05_MERGED_PHYS_StandardGRL_All_Good_25ns.xml']
}

def parse_input_filelist(path):
    """
    Read input files from text file.
    We support files per-line, but also comma-separated (prun does that...)
    """
    files = []
    fin = open(path, 'r')
    for line in fin.readlines():
        files += line.split(',')
    for i, f in enumerate(files):
        files[i] = f.strip()
    fin.close()
    return files


def get_data_type(fmd):
    """
    Check from FileMetaData what kind of dataset is this.
    Return if this is data or mc or afii
    NOTE: In general expect this to get more complicated as we start
    distinguishing different types of fast/fullsim/data overlay, etc
    """
    # TODO the actual treatment of various simulation types expected to evolve...
    try:
        simFlavour = fmd['SimulationFlavour']
        if 'FullG4' in simFlavour:
            data_type = 'mc'
        elif 'ATLFAST3' in simFlavour:
            data_type = 'afii'
    except KeyError:
        data_type = 'data'
    return data_type


def get_campaign(fmd):
    try:
        amiTags = fmd['AMITag']
    except KeyError:
        print('ERROR: This datasets\' FileMetaData does not contain AMITag.')
        print('       We cannot figure out MC campaign.')
        raise

    for cmp in _campaigns_AMITag.items():
        if cmp[1] in amiTags:
            return cmp[0]
    raise Exception(f'AMITag {amiTags} in FileMetaData does not correspond to any implemented campaign')


def isRun3(campaign):
    try:
        _campaigns_AMITag[campaign]
    except KeyError:
        raise Exception(f'Unrecognized campaign {campaign}')
    return (campaign in _campaigns_R3)

def get_LHCgeometry(campaign):
    if campaign in _campaigns_R2:
        return LHCPeriod.Run2
    elif campaign in _campaigns_R3:
        return LHCPeriod.Run3
    else:
        raise Exception(f'Unrecognized campaign {campaign}')

def get_grl(campaign):
    try:
        return _campaign_GRL[campaign]
    except KeyError:
        raise Exception(f'Unrecognized campaign {campaign}')


def get_mc_run_number(fmd):
    try:
        runNumbers = fmd['runNumbers']
        if len(runNumbers) > 1:
            print(f'WARNING: Got {len(runNumbers)} runNumbers, expecting only one.')
        return runNumbers[0]
    except KeyError:
        print('WARNING: Got no runNumber from input files. This could be '
              'an indication that none of the files have any events.')
    return 0

def get_mc_channel_number(fmd):
    try:
        mcChannelNumber = fmd['mc_channel_number']
        return mcChannelNumber
    except KeyError:
        print('WARNING: Got no mcProcID from inputfiles. This could be '
              'an indication that none of the files have any events/')
    return 0
