#ifndef BOOSTEDJETTAGGERSALG_H
#define BOOSTEDJETTAGGERSALG_H

#include <AnaAlgorithm/AnaAlgorithm.h>
#include <SystematicsHandles/SysListHandle.h>
#include <SystematicsHandles/SysReadHandle.h>
#include <SystematicsHandles/SysWriteDecorHandle.h>

#include <xAODJet/JetContainer.h>

// Top taggers
#include "BoostedJetTaggers/JSSWTopTaggerDNN.h"
#include "BoostedJetTaggers/JSSWTopTaggerANN.h"

//#include "AsgTools/StandaloneToolHandle.h"
#include "AsgTools/AnaToolHandle.h"

namespace top {

  class BoostedJetTaggersAlg final : public EL::AnaAlgorithm {

    public:
      BoostedJetTaggersAlg(const std::string &name, ISvcLocator *pSvcLocator);
      virtual StatusCode initialize() override;
      virtual StatusCode execute() override;

    private:
      
      bool m_isMC;
      std::string m_taggerTypeStr;
      std::string m_taggerCalibArea;
      std::string m_taggerConfigFile;
      std::string m_taggerDecoration;
      
      enum class TaggerType {
        JSSWTopTaggerDNN = 0, 
        JSSWTopTaggerANN = 1
      };
      TaggerType m_taggerType;
      asg::AnaToolHandle<JSSWTopTaggerDNN> m_taggerDNN;
      asg::AnaToolHandle<JSSWTopTaggerANN> m_taggerANN;
      
      CP::SysListHandle m_systematicsList {this};
      
      CP::SysReadHandle<xAOD::JetContainer> m_ljetsHandle {
        this, "ljets", "", "the input large-R jet container"
      };
      
      CP::SysWriteDecorHandle<int> m_ljetsTopTagHandle {
        this, "tagged", "tagged_%SYS%", "decoration name for top-tagging result"
      };
      CP::SysWriteDecorHandle<float> m_ljetsTopTagScoreHandle {
        this, "tagged_score", "tagged_score_%SYS%", "decoration name for top-tagging score"
      };
      CP::SysWriteDecorHandle<int> m_ljetsTopTagPassMassHandle {
        this, "tagged_passMass", "tagged_passMass_%SYS%", "decoration name for top-tagging pass mass cut"
      };
      CP::SysWriteDecorHandle<float> m_ljetsTopTagSFHandle {
        this, "tagged_SF", "tagged_SF_%SYS%", "decoration name for top-tagging scale factor"
      };
      CP::SysWriteDecorHandle<float> m_ljetsTopTagEfficiencyHandle {
        this, "tagged_efficiency", "tagged_efficiency_%SYS%", "decoration name for top-tagging efficiency"
      };
      CP::SysWriteDecorHandle<float> m_ljetsTopTagEffSFHandle {
        this, "tagged_effSF", "tagged_effSF_%SYS%", "decoration name for top-tagging efficiency scale factor"
      };
      
  };

} // namsepace top

#endif
