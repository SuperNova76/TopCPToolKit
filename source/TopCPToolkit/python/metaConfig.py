from Campaigns.Utils import Campaign
from SimulationConfig.SimEnums import SimulationFlavour
from AthenaConfiguration.Enums import LHCPeriod
from PathResolver import PathResolver
from AnalysisAlgorithmsConfig.ConfigAccumulator import DataType

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
    2022: 'GoodRunsLists/data22_13p6TeV/20230207/data22_13p6TeV.periodAllYear_DetStatus-v109-pro28-04_MERGED_PHYS_StandardGRL_All_Good_25ns.xml',
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


def populate_config_flags(flags, metadata):
    """
    Populate additional information in the AllConfigFlags from FileMetaData
    """
    flags.addFlag('Input.AMITag', metadata.get('AMITag', ''))
    if len(flags.Input.RunNumber) != 1:
        print('WARNING (metaConfig.populate_config_flags): FileMetaData reports RunNumber list '
              f'with not exactly 1 entry: {flags.Input.RunNumber}')
    flags.addFlag('Input.RunNumberAsInt', int(flags.Input.RunNumber[0]))
    flags.addFlag('Input.DataType', get_data_type)
    is_data = (flags.Input.DataType is DataType.Data)
    if not is_data:
        # try a fallback solution to determine MC campaign
        # this is for samples, that don't include the MCCampaign entry in FileMetaData
        # this problem should be fixed in p58XX tags
        if flags.Input.MCCampaign == Campaign.Unknown:
            flags.Input.MCCampaign = get_campaign_fallback
    flags.addFlag('Input.LHCPeriod', get_LHCgeometry)
    flags.addFlag('Input.isRun3', isRun3)
    flags.addFlag('Input.isPHYSLITE', isPhysLite)
    flags.addFlag('Analysis.FTAGMCMCGenerator',
                  'default' if is_data else get_generator_FTAG)
    flags.addFlag('Analysis.JESMCMCGenerator',
                  'default' if is_data else get_generator_JES)


def get_data_type(flags):
    if not flags.Input.isMC:
        return DataType.Data
    else:
        if flags.Sim.ISF.Simulator.isFullSim():
            return DataType.FullSim
        elif flags.Sim.ISF.Simulator.usesFastCaloSim():
            return DataType.FastSim
        else:
            raise Exception('Could not determine data_type, '
                            'perhaps SimulationFlavour metadata is missing')


def get_campaign_fallback(flags):
    """
    In case MC Campaign is not stored in FileMetaData, we can try to figure it out from AMI tag.
    """
    amiTags = flags.Input.AMITag
    if amiTags == '':
        print('WARNING (metaConfig.get_campaign): AMITag entry in FileMetaData '
                'appears to be empty or does not exist')

    for (cmp, tagsList) in _campaigns_AMITag.items():
        for tag in tagsList:
            if tag in amiTags:
                print('metaConfig.get_campaign: Auto-detected campaign ', cmp)
                return cmp
    raise Exception(f'AMITag {amiTags} in FileMetaData does not correspond to any implemented campaign')


def get_data_year(flags):
    """
    Try to determine the year of data-taking based on runNumber.
    """
    if flags.Input.RunNumberAsInt == 0:
        print('ERROR (metaConfig.get_data_year): runNumber == 0, we cannot determine data year reliably.')
    for (year, runRange) in _years_runNumbers.items():
        if flags.Input.RunNumberAsInt >= runRange[0] and flags.Input.RunNumberAsInt < runRange[1]:
            return year
    print(f'WARNING (metaConfig.get_data_year): runNumber {flags.Input.RunNumberAsInt} '
          'does not correspond to any of the defined years of data taking!')
    return 0

def isPhysLite(flags):
    """
    Check whether the derivation format is PHYSLITE.
    """
    if flags.Input.ProcessingTags is not None:
        return 'StreamDAOD_PHYSLITE' in flags.Input.ProcessingTags
    else:
        print('WARNING Could not find any information about the sample being PHYSLITE '
              'in the metadata. Will assume that it was regular PHYS.')
    return False

def isRun3(flags):
    if flags.Input.DataType is DataType.Data:
        year = get_data_year(flags)
        return (year >= 2022)
    else:
        cmp = flags.Input.MCCampaign
        return (cmp in _campaigns_R3)


def get_LHCgeometry(flags):
    if isRun3(flags):
        return LHCPeriod.Run3
    else:
        return LHCPeriod.Run2


def get_grl(flags):
    year = get_data_year(flags)
    try:
        return _year_GRL[year]
    except KeyError:
        raise Exception(f'Unrecognized year for GRL {year}')


def get_generator_info(flags):
    result = ['default', 'default'] # FTAG MC-MC, JES flavour
    if flags.Input.MCChannelNumber == 0:
        print('WARNING: Unable to get generator information from inputfiles.')
    if flags.Input.isRun3:
        tdpFile = 'dev/AnalysisTop/TopDataPreparation/XSection-MC21-13p6TeV.data'
    else:
        tdpFile = 'dev/AnalysisTop/TopDataPreparation/XSection-MC16-13TeV_JESinfo.data'
    with open(PathResolver.FindCalibFile(tdpFile), 'r') as _f:
        for line in _f:
            if not line.strip() or line.startswith('#'):
                continue
            columns = line.split()
            if columns[0].isdigit() and int(columns[0]) == flags.Input.MCChannelNumber:
                if len(columns) == 5:
                    # we have both FTAG and JES
                    result[0] = columns[-2].strip()
                    result[1] = columns[-1].strip()
                elif len(columns) == 4:
                    # we have only FTAG
                    result[0] = columns[-1].strip()
    return result


def get_generator_FTAG(flags):
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
        result = tdpTranslation[get_generator_info(flags)[0]]
        return result
    except KeyError:
        raise Exception('Unrecognised FTAG MC-to-MC generator setup {}, aborting.'.format(get_generator_info(flags)[0]))


def get_generator_JES(flags):
    return get_generator_info(flags)[1]
