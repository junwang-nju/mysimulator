
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/angle/common/buffer/pre-name.h"
#include "interaction/func/impl/angle/common/buffer/vec-name.h"
#include "interaction/func/impl/angle/common/buffer/post-name.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GMethodAngle(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T** Grad,InteractionBuffer<T>& Buf,
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int I=id[0],J=id[1],K=id[2];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[AngleBondVecIJ],X[I],X[J],Geo,Buf.dim);
      DisplacementCalc(Buf.tmvec[AngleBondVecKJ],X[K],X[J],Geo,Buf.dim);
      if(Buf.inf!=NULL)   Buf.GetPreDiff();
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

