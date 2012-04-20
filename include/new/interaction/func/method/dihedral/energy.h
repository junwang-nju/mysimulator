
#ifndef _Interaction_Func_Method_Dihedral_Energy_H_
#define _Interaction_Func_Method_Dihedral_Energy_H_

#include "distance/calc.h"
#include "array/1d/cross.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/dihedral/common/buffer/pre-name.h"
#include "interaction/func/impl/dihedral/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodDihedral(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      unsigned int I=idx[0], J=idx[1], K=idx[2], L=idx[3];
      DisplacementCalc(Buf.tmvec[DihedralBondVecJI],X[J],X[I],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecKJ],X[K],X[J],Geo);
      DisplacementCalc(Buf.tmvec[DihedralBondVecLK],X[L],X[K],Geo);
      cross(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralBondVecJI],
                                        Buf.tmvec[DihedralBondVecKJ]);
      cross(Buf.tmvec[DihedralNormVecB],Buf.tmvec[DihedralBondVecKJ],
                                        Buf.tmvec[DihedralBondVecLK]);
      cross(Buf.tmvec[DihedralCrossNormVec],Buf.tmvec[DihedralNormVecA],
                                            Buf.tmvec[DihedralNormVecB]);
      if(IsValid(Buf.inf)) Buf.GetPreFunc(&Buf);
      else {
        Buf.pre[DihedralIvNormASQ]=1./normSQ(Buf.tmvec[DihedralNormVecA]);
        Buf.pre[DihedralIvNormBSQ]=1./normSQ(Buf.tmvec[DihedralNormVecB]);
      }
      Buf.pre[DihedralDotNormAB]
        =dot(Buf.tmvec[DihedralNormVecA],Buf.tmvec[DihedralNormVecB]);
      Buf.pre[DihedralCrossNormAB]
        =dot(Buf.tmvec[DihedralBondVecKJ],Buf.tmvec[DihedralCrossNormVec]);
      Buf.P2PFunc(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee;
    efunc(Buf.post.start,P,&ee);
    Energy+=ee;
  }

}

#endif

