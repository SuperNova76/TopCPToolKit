from AnaAlgorithm.DualUseConfig import createAlgorithm, addPrivateTool
from AnaAlgorithm.AnaAlgSequence import AnaAlgSequence
from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock

particlelevel_branch_mappings = {
    "electrons": [
        'pt_dressed               -> pt',
        'eta_dressed              -> eta',
        'phi_dressed              -> phi',
        'e                        -> e',
        'charge                   -> charge',
        'classifierParticleType   -> type',
        'classifierParticleOrigin -> origin',
    ],
    "muons": [
        'pt_dressed               -> pt',
        'eta_dressed              -> eta',
        'phi_dressed              -> phi',
        'e                        -> e',
        'charge                   -> charge',
        'classifierParticleType   -> type',
        'classifierParticleOrigin -> origin',
    ],
    "photons": [
        'pt                       -> pt',
        'eta                      -> eta',
        'phi                      -> phi',
        'e                        -> e',
        'classifierParticleType   -> type',
        'classifierParticleOrigin -> origin',
    ],
    "taus": [
        'pt                       -> pt',
        'eta                      -> eta',
        'phi                      -> phi',
        'e                        -> e',
        'classifierParticleType   -> type',
        'classifierParticleOrigin -> origin',
        'IsHadronicTau            -> IsHadronicTau',
    ],
    "jets": [
        'pt                       -> pt',
        'eta                      -> eta',
        'phi                      -> phi',
        'e                        -> e',
        'GhostBHadronsFinalCount  -> nGhosts_bHadron',
        'GhostCHadronsFinalCount  -> nGhosts_cHadron',
    ],
    "ljets": [
        'pt                       -> pt',
        'eta                      -> eta',
        'phi                      -> phi',
        'e                        -> e',
        'GhostBHadronsFinalCount  -> nGhosts_bHadron',
    ],
    "met": [
        'met_met                  -> met',
        'met_phi                  -> phi',
    ],
}

class particleLevelConfig(ConfigBlock):
    """ConfigBlock for particle-level objects"""

    def __init__(self):
        super(particleLevelConfig, self).__init__('particleLevel')
        self.addOption('useTruthElectrons', True, type=bool)
        self.addOption('useTruthMuons', True, type=bool)
        self.addOption('useTruthPhotons', False, type=bool)
        self.addOption('useTruthTaus', False, type=bool)
        self.addOption('useTruthJets', True, type=bool)
        self.addOption('useTruthLargeRJets', False, type=bool)
        self.addOption('useTruthMET', True, type=bool)
        self.addOption('doOverlapRemoval', True, type=bool)
    
    def makeAlgs(self, config):
        alg = config.createAlgorithm("top::ParticleLevelAlg", "TopParticleLevel")
        alg.useTruthElectrons  = self.useTruthElectrons
        alg.useTruthMuons      = self.useTruthMuons
        alg.useTruthPhotons    = self.useTruthPhotons
        alg.useTruthTaus       = self.useTruthTaus
        alg.useTruthJets       = self.useTruthJets
        alg.useTruthLargeRJets = self.useTruthLargeRJets
        alg.useTruthMET        = self.useTruthMET
        alg.doOverlapRemoval   = self.doOverlapRemoval

        if self.useTruthElectrons:
            container = "ParticleLevelElectrons"
            config = self.createAndFillOutputContainer(config, container, "electrons")
        if self.useTruthMuons:
            container = "ParticleLevelMuons"
            config = self.createAndFillOutputContainer(config, container, "muons")
        if self.useTruthPhotons:
            container = "ParticleLevelPhotons"
            config = self.createAndFillOutputContainer(config, container, "photons")
        if self.useTruthTaus:
            container = "ParticleLevelTaus"
            config = self.createAndFillOutputContainer(config, container, "taus")
        if self.useTruthJets:
            container = "ParticleLevelJets"
            config = self.createAndFillOutputContainer(config, container, "jets")
        if self.useTruthLargeRJets:
            container = "ParticleLevelLargeRJets"
            config = self.createAndFillOutputContainer(config, container, "ljets")
        if self.useTruthMET:
            container = "ParticleLevelMissingET"
            config = self.createAndFillOutputContainer(config, container, "met", True)

        return
    
    def createAndFillOutputContainer(self, config, container, map_key, isMET=False):
        # create the output container for that object collection
        if not isMET:
            config.setSourceName(container, container)
            config.addOutputContainer(container, container)
        else:
            _ = config.writeName(container, isMet=True)

        # loop over branch mappings
        for mapping in particlelevel_branch_mappings[map_key]:
            inputname  = mapping.split("->")[0].rstrip()
            outputname = mapping.split("->")[1].lstrip()
            config.addOutputVar(container, inputname, outputname, noSys=True)
        
        return config
    
    def getOutputContainers(self):
        # return a dictionary of containers that can be added to the OutputAnalysisConfig
        containerDict = {}
        if self.useTruthElectrons:
            containerDict['el_']   = 'ParticleLevelElectrons'
        if self.useTruthMuons:
            containerDict['mu_']   = 'ParticleLevelMuons'
        if self.useTruthPhotons:
            containerDict['ph_']   = 'ParticleLevelPhotons'
        if self.useTruthTaus:
            containerDict['tau_']  = 'ParticleLevelTaus'
        if self.useTruthJets:
            containerDict['jet_']  = 'ParticleLevelJets'
        if self.useTruthLargeRJets:
            containerDict['ljet_'] = 'ParticleLevelLargeRJets'
        if self.useTruthMET:
            containerDict['met_']  = 'ParticleLevelMissingET'

        return containerDict
