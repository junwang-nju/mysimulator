
#ifndef _Propagator_Monomer_PEV_Move_H_
#define _Propagator_Monomer_PEV_Move_H_

#include "data/name/parameter-propagator-monomer-particle-conste-vverlet.h"
#include "data/basic/vector.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void PEVMove_BeforeG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad,const Vector<T>& dMask,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    shift(V,-P[PEV_HalfDeltaTIvM].value<T>(),Grad);
    shift(X,GP[DeltaTime].value<T>(),V);
  }

  template <typename T>
  void PEVMove_AfterG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad,const Vector<T>& dMask,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    shift(V,-P[PEV_HalfDeltaTIvM].value<T>(),Grad);
  }

}

#endif

