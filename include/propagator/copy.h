
#ifndef _Propagator_Copy_H_
#define _Propagator_Copy_H_

#include "propagator/interface.h"

namespace mysimulator {

  template <typename T>
  void copy(Propagator<T>& P, const Propagator<T>& cP) {
    assert(IsValid(P)&&IsValid(cP));
    assert(P.MoveMode==cP.MoveMode);
    copy(P.Data,cP.Data);
    copy(P.Sys,cP.Sys);
  }

}

#endif

