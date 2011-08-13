
#ifndef _Interaction_Func_Method_Pairwise_Gradient_H_
#define _Interaction_Func_Method_Pairwise_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void GFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad, Array1DContent<T>* tmvec,
      void (*dfunc)(const T&,const Unique64Bit*,T&)) {
    unsigned int I=idx[0],J=idx[1];
    T dsq=DistanceSQ(tmvec[0],X[I],X[J],Geo);
    T ef;
    dfunc(dsq,P,ef);
    shift(Grad[I],+ef,tmvec[0]);
    shift(Grad[J],-ef,tmvec[0]);
  }

}

#endif

