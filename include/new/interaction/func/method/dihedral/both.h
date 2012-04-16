
#ifndef _Interaction_Func_Method_Dihedral_Both_H_
#define _Interaction_Func_Method_Dihedral_Both_H_

#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void BFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      InteractionBuffer<T>& Buf,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[DihedralBondVecJI],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecKJ],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecLK],X[L],X[K],Geo);
      cross(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralBondVecJI],
                                        Buf.tmvec[DihedralBondVecKJ]);
      cross(Buf.tmvec[DihedralNormVecB],Buf.tmvec[DihedralBondVecKJ],
                                        Buf.tmvec[DihedralBondVecLK]);
      cross(Buf.tmvec[DihedralCrossNormVec],Buf.tmvec[DihedralNormVecA],
                                            Buf.tmvec[DihedralNormVecB]);
      if(IsValid(Buf.inf)) Buf.GetPreBoth(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[DihedralIvNormASQ]=1./normSQ(Buf.tmvec[DihedralNormVecA]);
        Buf.pre[DihedralIvNormBSQ]=1./normSQ(Buf.tmvec[DihedralNormVecB]);
        Buf.pre[DihedralAxisSQ]=normSQ(Buf.tmvec[DihedralBondVecKJ]);
        Buf.pre[DihedralDotBondAB]
          =dot(Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ]);
        Buf.pre[DihedralDotBondBC]
          =dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK]);
      }
      Buf.pre[DihedralDotNormAB]
        =dot(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      Buf.pre[DihedralCrossNormAB]
        =dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralCrossNormVec]);
      Buf.P2PBoth(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee,ef;
    bfunc(Buf.post.start,P,&ee,&ef);
    Energy+=ee;

    T efi=ef*Buf.post[DihedralFactorI];
    T efj=ef*Buf.post[DihedralFactorJ];
    T efk=ef*Buf.post[DihedralFactorK];
    T efl=ef*Buf.post[DihedralFactorL];

    shift(Grad[I],efi,Buf.tmvec[DihedralNormVecA]);
    shift(Grad[L],efl,Buf.tmvec[DihedralNormVecB]);
    shift(Grad[J],-efi-efj,Buf.tmvec[DihedralNormVecA]);
    shift(Grad[J],+efk,Buf.tmvec[DihedralNormVecB]);
    shift(Grad[K],+efj,Buf.tmvec[DihedralNormVecA]);
    shift(Grad[K],-efl-efk,Buf.tmvec[DihedralNormVecB]);
  }

}

#endif

