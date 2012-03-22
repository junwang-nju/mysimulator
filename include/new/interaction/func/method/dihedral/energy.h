
#ifndef _Interaction_Func_Method_Dihedral_Energy_H_
#define _Interaction_Func_Method_Dihedral_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "array/1d/cross.h"
#include "array/1d/scale.h"
#include "intrinsic-type/acos.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* tmvec,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    T nr3,nr4;
    T csDih,sgnDih,dih;
    DisplacementCalc(tmvec[0],X[J],X[I],Geo);
    DisplacementCalc(tmvec[1],X[K],X[J],Geo);
    DisplacementCalc(tmvec[2],X[L],X[K],Geo);
    cross(tmvec[3],tmvec[0],tmvec[1]);
    cross(tmvec[4],tmvec[1],tmvec[2]);
    nr3=norm(tmvec[3]);
    nr4=norm(tmvec[4]);
    assert(nr3>1e-8);
    assert(nr4>1e-8);
    scale(tmvec[3],1./nr3);
    scale(tmvec[4],1./nr4);
    csDih=dot(tmvec[3],tmvec[4]);
    cross(tmvec[5],tmvec[3],tmvec[4]);
    sgnDih=(dot(tmvec[1],tmvec[5])>0?1:-1);
    dih=arcCos(csDih)*sgnDih;
    T ee;
    efunc(&dih,P,&ee);
    Energy+=ee;
  }

}

#endif

