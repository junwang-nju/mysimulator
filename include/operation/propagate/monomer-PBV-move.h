
#ifndef _Propagator_Monomer_PBV_Move_H_
#define _Propagator_Monomer_PBV_Move_H_

#include "data/name/propagator-monomer-particle-berendsen-vverlet.h"
#include "data/name/propagator-berendsen-vverlet.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T>
  void PBVMove_PreProcess(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    scale(V,GP[BV_BScaleFactor].value<T>());
  }

  template <typename T>
  void PBVMove_BeforeG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    shift(V,-P[PBV_HalfDeltaTIvM].value<T>(),Grad);
    shift(X,GP[DeltaTime].value<T>(),V);
  }

  template <typename T>
  void PBVMove_AfterG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    shift(V,-P[PBV_HalfDeltaTIvM].value<T>(),Grad);
  }

  template <typename T>
  void PBVMove_PostProcess(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    scale(V,GP[BV_AScaleFactor].value<T>());
  }

}

#endif

