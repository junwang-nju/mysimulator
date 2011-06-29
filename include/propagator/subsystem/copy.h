
#ifndef _Propagator_Subsystem_Copy_H_
#define _Propagator_Subsystem_Copy_H_

#include "propagator/subsystem/interface.h"
#include "propagator/monomer/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(SubsysPropagator<T>& P, const SubsysPropagator<T>& cP) {
    assert(IsValid(P)&&IsValid(cP));
    assert(P.MoveMode==cP.MoveMode);
    assert(P.EnsembleMode==cP.EnsembleMode);
    assert(P.Mer.size==cP.Mer.size);
    copy(P.Data,cP.Data);
    copy(P.Mer,cP.Mer);
  }

}

#endif

