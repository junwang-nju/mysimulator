
#ifndef _Interaction_Func_Method_Dihedral_Both_H_
#define _Interaction_Func_Method_Dihedral_Both_H_

#include "interaction/buffer/interface.h"
#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/post-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GT,typename T>
  void BMethodDihedral(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      T& Energy, Array1D<Array1D<T> >& Grad,
      void (*bfunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*,T*)) {
    unsigned int I=ID[0],J=ID[1],K=ID[2],L=ID[3];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[DihedralBondVecJI],X[J],X[I],Geo,Buf.dim);
      DisplacementCalc(Buf.tmvec[DihedralBondVecKJ],X[K],X[J],Geo,Buf.dim);
      DisplacementCalc(Buf.tmvec[DihedralBondVecLK],X[L],X[K],Geo,Buf.dim);
      Cross(Buf.tmvec[DihedralNormVecA],
            Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ]);
      Cross(Buf.tmvec[DihedralNormVecB],
            Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK]);
      Cross(Buf.tmvec[DihedralCrossNormVec],
            Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      if(Buf.inf.IsValid()) Buf.GetPreBoth();
      else {
        Buf.pre[DihedralIvNormASQ]=
          1./NormSQ(Buf.tmvec[DihedralNormVecA],Buf.dim);
        Buf.pre[DihedralIvNormBSQ]=
          1./NormSQ(Buf.tmvec[DihedralNormVecB],Buf.dim);
        Buf.pre[DihedralAxisSQ]=NormSQ(Buf.tmvec[DihedralBondVecKJ],Buf.dim);
        Buf.pre[DihedralDotBondAB]=
          Dot(Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ],
              Buf.dim);
        Buf.pre[DihedralDotBondBC]=
          Dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK],
              Buf.dim);
      }
      Buf.pre[DihedralDotNormAB]=
        Dot(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB],Buf.dim);
      Buf.pre[DihedralCrossNormAB]=
        Dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralCrossNormVec],
            Buf.dim);
      Buf.Pre2PostBoth(P);
    }
    T ee,ef;
    bfunc(Buf.post,P,&ee,&ef);
    Energy+=ee;
    T efi=ef*Buf.post[DihedralFactorI];
    T efj=ef*Buf.post[DihedralFactorJ];
    T efk=ef*Buf.post[DihedralFactorK];
    T efl=ef*Buf.post[DihedralFactorL];
    Shift(Grad[I],efi,Buf.tmvec[DihedralNormVecA],Buf.dim);
    Shift(Grad[L],efl,Buf.tmvec[DihedralNormVecB],Buf.dim);
    Shift(Grad[J],-efi-efj,Buf.tmvec[DihedralNormVecA],Buf.dim);
    Shift(Grad[J],efk,Buf.tmvec[DihedralNormVecB],Buf.dim);
    Shift(Grad[K],efj,Buf.tmvec[DihedralNormVecA],Buf.dim);
    Shift(Grad[K],-efl-efk,Buf.tmvec[DihedralNormVecB],Buf.dim);
  }

}

#endif

