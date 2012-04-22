
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "interaction/buffer/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"
#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  template <typename GT,typename T>
  void GMethodAngle(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      Array1D<Array1D<T> >& Grad,
      void (*dfunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*)) {
    unsigned int I=ID[0],J=ID[1],K=ID[2];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[AngleBondVecIJ],X[I],X[J],Geo,Buf.dim);
      DisplacementCalc(Buf.tmvec[AngleBondVecKJ],X[K],X[J],Geo,Buf.dim);
      if(Buf.inf.IsValid())   Buf.GetPreDiff();
      else {
        Buf.pre[AngleEdgeASQ]=NormSQ(Buf.tmvec[AngleBondVecIJ],Buf.dim);
        Buf.pre[AngleEdgeBSQ]=NormSQ(Buf.tmvec[AngleBondVecKJ],Buf.dim);
      }
      Buf.pre[AngleDotAB]=
        Dot(Buf.tmvec[AngleBondVecIJ],Buf.tmvec[AngleBondVecKJ],Buf.dim);
      Buf.Pre2PostDiff(P);
      ScaleCopy(Buf.tmvec[AngleNormVecI],
                Buf.tmvec[AngleBondVecKJ],Buf.post[AngleIvRabSin],Buf.dim);
      Shift(Buf.tmvec[AngleNormVecI],
            -Buf.post[AngleIvRaSQCtg],Buf.tmvec[AngleBondVecIJ],Buf.dim);
      ScaleCopy(Buf.tmvec[AngleNormVecK],
                Buf.tmvec[AngleBondVecIJ],Buf.post[AngleIvRabSin],Buf.dim);
      Shift(Buf.tmvec[AngleNormVecK],
            -Buf.post[AngleIvRbSQCtg],Buf.tmvec[AngleBondVecKJ],Buf.dim);
    }
    T ef;
    dfunc(Buf.post,P,&ef);
    ScaleCopy(Buf.tmvec[AngleScaledNormVecI],
              Buf.tmvec[AngleNormVecI],ef,Buf.dim);
    ScaleCopy(Buf.tmvec[AngleScaledNormVecK],
              Buf.tmvec[AngleNormVecK],ef,Buf.dim);
    Shift(Grad[I],Buf.tmvec[AngleScaledNormVecI],Buf.dim);
    NegShift(Grad[J],Buf.tmvec[AngleScaledNormVecI],Buf.dim);
    Shift(Grad[K],Buf.tmvec[AngleScaledNormVecK],Buf.dim);
    NegShift(Grad[J],Buf.tmvec[AngleScaledNormVecK],Buf.dim);
  }

}

#endif

