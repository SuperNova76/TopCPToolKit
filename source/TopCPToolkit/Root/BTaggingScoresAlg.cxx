/// @author Diego Baron

#include "TopCPToolkit/BTaggingScoresAlg.h"
#include "xAODBTagging/BTagging.h"
#include "xAODBTagging/BTaggingUtilities.h"

BTaggingScoresAlg::BTaggingScoresAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
    , m_saveAllProbabilities(true)
    , m_taggerName("GN2v00LegacyWP")
    , m_btagging_sel_tool("", this)
{
  declareProperty("selectionTool", m_btagging_sel_tool, "BTaggingSelectionTool to account for b-/light- tagging");
  declareProperty("saveAllProbabilities", m_saveAllProbabilities, "Save the individual jet type probabilities");
  declareProperty("taggerName", m_taggerName, "Name of the b-tagging alrogithm to extract info from");
}

StatusCode BTaggingScoresAlg::initialize()
{
    ANA_MSG_INFO("Initializing BTaggingScoresAlg " << name());

    // Input handles
    ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));

    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    ANA_CHECK(m_btagging_sel_tool.retrieve());

    // Output decorations
    ANA_CHECK(m_btagScore_decor.initialize(m_systematicsList, m_jetsHandle));
    ANA_CHECK(m_probBottom_decor.initialize(m_systematicsList, m_jetsHandle));
    ANA_CHECK(m_probCharm_decor.initialize(m_systematicsList, m_jetsHandle));
    ANA_CHECK(m_probLight_decor.initialize(m_systematicsList, m_jetsHandle));

    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
}

StatusCode BTaggingScoresAlg::execute()
{
  for (const auto &sys : m_systematicsList.systematicsVector())
  { 

    // retrieve the EventInfo
    const xAOD::EventInfo *evtInfo = nullptr;
    ANA_CHECK(m_eventInfoHandle.retrieve(evtInfo, sys));

    // check the preselection
    if (m_preselection && !m_preselection.getBool(*evtInfo, sys))
      continue;

    // retrieve objects
    const xAOD::JetContainer *jets = nullptr;
    ANA_CHECK(m_jetsHandle.retrieve(jets, sys));

    for(const xAOD::Jet* jet : *jets)
    {
        //Get the b-tagger score
        double tagweight(-100.);
        if( m_btagging_sel_tool->getTaggerWeight( *jet ,tagweight)!=CP::CorrectionCode::Ok) { 
          ANA_MSG_ERROR (" error retrieving tagger weight! " );
          return StatusCode::FAILURE;
        }
        //if you have tagger weights, you can get the tagger weight this way
        const xAOD::BTagging *btag = xAOD::BTaggingUtilities::getBTagging( *jet );

        std::string EDMTaggerName;
        if (m_taggerName.find("GN2v00") != std::string::npos) {
          EDMTaggerName = "GN2v00";
        } else {
          EDMTaggerName = m_taggerName;
        }


        float jet_pb(-1.);
        float jet_pc(-1.);
        float jet_pl(-1.);
        if(m_saveAllProbabilities)
        {
          jet_pb = btag->auxdata<float>(EDMTaggerName + "_pb");
          jet_pc = btag->auxdata<float>(EDMTaggerName + "_pc");
          jet_pl = btag->auxdata<float>(EDMTaggerName + "_pu");
        }

        // save the decorations
        m_btagScore_decor.set(*jet, tagweight, sys);
        if(m_saveAllProbabilities)
        {
          m_probBottom_decor.set(*jet, jet_pb, sys);
          m_probCharm_decor.set(*jet, jet_pc, sys);
          m_probLight_decor.set(*jet, jet_pl, sys);
        }
    }

  }
  return StatusCode::SUCCESS;
}

StatusCode BTaggingScoresAlg::finalize()
{
  return StatusCode::SUCCESS;
}