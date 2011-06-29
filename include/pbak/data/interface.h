
#ifndef _Propagator_Data_Interface_H_
#define _Propagator_Data_Interface_H_

#include "io/error.h"
#include "propagator/move-name.h"
#include "propagator/ensemble-method-name.h"

namespace mysimulator {

  template <PropagatorMoveName MoveMode,
            PropagatorEnsembleMethodName EnsembleMode, typename T>
  struct PropagatorData { 

    typedef PropagatorData<MoveMode,EnsembleMode,T> Type;

    PropagatorData() {
      Error("PropagatorData for this Move or Ensemble Disabled!");
    }
    PropagatorData(const Type&) {
      Error("Copier of PropagatorData Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for PropagatorData Disabled!");
      return *this;
    }
    ~PropagatorData() { clearData(); }

    void clearData() {}

  };

  template <PropagatorMoveName MN,PropagatorEnsembleMethodName EN,typename T>
  bool IsValid(const PropagatorData<MN,EN,T>&) { return false; }

  template <PropagatorMoveName MN,PropagatorEnsembleMethodName EN,typename T>
  void release(PropagatorData<MN,EN,T>& PD) { PD.clearData(); }

}

#include "propagator/data/vverlet/const-e/specification.h"

#endif

