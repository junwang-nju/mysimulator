
#ifndef _Propagator_Monomer_Interface_H_
#define _Propagator_Monomer_Interface_H_

#include "propagator/monomer/name.h"
#include "propagator/move-name.h"
#include "propagator/ensemble-method-name.h"
#include "io/error.h"

namespace mysimulator {

  template <PropagatorMonomerName MonomerMode, PropagatorMoveName MoveMode,
            PropagatorEnsembleMethodName EnsembleMode, typename T>
  struct MonomerPropagator {

    typedef MonomerPropagator<MonomerMode,MoveMode,EnsembleMode,T>  Type;

    MonomerPropagator() {
      Error("MonomerPropagator with this Monomer, Move, or Ensemble Disabled!");
    }
    MonomerPropagator(const Type&) {
      Error("Copier of MonomerPropagator Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagator Disabled!");
      return *this;
    }
    ~MonomerPropagator() { clearData(); }

    void clearData() {}

  };

  template <PropagatorMonomerName MrN, PropagatorMoveName MvN,
            PropagatorEnsembleMethodName EN, typename T>
  bool IsValid(const MonomerPropagator<MrN,MvN,EN,T>&) { return false; }

  template <PropagatorMonomerName MrN, PropagatorMoveName MvN,
            PropagatorEnsembleMethodName EN, typename T>
  void release(MonomerPropagator<MrN,MvN,EN,T>& P) { P.clearData(); }

}

#endif

