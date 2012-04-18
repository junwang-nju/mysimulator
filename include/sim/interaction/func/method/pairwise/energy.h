
#ifndef _Interaction_Func_Method_Pairwise_Energy_H_
#define _Interaction_Func_Method_Pairwise_Energy_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"

namespace mysimulator {

  // assuming dimension is small
  template <typename GeomType, typename T>
  void EMethodPairwise(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      if(Buf.inf!=NULL) Buf.GetPreFunc();
      else {
        unsigned int I=id[0],J=id[1];
        Buf.pre[PairwiseDistanceSQ]=
          DistanceSQ(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo,Buf.dim);
      }
      Buf.Pre2PostFunc(P);
    }
    T ee;
    efunc(Buf.post,P,&ee);
    Energy+=ee;
  }

}

#endif

