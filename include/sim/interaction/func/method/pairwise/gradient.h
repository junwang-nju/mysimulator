
#ifndef _Interaction_Func_Method_Pairwise_Gradient_H_
#define _Interaction_Func_Method_Pairwise_Gradient_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"

namespace mysimulator {

  // assuming dimension is small
  template <typename GeomType, typename T>
  void GMethodPairwise(
      T** const X,const int* id,const Unique64Bit* P,const GeomType& Geo,
      T** Grad,InteractionBuffer<T>& Buf,
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    unsigned int I=id[0],J=id[1];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo,Buf.dim);
      if(Buf.inf!=NULL) Buf.GetPreDiff();
      else Buf.pre[PairwiseDistanceSQ]=NormSQ(Buf.tmvec[PairwiseBondVecIJ],
                                              Buf.dim);
    }
    T ef;
    dfunc(Buf.post,P,&ef);
    Shift(Grad[I],+ef,Buf.tmvec[PairwiseBondVecIJ],Buf.dim);
    Shift(Grad[J],-ef,Buf.tmvec[PairwiseBondVecIJ],Buf.dim);
  }

}

#endif

