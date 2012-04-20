
#ifndef _Interaction_Func_Method_Pairwise_Both_H_
#define _Interaction_Func_Method_Pairwise_Both_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  // assuming dimension is small
  template <typename GeomType, typename T>
  void BMethodPairwise(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T& Energy, T** Grad, InteractionBuffer<T>& Buf,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    unsigned int I=id[0],J=id[1];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo,Buf.dim);
      if(Buf.inf!=NULL) Buf.GetPreBoth();
      else Buf.pre[PairwiseDistanceSQ]=NormSQ(Buf.tmvec[PairwiseBondVecIJ],
                                              Buf.dim);
      Buf.Pre2PostBoth(P);
    }
    T ee,ef;
    bfunc(Buf.post,P,&ee,&ef);
    Energy+=ee;
    ScaleCopy(Buf.tmvec[PairwiseScaledBondVecIJ],
              Buf.tmvec[PairwiseBondVecIJ],ef,Buf.dim);
    Shift(Grad[I],Buf.tmvec[PairwiseScaledBondVecIJ],Buf.dim);
    NegShift(Grad[J],Buf.tmvec[PairwiseScaledBondVecIJ],Buf.dim);
  }

}

#endif

