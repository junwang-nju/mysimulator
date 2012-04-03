
#ifndef _Interaction_Func_Method_Angle_Energy_H_
#define _Interaction_Func_Method_Angle_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "intrinsic-type/square-root.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* tmvec,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    assert(IsValid(tmvec));
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    T csAngle;
    if(buffer==NULL) {
      unsigned int I=idx[0], J=idx[1], K=idx[2];
      T dsqij,dsqjk,dsqki;
      dsqij=DistanceSQ(tmvec[0],X[I],X[J],Geo);
      dsqjk=DistanceSQ(tmvec[1],X[J],X[K],Geo);
      dsqki=DistanceSQ(tmvec[2],X[K],X[I],Geo);
      csAngle=(dsqij+dsqjk-dsqki)/sqroot(dsqij*dsqjk)*0.5;
    } else csAngle=*buffer;
    T ee;
    efunc(&csAngle,P,&ee);
    Energy+=ee;
  }

}

#endif

