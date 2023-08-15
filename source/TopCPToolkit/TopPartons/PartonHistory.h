#ifndef ANALYSISTOP_TOPPARTONS_PARTONHISORTY_H
#define ANALYSISTOP_TOPPARTONS_PARTONHISORTY_H

// EDM include(s):
#include "AthContainers/DataVector.h"
#include "AthContainers/AuxElement.h"
#include "xAODCore/AuxInfoBase.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/CLASS_DEF.h"
#include <vector>

namespace xAOD {
  /// Aux Container
  class PartonHistoryAuxContainer: public AuxContainerBase {
  public:
    /// Default constructor
    PartonHistoryAuxContainer();
  }; // end Aux container

  /// Interface class
  class PartonHistory: public SG::AuxElement {
  public:
    /// Default constructor
    PartonHistory();
    /// Default desturctor
    virtual ~PartonHistory() {}

    void IniVarTtbar();
    void IniVarTzq();
    void IniVarTtbarLight();
    void IniVarTbbar();
    void IniVarWlv();
    void IniVarWtb();
    void IniVarZ();
    void IniVarTtGamma();
    void IniVarThq();
  };

  class PartonHistoryAux: public AuxInfoBase {
  public:
    PartonHistoryAux();
    virtual ~PartonHistoryAux() {}
  };

  typedef DataVector < xAOD::PartonHistory > PartonHistoryContainer;
}

// Dictonaries
CLASS_DEF(xAOD::PartonHistory, 135846343, 1)
CLASS_DEF(xAOD::PartonHistoryAux, 151403368, 1)
CLASS_DEF(xAOD::PartonHistoryContainer, 1219079565, 1)
CLASS_DEF(xAOD::PartonHistoryAuxContainer, 1244378748, 1)

#endif
