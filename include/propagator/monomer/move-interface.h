
#ifndef _Propagator_Monomer_Move_Interface_H_
#define _Propagator_Monomer_Move_Interface_H_

#include "propagator/move-name.h"
#include "io/error.h"

namespace mysimulator {

  template <PropagatorMoveName MoveMode, typename T>
  struct MonomerPropagatorMove {

    typedef MonomerPropagatorMove<MoveMode,T> Type;

    MonomerPropagatorMove() {
      Error("MonomerPropagatorMove for this MoveMode Disabled!");
    }
    MonomerPropagatorMove(const Type&) {
      Error("Copier of MonomerPropagatorMove Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for MonomerPropagatorMove Disabled!");
      return *this;
    }
    ~MonomerPropagatorMove() { clearData(); }

    void clearData() {}

  };

  template <PropagatorMoveName MN, typename T>
  bool IsValid(const MonomerPropagatorMove<MN,T>&) { return false; }

  template <PropagatorMoveName MN, typename T>
  void release(MonomerPropagatorMove<MN,T>& P) { P.clearData(); }

}

#include "propagator/monomer/vverlet/move-specification.h"

#endif

