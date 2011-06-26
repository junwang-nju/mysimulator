
#ifndef _Propagator_Monomer_Move_Ensemble_Interface_H_
#define _Propagator_Monomer_Move_Ensemble_Interface_H_

#include "propagator/move-name.h"
#include "propagator/ensemble-method-name.h"

namespace mysimulator {

  template <PropagatorMoveName MoveMode,
            PropagatorEnsembleMethodName EnsembleMode, typename T>
  struct MonomerPropagatorMoveEnsemble {

    typedef MonomerPropagatorMoveEnsemble<MoveMode,EnsembleMode,T>  Type;

    MonomerPropagatorMoveEnsemble() {
      Error("MonomerPropagatorMoveEnsemble for this Move or Ensemble Disabled!");
    }
    MonomerPropagatorMoveEnsemble(const Type&) {
      Error("Copier of MonomerPropagatorMoveEnsemble Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagatorMoveEnsemble Disabled!");
      return *this;
    }
    ~MonomerPropagatorMoveEnsemble() { clearData(); }

    void clearData() {}

  };

  template<PropagatorMoveName MN,PropagatorEnsembleMethodName EN,typename T>
  bool IsValid(const MonomerPropagatorMoveEnsemble<MN,EN,T>&) { return false; }

  template<PropagatorMoveName MN,PropagatorEnsembleMethodName EN,typename T>
  void release(MonomerPropagatorMoveEnsemble<MN,EN,T>& P) { P.clearData(); }

}

#include "propagator/monomer/vverlet/const-e/move-ensemble-specification.h"

#endif

