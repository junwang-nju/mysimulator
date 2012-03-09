
#ifndef _Interaction_Func_Method_Dihedral_Gradient_H_
#define _Interaction_Func_Method_Dihedral_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "intrinsic-type/acos.h"
#include "intrinsic-type/square-root.h"
#include "array/1d/cross.h"
#include "array/1d/scale.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad, Array1DContent<T>* tmvec,
      void (*dfunc)(const T&,const Unique64Bit*,T&)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    T dsqij,dsqjk,dsqkl,nr3,nr4;
    T csDih,sgnDih,dih;
    T ef,efi,efj,efk,efl;
    T ivdsqjk,tma,tmb,dotab,dotbc;
    dsqij=DistanceSQ(tmvec[0],X[J],X[I],Geo);
    dsqjk=DistanceSQ(tmvec[1],X[K],X[J],Geo);
    dsqkl=DistanceSQ(tmvec[2],X[L],X[K],Geo);
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
    dfunc(dih,P,ef);
    ivdsqjk=1./dsqjk;
    dotab=dot(tmvec[0],tmvec[1]);
    dotbc=dot(tmvec[1],tmvec[2]);
    tma=dotab*ivdsqjk;
    tmb=dotbc*ivdsqjk;
    efi=-ef/sqroot(dsqij-dotab*tma);
    efl=+ef/sqroot(dsqkl-dotbc*tmb);
    efj=tma*efi;
    efk=tmb*efl;
    shift(Grad[I],efi,tmvec[3]);
    shift(Grad[L],efl,tmvec[4]);
    shift(Grad[J],-efi-efj,tmvec[3]);
    shift(Grad[J],+efk,tmvec[4]);
    shift(Grad[K],+efj,tmvec[3]);
    shift(Grad[K],-efl-efk,tmvec[4]);
  }

}

#endif
