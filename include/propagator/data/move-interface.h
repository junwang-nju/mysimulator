
#ifndef _Propagator_Data_Move_Interface_H_
#define _Propagator_Data_Move_Interface_H_

#include "propagator/move-name.h"
#include "io/error.h"

namespace mysimulator {

  template <PropagatorMoveName MoveMode, typename T>
  struct PropagatorDataMove {

    typedef PropagatorDataMove<MoveMode,T>    Type;

    PropagatorDataMove() {
      Error("PropagatorDataMove for this ensemble Disabled!");
    }
    PropagatorDataMove(const Type&) {
      Error("Copier of PropagatorDataMove Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for PropagatorDataMove Disabled!");
      return *this;
    }
    ~PropagatorDataMove() { clearData(); }

    void clearData() {}

  };

  template <PropagatorMoveName MN, typename T>
  bool IsValid(const PropagatorDataMove<MN,T>&) { return false; }

  template <PropagatorMoveName MN, typename T>
  void release(PropagatorDataMove<MN,T>& PD) { PD.clearData(); }

}

#include "propagator/data/vverlet/move-specification.h"

#endif

