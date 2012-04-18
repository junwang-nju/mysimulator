
#ifndef _Interaction_Func_Method_Pairwise_Energy_H_
#define _Interaction_Func_Method_Pairwise_Energy_H_

#include "distance/calc.h"
#include "interaction/buffer/interface.h"
#include "interaction/func/impl/pairwise/common/buffer/pre-name.h"
#include "interaction/func/impl/pairwise/common/buffer/vec-name.h"
#include <iostream>

namespace mysimulator {

  // assuming dimension is small
  template <typename GeomType, typename T>
  void EMethodPairwise(
      T** const X,const unsigned int* id,const Unique64Bit* P,
      const GeomType& Geo,T& Energy, InteractionBuffer<T>& Buf,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    if(Buf.postUpdate) {
      std::cout<<"====0======="<<std::endl;
      if(Buf.inf!=NULL) Buf.GetPreFunc();
      else {
        unsigned int I=id[0],J=id[1];
      std::cout<<"====1======="<<std::endl;
        Buf.pre[PairwiseDistanceSQ]=
          DistanceSQ(Buf.tmvec[PairwiseBondVecIJ],X[I],X[J],Geo,Buf.dim);
      std::cout<<"====2======="<<std::endl;
      }
      std::cout<<"====3======="<<std::endl;
      Buf.Pre2PostFunc(P);
      std::cout<<"====4======="<<std::endl;
    }
    T ee;
      std::cout<<"====5======="<<std::endl;
    efunc(Buf.post,P,&ee);
      std::cout<<"====6======="<<std::endl;
    Energy+=ee;
  }

}

#endif

