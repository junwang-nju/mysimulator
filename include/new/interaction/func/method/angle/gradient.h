
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "distance/calc.h"
#include "array/1d/content/scale.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/angle/common/buffer/name.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad,InteractionBuffer<T>& Buf,
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int I=idx[0], J=idx[1], K=idx[2];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[0],X[I],X[J],Geo);
      DisplacementCalc(Buf.tmvec[1],X[K],X[J],Geo);
      if(IsValid(Buf.inf))  Buf.GetPreDiff(&Buf,Buf.inf.start,Buf.pre.start);
      else {
        Buf.pre[0]=normSQ(Buf.tmvec[0]);
        Buf.pre[1]=normSQ(Buf.tmvec[1]);
        Buf.pre[2]=dot(Buf.tmvec[0],tmvec[1]);
      }
      Buf.P2PDiff(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
      copy(Buf.tmvec[2],Buf.tmvec[1]);
      scale(Buf.tmvec[2],Buf.post[AngleIvRabSin]);
      shift(Buf.tmvec[2],-Buf.post[AngleIvRaSQCtg],Buf.tmvec[0]);
      copy(Buf.tmvec[3],Buf.tmvec[0]);
      scale(Buf.tmvec[3],Buf.post[AngleIvRabSin]);
      shift(Buf.tmvec[3],-Buf.post[AngleIvRbSQCtg],Buf.tmvec[1]);
    }
    T ef;
    dfunc(Buf.post.start,P,&ef);
    shift(Grad[I],+ef,Buf.tmvec[2]);
    shift(Grad[J],-ef,Buf.tmvec[2]);
    shift(Grad[K],+ef,Buf.tmvec[3]);
    shift(Grad[J],-ef,Buf.tmvec[3]);
  }

}

#endif

