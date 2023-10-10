from Campaigns.Utils import Campaign
from AthenaConfiguration.Enums import LHCPeriod
from PathResolver import PathResolver

_campaigns_AMITag = {
    # NOTE this is a "fallback" approach to read campaign based on standard r-tag with pile-up for
    # MC campaigns. For non-standard reconstruction, extra r-tags have to be added here to be recognized.
    # Recommended approach is to read mc_campaign from FileMetaData (seems to require reasonably recent p-tags)
    Campaign.MC20a: ['r13167'],
    Campaign.MC20d: ['r13144'],
    Campaign.MC20e: ['r13145'],
    Campaign.MC21a: ['r13829'],
    Campaign.MC23a: ['r14622'],
    Campaign.MC23c: ['r14799'],
}

_years_runNumbers = {
    # for each year (dict key), provide list of [min runNumber, max runNumber)
    # i.e. we check min runNumber <= runNumber < max runNumber 
    2015: [0, 290000],
    2016: [290000, 320000],
    2017: [320000, 342000],
    2018: [342000, 400000],
    2022: [410000, 450000],
    2023: [450000, 999999]
}

_campaigns_R2 = [
    Campaign.MC20a, Campaign.MC20d, Campaign.MC20e
]

_campaigns_R3 = [
    Campaign.MC21a, Campaign.MC23a, Campaign.MC23c,
]

_year_GRL = {
    2015: 'GoodRunsLists/data15_13TeV/20170619/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml',
    2016: 'GoodRunsLists/data16_13TeV/20180129/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml',
    2017: 'GoodRunsLists/data17_13TeV/20180619/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml',
    2018: 'GoodRunsLists/data18_13TeV/20190318/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml',
    2022: 'GoodRunsLists/data22_13p6TeV/20221123/data22_13p6TeV.periodFH_DetStatus-v108-pro28-01_MERGED_PHYS_StandardGRL_All_Good_25ns.xml',
    2023: 'GoodRunsLists/data23_13p6TeV/20230712/data23_13p6TeV.periodAllYear_DetStatus-v110-pro31-05_MERGED_PHYS_StandardGRL_All_Good_25ns.xml'
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


def get_data_type(metadata):
    """
    Check from FileMetaData what kind of dataset is this.
    Return if this is data or mc or afii
    NOTE: In general expect this to get more complicated as we start
    distinguishing different types of fast/fullsim/data overlay, etc
    """
    # TODO the actual treatment of various simulation types expected to evolve...
    eventTypes = metadata.get('eventTypes', None)
    if eventTypes:
        if 'IS_DATA' in eventTypes:
            data_type = 'data'
        elif 'IS_SIMULATION' in eventTypes:
            data_type = get_simulation_type(metadata)
    else:
        # fallback if eventTypes is not filled,
        # we try to guess if it's data from SimulationFlavour being None
        print('metaConfig.get_data_type: Did not find eventTypes in FileMetaData, '
              'trying to determine the data type using SimulationFlavour')
        return get_simulation_type(metadata)
    return data_type


def get_simulation_type(metadata):
    """
    Check SimulationFlavour from FileMetaData.
    NOTE that this can still be data sample, denoted by SimulationFlavour == None.
    """
    try:
        simFlavour = metadata['SimulationFlavour']
        if simFlavour is None:
            data_type = 'data'
        elif 'FullG4' in simFlavour:
            data_type = 'mc'
        elif 'ATLFAST3' in simFlavour:
            data_type = 'afii'
    except KeyError:
        raise Exception('Cannot retrieve SimulationFlavour from FileMetaData!')
    return data_type
        

def get_campaign(metadata):
    # first try to read mc_campaign entry from FMD
    # it seems to not be present either in old p-tags or samples before mc23 (?)
    mc_campaign = metadata.get('mc_campaign', None)
    if mc_campaign is not None:
        return Campaign(mc_campaign)
    else:
        try:
            amiTags = metadata['AMITag']
        except KeyError:
            print('ERROR (metaConfig.get_campaign): This datasets\' FileMetaData '
                  'does not contain AMITag. We cannot figure out MC campaign.')
            raise

        for (cmp, tagsList) in _campaigns_AMITag.items():
            for tag in tagsList:
                if tag in amiTags:
                    print('metaConfig.get_campaign: Auto-detected campaign ', cmp)
                    return cmp
        raise Exception(f'AMITag {amiTags} in FileMetaData does not correspond to any implemented campaign')


def get_data_year(metadata):
    """
    Try to determine the year of data-taking based on runNumber.
    """
    runNumber = get_run_number(metadata)
    if runNumber == 0:
        print('ERROR (metaConfig.get_data_year): runNumber == 0, we cannot determine data year reliably.')
    for (year, runRange) in _years_runNumbers.items():
        if runNumber >= runRange[0] and runNumber < runRange[1]:
            return year
    print(f'WARNING (metaConfig.get_data_year): runNumber {runNumber} '
          'does not correspond to any of the defined years of data taking!')
    return 0

def isPhysLite(metadata):
    """
    Check whether the derivation format is PHYSLITE.
    """
    processingTags = metadata.get('processingTags', None)
    if processingTags is not None:
        return 'StreamDAOD_PHYSLITE' in processingTags
    else:
        try:
            check = metadata['metadata_items']['StreamDAOD_PHYSLITE']
            return True
        except:
            print('WARNING Could not find any information about the sample being PHYSLITE in the metadata... Will assume that it was regular PHYS.')
    return False

def isRun3(metadata):
    data_type = get_data_type(metadata)
    if data_type == 'data':
        year = get_data_year(metadata)
        return (year >= 2022)
    else:
        cmp = get_campaign(metadata)
        return (cmp in _campaigns_R3)


def get_LHCgeometry(metadata):
    if isRun3(metadata):
        return LHCPeriod.Run3
    else:
        return LHCPeriod.Run2


def get_grl(metadata):
    year = get_data_year(metadata)
    try:
        return _year_GRL[year]
    except KeyError:
        raise Exception(f'Unrecognized year for GRL {year}')


def get_run_number(metadata):
    try:
        runNumbers = metadata['runNumbers']
        if len(runNumbers) > 1:
            print(f'WARNING: Got {len(runNumbers)} runNumbers, expecting only one.')
        return runNumbers[0]
    except KeyError:
        print('WARNING: Got no runNumber from input files. This could be '
              'an indication that none of the files have any events.')
    return 0


def get_mc_channel_number(metadata):
    try:
        mcChannelNumber = metadata['mc_channel_number']
        return mcChannelNumber
    except KeyError:
        print('WARNING: Got no mcProcID from inputfiles. This could be '
              'an indication that none of the files have any events/')
    return 0


def get_generator_info(metadata):
    result = ['default', 'default'] # FTAG MC-MC, JES flavour
    dsid = get_mc_channel_number(metadata)
    if dsid == 0:
        print('WARNING: Unable to get generator information from inputfiles.')
    if isRun3(metadata):
        tdpFile = 'dev/AnalysisTop/TopDataPreparation/XSection-MC21-13p6TeV.data'
    else:
        tdpFile = 'dev/AnalysisTop/TopDataPreparation/XSection-MC16-13TeV_JESinfo.data'
    with open(PathResolver.FindCalibFile(tdpFile), 'r') as _f:
        for line in _f:
            if not line.strip() or line.startswith('#'):
                continue
            columns = line.split()
            if columns[0].isdigit() and int(columns[0]) == dsid:
                if len(columns) == 5:
                    # we have both FTAG and JES
                    result[0] = columns[-2].strip()
                    result[1] = columns[-1].strip()
                elif len(columns) == 4:
                    # we have only FTAG
                    result[0] = columns[-1].strip()
    return result


def get_generator_FTAG(metadata):
    # we have to translate between what's in TDP and what's expected by FTAG
    # https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/TopPhys/TopPhysUtils/TopDataPreparation/Root/SampleXsection.cxx#0150
    # https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/FTagAnalysisAlgorithms/python/FTagAnalysisConfig.py
    # https://twiki.cern.ch/twiki/bin/view/AtlasProtected/BTagRecommendationsRelease22#Calibration_pre_recommendations
    tdpTranslation = {
        'herwig': 'Herwig7',
        'herwigpp': 'Herwig7',
        'pythia8': 'default',
        'sherpa': 'Sherpa221',
        'sherpa21': 'Sherpa221',
        'amcatnlopythia8': 'amcAtNLOPythia',
        'herwigpp713': 'Herwig713',
        'sherpa228': 'Sherpa228',
        'sherpa2210': 'Sherpa2210',
        'sherpa2212': 'Sherpa2212',
        'herwigpp721': 'Herwig721',
    }
    try:
        result = tdpTranslation[get_generator_info(metadata)[0]]
        return result
    except KeyError:
        raise Exception('Unrecognised FTAG MC-to-MC generator setup {}, aborting.'.format(get_generator_info(metadata)[0]))


def get_generator_JES(metadata):
    return get_generator_info(metadata)[1]
