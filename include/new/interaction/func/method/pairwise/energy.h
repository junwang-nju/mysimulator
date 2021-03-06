
#ifndef _Interaction_Func_Method_Pairwise_Energy_H_
#define _Interaction_Func_Method_Pairwise_Energy_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      if(IsValid(Buf.inf))  Buf.GetPreFunc(&Buf);
      else
        Buf.pre[PairwiseDistanceSQ]=
          DistanceSQ(Buf.tmvec[PairwiseBondVecIJ],X[idx[0]],X[idx[1]],Geo);
      Buf.P2PFunc(Buf.pre.start,P,Buf.post.start,Buf.postUpdate);
    }
    T ee;
    efunc(Buf.post.start,P,&ee);
    Energy+=ee;
  }

}

#endif

