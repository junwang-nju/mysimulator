
#ifndef _Interaction_Func_Method_Pairwise_Gradient_H_
#define _Interaction_Func_Method_Pairwise_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"
#include "interaction/func/impl/common/parameter/name.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void GFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad, Array1DContent<T>* tmvec,
      void (*dfunc)(const T*,const Unique64Bit*,T*)) {
    assert(IsValid(tmvec));
    T* buffer=reinterpret_cast<T*>(P[InteractionBuffer].ptr[0]);
    unsigned int I=idx[0],J=idx[1];
    T dsq;
    if(buffer==NULL) dsq=DistanceSQ(tmvec[0],X[I],X[J],Geo);
    else {
      dsq=*buffer;
      _copy(tmvec[0].start,buffer+1,tmvec[0].size);
    }
    T ef;
    dfunc(&dsq,P,&ef);
    shift(Grad[I],+ef,tmvec[0]);
    shift(Grad[J],-ef,tmvec[0]);
  }

}

#endif

