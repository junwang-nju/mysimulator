
#ifndef _Interaction_Func_Method_Pairwise_Both_H_
#define _Interaction_Func_Method_Pairwise_Both_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void BFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      InteractionBuffer<T>& Buf,
      void (*bfunc)(const T*,const Unique64Bit*,T*,T*)) {
    unsigned int I=idx[0], J=idx[1];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo);
      if(IsValid(Buf.inf)) Buf.GetPreBoth(&Buf,Buf.inf.start,Buf.pre.start);
      else Buf.pre[PairwiseDistanceSQ]=normSQ(Buf.tmvec[PairwiseBondVecIJ]);
      Buf.P2PBoth(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee,ef;
    bfunc(Buf.post.start,P,&ee,&ef);
    Energy+=ee;
    shift(Grad[I],+ef,Buf.tmvec[PairwiseBondVecIJ]);
    shift(Grad[J],-ef,Buf.tmvec[PairwiseBondVecIJ]);
  }

}

#endif

