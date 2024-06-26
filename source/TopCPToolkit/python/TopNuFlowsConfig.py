from AnalysisAlgorithmsConfig.ConfigBlock import ConfigBlock


class TopNuFlowsConfig(ConfigBlock):
    """ConfigBlock, for the NuFlows Algorithms"""

    def __init__(self) -> None:
        super().__init__()
        self.addOption("btagger", "Dl1dv01", type=str)
        self.addOption("electrons", None, type=str)
        self.addOption("muons", None, type=str)
        self.addOption("jets", None, type=str)
        self.addOption("met", None, type=str)
        self.addOption("eventSelection", None, type=str)

    def makeAlgs(self, config):
        alg = config.createAlgorithm("top::RunNuFlowsAlg", "RunNuFlowsAlg")

        # All the inputs to initialize the algorithm
        alg.btagger = self.btagger
        alg.electrons, alg.electronSelection = config.readNameAndSelection(self.electrons)
        alg.muons, alg.muonSelection = config.readNameAndSelection(self.muons)
        alg.jets, alg.jetSelection = config.readNameAndSelection(self.jets)
        alg.met = config.readName(self.met)
        alg.eventSelection = self.eventSelection

        # Appropriate names for the handles to decorate
        alg.nu_px = "nuflows_nu_px_%SYS%"
        alg.nu_py = "nuflows_nu_py_%SYS%"
        alg.nu_pz = "nuflows_nu_pz_%SYS%"
        alg.anti_nu_px = "nuflows_anti_nu_px_%SYS%"
        alg.anti_nu_py = "nuflows_anti_nu_py_%SYS%"
        alg.anti_nu_pz = "nuflows_anti_nu_pz_%SYS%"
        alg.loglik = "nuflows_loglik_%SYS%"

        # Add the output variables
        config.addOutputVar("EventInfo", alg.nu_px, "nuflows_nu_px")
        config.addOutputVar("EventInfo", alg.nu_py, "nuflows_nu_py")
        config.addOutputVar("EventInfo", alg.nu_pz, "nuflows_nu_pz")
        config.addOutputVar("EventInfo", alg.anti_nu_px, "nuflows_anti_nu_px")
        config.addOutputVar("EventInfo", alg.anti_nu_py, "nuflows_anti_nu_py")
        config.addOutputVar("EventInfo", alg.anti_nu_pz, "nuflows_anti_nu_pz")
        config.addOutputVar("EventInfo", alg.loglik, "nuflows_loglik")
