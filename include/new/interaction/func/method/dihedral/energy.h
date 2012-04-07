
#ifndef _Interaction_Func_Method_Dihedral_Energy_H_
#define _Interaction_Func_Method_Dihedral_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy,
      void (*ufunc)(const T*,const Unique64Bit*,T*),
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    assert(IsValid(tmvec));
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    if(P[InteractionBufferFlag].u[0]==0) {
      unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
      T dt[4];
      DisplacementCalc(tmvec[0],X[J],X[I],Geo);
      DisplacementCalc(tmvec[1],X[K],X[J],Geo);
      DisplacementCalc(tmvec[2],X[L],X[K],Geo);
      cross(tmvec[3],tmvec[0],tmvec[1]);
      cross(tmvec[4],tmvec[1],tmvec[2]);
      cross(tmvec[5],tmvec[3],tmvec[4]);
      dt[0]=dot(tmvec[3],tmvec[3]);
      dt[1]=dot(tmvec[4],tmvec[4]);
      dt[2]=dot(tmvec[3],tmvec[4]);
      dt[3]=dot(tmvec[1],tmvec[5]);
      ufunc(dt,P,buffer);
    }
    T ee;
    efunc(buffer,P,&ee);
    Energy+=ee;
  }

}

#endif

