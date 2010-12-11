
#ifndef _Monomer_Propagator_PLV_Move_H_
#define _Monomer_Propagator_PLV_Move_H_

#include "data/propagator/monomer-propagator.h" 
#include "data/name/monomer-propagator-particle-langevin-vverlet.h"
#include "data/name/subsys-propagator-langevin-vverlet.h"
#include "data/random/regular.h"
#include "operation/random/random-generator-op.h"

namespace std {

  template <typename T>
  void PLVMove_BeforeG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& X=*reinterpret_cast<Vector<T>*>(MP[XVector].ptr);
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    Vector<T>& Msk=*reinterpret_cast<Vector<T>*>(MP[MskVector].ptr);
    scaleshift(
        V,
        static_cast<UniqueParameter&>(MP[PLV_FactorBeforeG]).value<T>(),
        -static_cast<UniqueParameter&>(MP[PLV_HalfTimeStepIvM]).value<T>(),
        G);
    GaussianRNG *grng=reinterpret_cast<GaussianRNG*>(GP[LV_GaussianRNG].ptr);
    Vector<T> rv;
    refer(rv,*reinterpret_cast<Vector<T>*>(MP[PLV_RandomVelocity].ptr));
    fillarray(*grng,rv);
    scale(rv,Msk);
    shift(V,
          static_cast<UniqueParameter&>(MP[PLV_RandomVelocitySize]).value<T>(),
          rv);
    shift(X,GP[TimeStep].value<T>(),V);
  }

  template <typename T>
  void PLVMove_AfterG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    Vector<T>& Msk=*reinterpret_cast<Vector<T>*>(MP[MskVector].ptr);
    shift(V,
          -static_cast<UniqueParameter&>(MP[PLV_HalfTimeStepIvM]).value<T>(),
          G);
    GaussianRNG *grng=reinterpret_cast<GaussianRNG*>(GP[LV_GaussianRNG].ptr);
    Vector<T> rv;
    refer(rv,*reinterpret_cast<Vector<T>*>(MP[PLV_RandomVelocity].ptr));
    fillarray(*grng,rv);
    scale(rv,Msk);
    shift(V,
          static_cast<UniqueParameter&>(MP[PLV_RandomVelocitySize]).value<T>(),
          rv);
    scale(V,
          static_cast<UniqueParameter&>(MP[PLV_FactorAfterG]).value<T>());
  }

}

#endif

