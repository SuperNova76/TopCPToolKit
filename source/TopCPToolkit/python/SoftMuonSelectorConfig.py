from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

class SoftMuonSelectorConfig(ConfigBlock):
    """Config Block for the SoftMuonSelector Algorithm"""

    def __init__(self):
        super(SoftMuonSelectorConfig, self).__init__()
#        self.addOption('electrons', None, type=str)
#        self.addOption('muons', None, type=str)
        self.addOption('jets', None, type=str)
#        self.addOption('met', None, type=str)
        self.addOption('selection', "", type=str)

#        self.addOption('silliness', False, type=bool)

        self.addOption('softmuons', None, type=str) #Soft muons

        self.addOption('SoftMuonDRJet', None, type=float)

    def makeAlgs(self, config):
##        electrons = config.readName(self.electrons)
##        muons = config.readName(self.muons)
#        jets  = config.readName(self.jets)
##        met   = config.readName(self.met)
#        softmuons = config.readName(self.softmuons) #Soft muons


        alg = config.createAlgorithm('top::SoftMuonSelectorAlg', 'SoftMuonSelectorAlg')

        alg.softmuons, alg.softmuonSelection = config.readNameAndSelection(self.softmuons)
        alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)

##        alg.electrons = electrons
##        alg.muons = muons
#        alg.jets  = jets
##        alg.met   = met
#        alg.softmuons = softmuons #Soft muons
        alg.eventPreselection = self.selection

        # give appropriate names for the handles to decorate
#        alg.SoftMuonJetDRmin     = 'SoftMuonJetDRmin_%SYS%'
#        alg.SoftMuonPassDRJetcut = 'SoftMuonPassDRJetcut_%SYS%'

#        if self.silliness:
#            print("This is a pointless printout that has nothing to do with our tutorial.")

#        config.addOutputVar('EventInfo', 'mtw_%SYS%', 'transverseWmass' )
#        config.addOutputVar(self.jets, 'dphimet_%SYS%', 'deltaPhi_with_met')

        config.addOutputVar(self.softmuons.split('.')[0], 'SoftMuonJetDRmin_%SYS%', 'SoftMuonJetDRmin')
        config.addOutputVar(self.softmuons.split('.')[0], 'SoftMuonPassDRJetcut_%SYS%', 'SoftMuonPassDRJetcut')

        config.addOutputVar('EventInfo', 'pass_SoftMuonPassDRJetcut_%SYS%', 'pass_SoftMuonPassDRJetcut' )
