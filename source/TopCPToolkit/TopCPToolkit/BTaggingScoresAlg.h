/// @author Diego Baron

#ifndef B_TAGGING_SCORES_ALG_H
#define B_TAGGING_SCORES_ALG_H

// Algorithm includes
#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SelectionHelpers/SysReadSelectionHandle.h>
#include <SystematicsHandles/SysWriteHandle.h>
#include <SystematicsHandles/SysReadDecorHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>
#include "FTagAnalysisInterfaces/IBTaggingSelectionTool.h"

// Framework includes
#include <xAODJet/JetContainer.h>
#include <xAODEventInfo/EventInfo.h>

class BTaggingScoresAlg final : public EL::AnaAlgorithm
{

public:
  BTaggingScoresAlg(const std::string &name, ISvcLocator *pSvcLocator);
  virtual StatusCode initialize() override;
  virtual StatusCode execute() override;
  virtual StatusCode finalize() override;

private:
  // configurable properties
  const bool m_saveAllProbabilities;
  const std::string m_taggerName;

  // systematics
  CP::SysListHandle m_systematicsList{this};

  // inputs needed for retrieving b-tagging scores
  CP::SysReadHandle<xAOD::JetContainer> m_jetsHandle{
      this, "jets", "", "the jet container to use"};

  CP::SysReadHandle<xAOD::EventInfo> m_eventInfoHandle{
      this, "eventInfo", "EventInfo", "the EventInfo container to read selection decisions from"};
  CP::SysReadSelectionHandle m_preselection{
      this, "eventSelection", "", "Name of the selection on which this instance is allowed to run"};

  ToolHandle<IBTaggingSelectionTool> m_btagging_sel_tool;

  // output decorations
  CP::SysWriteDecorHandle<double> m_btagScore_decor {this, "btagScore", "btagScore_%SYS%", "Combined b-tagging score"};
  CP::SysWriteDecorHandle<double> m_probBottom_decor {this, "probBottom", "prob_pb_%SYS%", "b probability"};
  CP::SysWriteDecorHandle<double> m_probCharm_decor {this, "probCharm", "prob_pc_%SYS%", "c probability"};
  CP::SysWriteDecorHandle<double> m_probLight_decor {this, "probLight", "prob_pl_%SYS%", "l probability"};


};

#endif