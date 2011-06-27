
#ifndef _Propagator_Base_Copy_H_
#define _Propagator_Base_Copy_H_

#include "propagator/interface.h"

namespace mysimulator {

  template <typename T>
  void copy(PropagatorBase<T>& P, const PropagatorBase<T>& cP) {
    assert(IsValid(P)&&IsValid(cP));
    assert(P.MoveMode==cP.MoveMode);
    copy(P.Data,cP.Data);
    copy(P.Sys,cP.Sys);
    /// the compatibility of following data are not checked
    copy(P.ID,cP.ID);
    copy(P.X,cP.X);
    copy(P.V,cP.V);
    copy(P.G,cP.G);
    copy(P.Msk,cP.Msk);
  }

}

#endif

