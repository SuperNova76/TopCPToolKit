from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class TtbarNNLORecursiveRewConfig(ConfigBlock):
    """ConfigBlock for ttbar NNLO reweighting algorithms"""

    def __init__(self, mcChannelNumber, datatype, isRun3Geo=False):
        super(TtbarNNLORecursiveRewConfig, self).__init__('RunTtbarNNLORecursiveRewAlg')
        self.mcChannelNumber = mcChannelNumber
        self.datatype = datatype
        self.isRun3 = isRun3Geo
        self.addOption('sampleID', 'AutoConfig', type=str)
        self.addOption('reweightType', '2D', type=str)
        self.addOption('reweightPath', 'dev/AnalysisTop/TTbarNNLOReweighter', type=str)
        self.addOption('reweightSuffix', '_3iter_2023_LUX', type=str)

    def makeAlgs(self, config):
        # don't run on data!
        if self.datatype == 'data':
            return
        
        if self.isRun3:
            print("Run 3 NNLO ttbar reweighting is not supported yet! skipping the algorithm.")
            return
        
        # internal mapping for the tool
        map_sampleID = {
           "Nominal" : [410470],
           "PH7new": [],
           "aMCH7": [],
           "PH7": [],
           "aMCP8": [],
           "PP8hdamp": [],
           "PP8muRup": [],
           "PP8muRdown": [],
           "PP8muFup": [],
           "PP8muFdown": [],
           "PP8FSRup": [],
           "PP8FSRdown": [],
           "PP8pthard1": [],
           "MECoff": [],
        }
        if self.sampleID == 'AutoConfig':
            for key, value in map_sampleID.items():
                if self.mcChannelNumber in value:
                    self.sampleID = key
                    break
            else:
                # this sample is not supported for reweighting:
                # simply don't set up the algorithm
                print("Sample with DSID", self.mcChannelNumber, "is not supported for ttbar NNLO reweighting, skipping the algorithm.")
                return

        alg = config.createAlgorithm('top::RunTtbarNNLORecursiveRewAlg', 'RunTtbarNNLORecursiveRewAlg'+self.reweightType)
        alg.sampleID = self.sampleID
        alg.reweightingType = self.reweightType
        alg.reweightingPath = self.reweightPath
        alg.reweightingSuffix = self.reweightSuffix

        # give appropriate names for the handles to decorate
        alg.NNLO_weight = 'NNLO_'+self.reweightType+'_weight_%SYS%'
        config.addOutputVar('EventInfo', alg.NNLO_weight, 'weight_NNLO_'+self.reweightType)
