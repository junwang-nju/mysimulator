
#ifndef _Interaction_Func_Method_Pairwise_Energy_H_
#define _Interaction_Func_Method_Pairwise_Energy_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void EFuncMethodPairwise(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* tmvec,
      void (*efunc)(const T*,const Unique64Bit*,T*)) {
    T dsq=DistanceSQ(tmvec[0],X[idx[0]],X[idx[1]],Geo);
    T ee;
    efunc(&dsq,P,&ee);
    Energy+=ee;
  }

}

#endif

