
#ifndef _Interaction_Func_Method_Dihedral_Energy_H_
#define _Interaction_Func_Method_Dihedral_Energy_H_

#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/buffer/interface.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
      DisplacementCalc(Buf.tmvec[0],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[1],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[2],X[L],X[K],Geo);
      cross(Buf.tmvec[3],Buf.tmvec[0],Buf.tmvec[1]);
      cross(Buf.tmvec[4],Buf.tmvec[1],Buf.tmvec[2]);
      cross(Buf.tmvec[5],Buf.tmvec[3],Buf.tmvec[4]);
      if(IsValid(Buf.inf)) Buf.GetPreFunc(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[0]=1./normSQ(Buf.tmvec[3]);
        Buf.pre[1]=1./normSQ(Buf.tmvec[4]);
      }
      Buf.pre[2]=dot(Buf.tmvec[3],Buf.tmvec[4]);
      Buf.pre[3]=dot(Buf.tmvec[1],Buf.tmvec[5]);
      Buf.P2PFunc(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee;
    efunc(Buf.post.start,P,&ee);
    Energy+=ee;
  }

}

#endif

