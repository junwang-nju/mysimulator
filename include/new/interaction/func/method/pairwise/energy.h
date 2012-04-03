
#ifndef _Interaction_Func_Method_Pairwise_Energy_H_
#define _Interaction_Func_Method_Pairwise_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, void (*ufunc)(const T&,T*),
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array1D<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    T dsq;
    if(P[InteractionBufferFlag].u[0]==0) {
      dsq=DistanceSQ(tmvec[0],X[idx[0]],X[idx[1]],Geo);
      ufunc(dsq,buffer);
    }
    T ee;
    efunc(buffer,P,&ee);
    Energy+=ee;
  }

}

#endif

