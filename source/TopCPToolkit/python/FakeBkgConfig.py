from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class FakeBkgConfig(ConfigBlock):
    """ConfigBlock for the FakeBkgTools Calculator algorithm"""

    def __init__(self, algoName=''):
        super(FakeBkgConfig, self).__init__('FakeBkgConfig' + algoName)
        self.algoName = algoName
        self.addOption('electrons', None, type=str)
        self.addOption('electronsTarget', None, type=str)
        self.addOption('muons', None, type=str)
        self.addOption('muonsTarget', None, type=str)
        self.addOption('eventPreselection', '', type=str)    
        self.addOption('fakeTool', '', type=str)    
        self.addOption('config', '', type=str)    
        self.addOption('process', '', type=str)    
        self.addOption('definition', '', type=str)

    def makeAlgs(self, config):
        alg = config.createAlgorithm('top::FakeBkgCalculatorAlg', 'FakeBkgCalculatorAlg_' + self.algoName)
       
        alg.electrons, alg.electronSelection = config.readNameAndSelection(self.electrons)
        alg.electronSelectionTarget = config.getFullSelection(self.electrons.split(".")[0], self.electronsTarget)
        alg.muons, alg.muonSelection = config.readNameAndSelection(self.muons)
        alg.muonSelectionTarget = config.getFullSelection(self.muons.split(".")[0], self.muonsTarget)
            
        alg.eventPreselection = self.eventPreselection
        alg.Process = self.process
        alg.Definition = self.definition

        config.addPrivateTool('FakeTool', self.fakeTool)
        from PathResolver import PathResolver
        alg.FakeTool.InputFiles = [PathResolver.FindCalibFile(self.config)]
        alg.FakeTool.Process = self.process
        alg.FakeTool.Selection = self.definition
        alg.FakeTool.EnergyUnit = 'GeV'
        alg.FakeTool.ConvertWhenMissing = True

        alg.FakeToolResult = 'FakeToolResult_' + self.algoName + '_%SYS%'
        config.addOutputVar('EventInfo', alg.FakeToolResult, 'weight_fake_' + self.algoName, noSys=True)
