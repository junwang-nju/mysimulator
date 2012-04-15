
#ifndef _Interaction_Func_Method_Angle_Energy_H_
#define _Interaction_Func_Method_Angle_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy,
      void (*ufunc)(const T*,const Unique64Bit*,T*),
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array1D<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    if(P[InteractionBufferFlag].u[0]==0) {
      unsigned int I=idx[0], J=idx[1], K=idx[2];
      T dsq[3];
      dsq[0]=DistanceSQ(tmvec[0],X[I],X[J],Geo);
      dsq[1]=DistanceSQ(tmvec[1],X[J],X[K],Geo);
      dsq[2]=DistanceSQ(tmvec[2],X[K],X[I],Geo);
      ufunc(dsq,P,buffer);
    }
    T ee;
    efunc(buffer,P,&ee);
    Energy+=ee;
  }

}

#endif

