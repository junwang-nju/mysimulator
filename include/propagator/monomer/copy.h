
#ifndef _Propagator_Monomer_Copy_H_
#define _Propagator_Monomer_Copy_H_

#include "propagator/monomer/interface.h"
#include "vector/copy.h"

namespace mysimulator {

  template <typename T>
  void copy(MonomerPropagator<T>& P, const MonomerPropagator<T>& cP) {
    assert(IsValid(P)&&IsValid(cP));
    assert(P.MoveMode==cP.MoveMode);
    assert(P.EnsembleMode==cP.EnsembleMode);
    assert(P.MonomerMode==cP.MonomerMode);
    copy(P.Data,cP.Data);
  }

}

#endif

