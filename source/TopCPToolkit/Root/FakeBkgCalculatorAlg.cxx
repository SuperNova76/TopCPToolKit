#include "TopCPToolkit/FakeBkgCalculatorAlg.h"

namespace top {

  FakeBkgCalculatorAlg::FakeBkgCalculatorAlg(const std::string &name,
                           ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
  {
    declareProperty("FakeTool"       , m_fake_tool       , "FakeBkgTool you want to use from IFF");
    declareProperty("Definition"     , m_Definition      , "Lepton definition used by FakeBkgTools from IFF.");
    declareProperty("Process"        , m_Process         , "Target process used by FakeBkgTools from IFF.");
  }
  
  StatusCode FakeBkgCalculatorAlg::initialize() {
    ANA_MSG_INFO("Initialising FakeBkgCalculatorAlg");

    ANA_CHECK(m_electronsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_electronSelection.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_electronSelectionTarget.initialize(m_systematicsList, m_electronsHandle));
    ANA_CHECK(m_muonsHandle.initialize(m_systematicsList));
    ANA_CHECK(m_muonSelection.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_muonSelectionTarget.initialize(m_systematicsList, m_muonsHandle));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));
    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_fake_tool_result.initialize(m_systematicsList, m_eventInfoHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
  }

  StatusCode FakeBkgCalculatorAlg::execute() {
      static const SG::AuxElement::Decorator<char> dec_lepton_tight("Tight");
      static const SG::AuxElement::Accessor<char> flagAcc("Tight");

      ANA_MSG_VERBOSE(" ----> FakeBkgCalculatorAlg::execute()");
      for (const auto &sys : m_systematicsList.systematicsVector()) {
        const xAOD::EventInfo *evtInfo = nullptr;
        const xAOD::ElectronContainer *electrons = nullptr;
        const xAOD::MuonContainer *muons = nullptr;

        ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

        m_fake_tool_result.set(*evtInfo, -1, sys); // default value
        if ( m_preselection && !m_preselection.getBool(*evtInfo, sys)) continue;
            
        ANA_CHECK(m_electronsHandle.retrieve(electrons, sys));
        ANA_CHECK(m_muonsHandle.retrieve(muons, sys));

        xAOD::IParticleContainer leptons(SG::VIEW_ELEMENTS);
        for (const xAOD::Electron *t : *electrons) {
          if( m_electronSelection && !m_electronSelection.getBool(*t, sys)) continue;
          leptons.push_back(const_cast<xAOD::Electron*>(t));
          dec_lepton_tight(*leptons.back()) = m_electronSelectionTarget.getBool(*t, sys);
        }
        for (const xAOD::Muon *t : *muons) {
          if( m_muonSelection && !m_muonSelection.getBool(*t, sys)) continue;
          leptons.push_back(const_cast<xAOD::Muon*>(t));
          dec_lepton_tight(*leptons.back()) = m_muonSelectionTarget.getBool(*t, sys);        
        }

        if ( this->msg().level()==MSG::DEBUG || this->msg().level()==MSG::VERBOSE ) {
          for (const xAOD::IParticle *t : leptons)
            ANA_MSG_VERBOSE("lepton type = "<<t->type()<<", pt = "<<t->pt()<<" , eta = "<<t->eta()<<", tight = "<<bool(flagAcc(*t)));
        }

        ANA_CHECK(m_fake_tool->addEvent(leptons));
        float asmWgt = 0.;
        ANA_CHECK(m_fake_tool->applySystematicVariation({})); // the nominal MM weight is computed
        ANA_CHECK(m_fake_tool->getEventWeight(asmWgt, m_Definition, m_Process));
        ANA_MSG_VERBOSE(" ----> asmWgt = "<<asmWgt);
            
        m_fake_tool_result.set(*evtInfo, asmWgt, sys);      
      }
    
      return StatusCode::SUCCESS;
  }
  
}
