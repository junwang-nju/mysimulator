
#ifndef _Propagator_Monomer_PLV_Move_H_
#define _Propagator_Monomer_PLV_Move_H_

#include "data/name/propagator-monomer-particle-langevin-vverlet.h"
#include "data/name/propagator-langevin-vverlet.h"
#include "data/basic/unique-parameter.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-op.h"

namespace std {

  template <typename T>
  void PLVMove_BeforeG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    scaleshift(
        V,P[PLV_FactorBeforeG].value<T>(),-P[PLV_HalfDeltaTIvM].value<T>(),
        Grad);
    GaussianRNG *grng=reinterpret_cast<GaussianRNG*>(GP[LV_GaussianRNG].ptr);
    Vector<T> rv;
    refer(rv,*reinterpret_cast<Vector<T>*>(P[PLV_RandomVelocity].ptr));
    fillarray(*grng,rv);
    scale(rv,dMsk);
    shift(V,P[PLV_RandomVelocitySize].value<T>(),rv);
    shift(X,GP[DeltaTime].value<T>(),V);
  }

  template <typename T>
  void PLVMove_AfterG(
      Vector<T>& X, Vector<T>& V, const Vector<T>& Grad, const Vector<T>& dMsk,
      const Vector<UniqueParameter>& GP, const Vector<UniqueParameter>& P) {
    shift(V,-P[PLV_HalfDeltaTIvM].value<T>(),Grad);
    GaussianRNG *grng=reinterpret_cast<GaussianRNG*>(GP[LV_GaussianRNG].ptr);
    Vector<T> rv;
    refer(rv,*reinterpret_cast<Vector<T>*>(P[PLV_RandomVelocity].ptr));
    fillarray(*grng,rv);
    scale(rv,dMsk);
    shift(V,P[PLV_RandomVelocitySize].value<T>(),rv);
    scale(V,P[PLV_FactorAfterG].value<T>());
  }

}

#endif

