
#ifndef _Monomer_Propagator_PEV_Move_H_
#define _Monomer_Propagator_PEV_Move_H_

#include "data/propagator/monomer-propagator.h" 
#include "data/name/monomer-propagator-particle-conste-vverlet.h"
#include "data/name/propagator-conste-vverlet.h"

namespace std {

  template <typename T>
  void PEVMove_BeforeG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& X=*reinterpret_cast<Vector<T>*>(MP[XVector].ptr);
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    shift(V,-MP[PEV_HalfDeltaTIvM].value<T>(),G);
    shift(X,GP[DeltaTime].value<T>(),V);
  }

  template <typename T>
  void PEVMove_AfterG(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    Vector<T>& V=*reinterpret_cast<Vector<T>*>(MP[VVector].ptr);
    Vector<T>& G=*reinterpret_cast<Vector<T>*>(MP[GVector].ptr);
    shift(V,-MP[PEV_HalfDeltaTIvM].value<T>(),Grad);
  }

}

#endif

