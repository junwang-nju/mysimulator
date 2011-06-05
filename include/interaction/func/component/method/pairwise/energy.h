
#ifndef _Interaction_Function_Component_Method_Pairwise_Energy_H_
#define _Interaction_Function_Component_Method_Pairwise_Energy_H_

#include "unique-parameter/64bit/interface.h"
#include "vector/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  void EFuncMethodPairwise(
      const Vector<T>* X,const unsigned int* idx,const UniqueParameter64Bit* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* tmvec,
      void (*efunc)(const T&,const UniqueParameter64Bit*,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=DistanceSqCalc(X[I],X[J],I,J,Geo,B);
    T ee;
    efunc(dsq,P,ee);
    Energy+=ee;
  }

}

#endif

