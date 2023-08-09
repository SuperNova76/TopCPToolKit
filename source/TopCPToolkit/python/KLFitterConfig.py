from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class KLFitterConfig(ConfigBlock):
    """ConfigBlock for KLFitter algorithms"""

    def __init__(self, containerName):
        super(KLFitterConfig, self).__init__(containerName)
        self.containerName = containerName
        self.addOption('electrons', '', type=str)
        self.addOption('muons', '', type=str)
        self.addOption('jets', '', type=str)
        self.addOption('met', '', type=str)
        self.addOption('likelihoodType', '', type=str)
        self.addOption('leptonType', '', type=str)
        self.addOption('jetSelectionMode', '', type=str)
        self.addOption('btaggingMethod', 'kNoTag', type=str)
        self.addOption('bTagCDIFile',
                       'xAODBTaggingEfficiency/13TeV/2022-22-13TeV-MC20-CDI-2022-07-28_v1.root', type=str)
        self.addOption('btagger', 'DL1dv00', type=str)
        self.addOption('btagWP', 'FixedCutBEff_77', type=str)
        self.addOption('selectionRegionsConfig', '', type=str)
        self.addOption('saveAllPermutations', False, type=bool)
        # list of dictionaries for the per-region config options
        self.perRegionConfiguration = list()

    def parseSelectionRegionsConfig(self):
        regions = self.selectionRegionsConfig.split(';')
        if len(regions) == 0:
            raise Exception('KLFitterConfig: Could not determine any regions in your SelectionRegionsConfig')
        for reg in regions:
            regstrip = reg.replace(' ', '')
            regionopts = dict(tuple(option.split(':')) for option in regstrip.split(','))
            try:
                regionopts['selectionName']
            except KeyError:
                raise Exception('KLFitterConfig: Could not parse SelectionRegionsConfig selectionName for region ', reg)

            self.perRegionConfiguration.append(regionopts)

    def makeAlgs(self, config):
        self.parseSelectionRegionsConfig()
        for perRegionConfig in self.perRegionConfiguration:
            selectionName = perRegionConfig['selectionName']
            alg = config.createAlgorithm('top::KLFitterAlg',
                                         'KLFitterAlg_' + selectionName)
            # input objects and their object selections
            alg.electrons, alg.electronSelection = config.readNameAndSelection(self.electrons)
            alg.muons, alg.muonSelection = config.readNameAndSelection(self.muons)
            alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
            alg.met = config.readName(self.met)

            # global settings, in future expect to expose more options for configuration
            alg.SaveAllPermutations = self.saveAllPermutations

            # these settings can be defined per-region, but if not, we fallback to global setting
            alg.selectionDecorationName = selectionName + '_%SYS%'
            alg.LHType = perRegionConfig.get('likelihoodType', self.likelihoodType)
            alg.LeptonType = perRegionConfig.get('leptonType', self.leptonType)
            alg.JetSelectionMode = perRegionConfig.get('jetSelectionMode', self.jetSelectionMode)
            btagAlgo = perRegionConfig.get('btagger', self.btagger)
            btagWP = perRegionConfig.get('btagWP', self.btagWP)
            alg.BTaggingDecoration = f'ftag_select_{btagAlgo}_{btagWP}'

            if perRegionConfig.get('btaggingMethod', self.btaggingMethod) == 'kWorkingPoint':
                config.addPrivateTool('BTaggingEfficiencyTool', 'BTaggingEfficiencyTool')
                alg.BTaggingEfficiencyTool.TaggerName = self.btagger
                alg.BTaggingEfficiencyTool.OperatingPoint = self.btagWP
                jetCollection = config.originalName(self.jets.split('.')[0])
                alg.BTaggingEfficiencyTool.JetAuthor = jetCollection
                alg.BTaggingEfficiencyTool.ScaleFactorFileName = self.bTagCDIFile
                alg.BTaggingEfficiencyTool.MinPt = 20e3  # hardcoded to the recommendation for EMPFlow at the moment
                # NOTE the efficiency tool is simply set to the default generator,
                # meaning the results are not correct for alternative showering generators!!

        finalizeAlg = config.createAlgorithm('top::KLFitterFinalizeOutputAlg', 'KLFitterFinalizeOutputAlg')

        config.setSourceName(self.containerName, self.containerName)
        config.addOutputContainer(self.containerName, self.containerName + '_%SYS%')

        config.addOutputVar(self.containerName, 'eventProbability', 'eventProbability')
        config.addOutputVar(self.containerName, 'logLikelihood', 'logLikelihood')
        if self.saveAllPermutations:
            config.addOutputVar(self.containerName, 'selected', 'selected')
