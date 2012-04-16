
#ifndef _Interaction_Func_Method_Dihedral_Gradient_H_
#define _Interaction_Func_Method_Dihedral_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/func/impl/common/parameter/name.h"
#include "interaction/func/impl/dihedral/common/buffer/name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad,
      void (*ufunc)(const T*,const Unique64Bit*,T*),
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    assert(IsValid(tmvec));
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    Array1D<T>* tmvec=
      reinterpret_cast<Array1D<T>*>(P[InteractionArrayBuffer].ptr[0]);
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    T dih,ivfaci,ivfacl,facji,fackl;
    if(P[InteractionBufferFlag].u[0]==0) {
      T dt[7];
      DisplacementCalc(tmvec[0],X[J],X[I],Geo);
      dt[4]=DistanceSQ(tmvec[1],X[K],X[J],Geo);
      DisplacementCalc(tmvec[2],X[L],X[K],Geo);
      cross(tmvec[3],tmvec[0],tmvec[1]);
      cross(tmvec[4],tmvec[1],tmvec[2]);
      dt[0]=dot(tmvec[3],tmvec[3]);
      dt[1]=dot(tmvec[4],tmvec[4]);
      dt[2]=dot(tmvec[3],tmvec[4]);
      cross(tmvec[5],tmvec[3],tmvec[4]);
      dt[3]=dot(tmvec[1],tmvec[5]);
      dt[5]=dot(tmvec[0],tmvec[1]);
      dt[6]=dot(tmvec[1],tmvec[2]);
      ufunc(dt,P,buffer);
    }
    T ef;
    dfunc(buffer,P,&ef);

    T efi=ef*buffer[DihedralFactorI];
    T efj=ef*buffer[DihedralFactorJ];
    T efk=ef*buffer[DihedralFactorK];
    T efl=ef*buffer[DihedralFactorL];

    shift(Grad[I],efi,tmvec[3]);
    shift(Grad[L],efl,tmvec[4]);
    shift(Grad[J],-efi-efj,tmvec[3]);
    shift(Grad[J],+efk,tmvec[4]);
    shift(Grad[K],+efj,tmvec[3]);
    shift(Grad[K],-efl-efk,tmvec[4]);
  }

}

#endif

