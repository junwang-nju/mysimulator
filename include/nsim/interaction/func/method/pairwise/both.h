
#ifndef _Interaction_Func_Method_Pairwise_Both_H_
#define _Interaction_Func_Method_Pairwise_Both_H_

#include "interaction/buffer/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"
#include "array/1d/scale-copy.h"

namespace mysimulator {

  template <typename GT,typename T>
  void BMethodPairwise(
      const Array1D<Array1D<T> >& X,const Array1D<unsigned int>& ID,
      const Array1D<Unique64Bit>& P,InteractionBuffer<T>& Buf,const GT& Geo,
      T& Energy,Array1D<Array1D<T> >& Grad,
      void (*bfunc)(const Array1D<T>&,const Array1D<Unique64Bit>&,T*,T*)) {
    unsigned int I=ID[0],J=ID[1];
    if(Buf.postUpdate) {
      DisplacementCalc(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo,Buf.dim);
      if(Buf.inf.IsValid())   Buf.GetPreBoth();
      else Buf.pre[PairwiseDistanceSQ]
        =NormSQ(Buf.tmvec[PairwiseBondVecIJ],Buf.dim);
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

