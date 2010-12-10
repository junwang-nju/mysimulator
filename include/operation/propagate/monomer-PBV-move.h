
#ifndef _Monomer_Propagator_PBV_Move_H_
#define _Monomer_Propagator_PBV_Move_H_

#include "data/propagator/monomer-propagator.h" 
#include "data/name/monomer-propagator-particle-berendsen-vverlet.h"
#include "data/name/propagator-berendsen-vverlet.h"

namespace std {

  template <typename T>
  void PBVMove_PreProcess(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    scale(V,GP[BV_BScaleFactor].value<T>());
  }

  template <typename T>
  void PBVMove_BeforeG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& X=*reinterpret_cast<Vector<T>*>(MP[XVector].ptr);
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    shift(V,-MP[PBV_HalfDeltaTIvM].value<T>(),G);
    shift(X,GP[DeltaTime].value<T>(),V);
  }

  template <typename T>
  void PBVMove_AfterG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    shift(V,-MP[PBV_HalfDeltaTIvM].value<T>(),G);
  }

  template <typename T>
  void PBVMove_PostProcess(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    scale(V,GP[BV_AScaleFactor].value<T>());
  }

}

#endif

