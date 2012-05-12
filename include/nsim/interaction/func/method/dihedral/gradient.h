
#ifndef _Interaction_Func_Method_Dihedral_Gradient_H_
#define _Interaction_Func_Method_Dihedral_Gradient_H_

#include "interaction/buffer/interface.h"
#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"
#include "interaction/func/impl/dihedral/common/buffer/post-name.h"

namespace mysimulator {

  template <typename GT,typename T>
  void GMethodDihedral(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      Array1D<Array1D<T> >& Grad,
      void (*dfunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*)) {
    unsigned int I=ID[0],J=ID[1],K=ID[2],L=ID[3];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[DihedralBondVecJI],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecKJ],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecLK],X[L],X[K],Geo);
      Cross(Buf.tmvec[DihedralNormVecA],
            Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ]);
      Cross(Buf.tmvec[DihedralNormVecB],
            Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK]);
      Cross(Buf.tmvec[DihedralCrossNormVec],
            Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      if(Buf.inf.IsValid()) Buf.GetPreDiff();
      else {
        Buf.pre[DihedralIvNormASQ]=1./NormSQ(Buf.tmvec[DihedralNormVecA]);
        Buf.pre[DihedralIvNormBSQ]=1./NormSQ(Buf.tmvec[DihedralNormVecB]);
        Buf.pre[DihedralAxisSQ]=NormSQ(Buf.tmvec[DihedralBondVecKJ]);
        Buf.pre[DihedralDotBondAB]=
          Dot(Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ]);
        Buf.pre[DihedralDotBondBC]=
          Dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK]);
      }
      Buf.pre[DihedralDotNormAB]=
        Dot(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      Buf.pre[DihedralCrossNormAB]=
        Dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralCrossNormVec]);
      Buf.Pre2PostDiff(P);
    }
    T ef;
    dfunc(Buf.post,P,&ef);
    T efi=ef*Buf.post[DihedralFactorI];
    T efj=ef*Buf.post[DihedralFactorJ];
    T efk=ef*Buf.post[DihedralFactorK];
    T efl=ef*Buf.post[DihedralFactorL];
    Shift(Grad[I],efi,Buf.tmvec[DihedralNormVecA]);
    Shift(Grad[L],efl,Buf.tmvec[DihedralNormVecB]);
    Shift(Grad[J],-efi-efj,Buf.tmvec[DihedralNormVecA]);
    Shift(Grad[J],+efk,Buf.tmvec[DihedralNormVecB]);
    Shift(Grad[K],+efj,Buf.tmvec[DihedralNormVecA]);
    Shift(Grad[K].-efl-efk,Buf.tmvec[DihedralNormVecB]);
  }

}

#endif

