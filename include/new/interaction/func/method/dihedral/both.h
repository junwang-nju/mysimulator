
#ifndef _Interaction_Func_Method_Dihedral_Both_H_
#define _Interaction_Func_Method_Dihedral_Both_H_

#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void BFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      InteractionBuffer<T>& Buf,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[0],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[1],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[2],X[L],X[K],Geo);
      cross(Buf.tmvec[3],Buf.tmvec[0],Buf.tmvec[1]);
      cross(Buf.tmvec[4],Buf.tmvec[1],Buf.tmvec[2]);
      cross(Buf.tmvec[5],Buf.tmvec[3],Buf.tmvec[4]);
      if(IsValid(Buf.inf)) Buf.GetPreBoth(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[0]=1./normSQ(Buf.tmvec[3]);
        Buf.pre[1]=1./normSQ(Buf.tmvec[4]);
        Buf.pre[4]=normSQ(Buf.tmvec[1]);
        Buf.pre[5]=dot(Buf.tmvec[0],Buf.tmvec[1]);
        Buf.pre[6]=dot(Buf.tmvec[1],Buf.tmvec[2]);
      }
      Buf.pre[2]=dot(Buf.tmvec[3],Buf.tmvec[4]);
      Buf.pre[3]=dot(Buf.tmvec[1],Buf.tmvec[5]);
      Buf.P2PBoth(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee,ef;
    bfunc(Buf.post.start,P,&ee,&ef);
    Energy+=ee;

    T efi=ef*Buf.post[DihedralFactorI];
    T efj=ef*Buf.post[DihedralFactorJ];
    T efk=ef*Buf.post[DihedralFactorK];
    T efl=ef*Buf.post[DihedralFactorL];

    shift(Grad[I],efi,Buf.tmvec[3]);
    shift(Grad[L],efl,Buf.tmvec[4]);
    shift(Grad[J],-efi-efj,Buf.tmvec[3]);
    shift(Grad[J],+efk,Buf.tmvec[4]);
    shift(Grad[K],+efj,Buf.tmvec[3]);
    shift(Grad[K],-efl-efk,Buf.tmvec[4]);
  }

}

#endif

