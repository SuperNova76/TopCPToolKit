/// @author Diego Baron

#ifndef SV_MASS_ALG_H
#define SV_MASS_ALG_H
// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

// Framework includes
#include <xAODJet/JetContainer.h>
#include <xAODEventInfo/EventInfo.h>

class SVMassAlg final : public EL::AnaAlgorithm
{

public:
  SVMassAlg(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;

private:
  // configurable properties

  // systematics
  CP::SysListHandle m_systematicsList{this};

  // inputs needed for retrieving SV-Mass
  CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle{
      this, "jets", "", "the jet container to use"};

  CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle{
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"};
  CP::SysReadSelectionHandle m_preselection{
      this, "eventSelection", "", "Name of the selection on which this instance is allowed to run"};

  // output decorations
  CP::SysWriteDecorHandle<float> m_svmass_decor {this, "SVMass", "SVMass_%SYS%", "Secondary Vertex Mass"};
};

#endif