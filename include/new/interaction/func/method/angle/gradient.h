
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad,InteractionBuffer<T>& Buf,
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[AngleBondVecIJ],X[I],X[J],Geo);
      DisplacementCalc(Buf.tmvec[AngleBondVecKJ],X[K],X[J],Geo);
      if(IsValid(Buf.inf))  Buf.GetPreDiff(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[AngleEdgeASQ]=normSQ(Buf.tmvec[AngleBondVecIJ]);
        Buf.pre[AngleEdgeBSQ]=normSQ(Buf.tmvec[AngleBondVecKJ]);
      }
      Buf.pre[AngleDotAB]=dot(Buf.tmvec[AngleBondVecIJ],tmvec[AngleBondVecKJ]);
      Buf.P2PDiff(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
      copy(Buf.tmvec[AngleNormVecI],Buf.tmvec[AngleBondVecKJ]);
      scale(Buf.tmvec[AngleNormVecI],Buf.post[AngleIvRabSin]);
      shift(Buf.tmvec[AngleNormVecI],-Buf.post[AngleIvRaSQCtg],
                                     Buf.tmvec[AngleBondVecIJ]);
      copy(Buf.tmvec[AngleNormVecK],Buf.tmvec[AngleBondVecIJ]);
      scale(Buf.tmvec[AngleNormVecK],Buf.post[AngleIvRabSin]);
      shift(Buf.tmvec[AngleNormVecK],-Buf.post[AngleIvRbSQCtg],
                                     Buf.tmvec[AngleBondVecKJ]);
    }
    T ef;
    dfunc(Buf.post.start,P,&ef);
    shift(Grad[I],+ef,Buf.tmvec[AngleNormVecI]);
    shift(Grad[J],-ef,Buf.tmvec[AngleNormVecI]);
    shift(Grad[K],+ef,Buf.tmvec[AngleNormVecK]);
    shift(Grad[J],-ef,Buf.tmvec[AngleNormVecK]);
  }

}

#endif

