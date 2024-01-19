/// @author Diego Baron

#include "TopCPToolkit/SVMassAlg.h"
#include "xAODBTagging/BTagging.h"
#include "xAODBTagging/BTaggingUtilities.h"

SVMassAlg::SVMassAlg(const std::string &name, ISvcLocator *pSvcLocator)
    : EL::AnaAlgorithm(name, pSvcLocator)
{
  
}

StatusCode SVMassAlg::initialize()
{
    ANA_MSG_INFO("Initializing SVMassAlg " << name());

    // Input handles
    ANA_CHECK(m_jetsHandle.initialize(m_systematicsList));

    ANA_CHECK(m_preselection.initialize(m_systematicsList, m_eventInfoHandle, SG::AllowEmpty));
    ANA_CHECK(m_eventInfoHandle.initialize(m_systematicsList));

    // Output decorations
    ANA_CHECK(m_svmass_decor.initialize(m_systematicsList, m_jetsHandle));


    ANA_CHECK(m_systematicsList.initialize());

    return StatusCode::SUCCESS;
}

StatusCode SVMassAlg::execute()
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

    // Loop over the jets, get the SVMass and write to output.
    for(const xAOD::Jet* jet : *jets)
    {
        //Get the SVMass using b-tagging utilities.
        const auto btag = xAOD::BTaggingUtilities::getBTagging( *jet );
        float SVMass{-100.0f};
        SVMass = btag->auxdata<float>("SV1_masssvx");
        // Set the mass to the extracted value.
        m_svmass_decor.set(*jet, SVMass, sys);
    }

  }
  return StatusCode::SUCCESS;
}
