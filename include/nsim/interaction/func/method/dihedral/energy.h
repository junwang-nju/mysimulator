
#ifndef _Interaction_Func_Method_Dihedral_Energy_H_
#define _Interaction_Func_Method_Dihedral_Energy_H_

#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GT,typename T>
  void EMethodDihedral(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      T& Energy,
      void (*efunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*)) {
    if(Buf.postUpdate) {
      unsigned int I=ID[0],J=ID[1],K=ID[2],L=ID[3];
      DisplacementCalc(Buf.tmvec[DihedralBondVecJI],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecKJ],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecLK],X[L],X[K],Geo);
      Cross(Buf.tmvec[DihedralNormVecA],
            Buf.tmvec[DihedralBondVecJI],Buf.tmvec[DihedralBondVecKJ]);
      Cross(Buf.tmvec[DihedralNormVecB],
            Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralBondVecLK]);
      Cross(Buf.tmvec[DihedralCrossNormVec],
            Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      if(Buf.Inf.IsValid()) Buf.GetPreFunc();
      else {
        Buf.pre[DihedralIvNormASQ]=1./NormSQ(Buf.tmvec[DihedralNormVecA]);
        Buf.pre[DihedralIvNormBSQ]=1./NormSQ(Buf.tmvec[DihedralNormVecB]);
      }
      Buf.pre[DihedralDotNormAB]=
        dot(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      Buf.pre[DihedralCrossNormAB]=
        dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralCrossNormVec]);
      Buf.Pre2PostFunc(P);
    }
    T ee;
    efunc(Buf.post,P,&ee);
    Energy+=ee;
  }

}

#endif

