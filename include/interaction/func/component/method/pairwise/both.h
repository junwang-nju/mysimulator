
#ifndef _Interaction_Function_Component_Method_Pairwise_Both_H_
#define _Interaction_Function_Component_Method_Pairwise_Both_H_

#include "unique-parameter/64bit/interface.h"
#include "vector/interface.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  void BFuncMethodPairwise(
      const Vector<T>* X,const unsigned int* idx,const UniqueParameter64Bit* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter64Bit*,T&,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=DistanceSqCalc(X[I],X[J],I,J,Geo,B);
    T ee,ef;
    bfunc(dsq,P,ee,ef);
    Energy+=ee;
    shift(Gradient[I],+ef,B.DisplaceVector);
    shift(Gradient[J],-ef,B.DisplaceVector);
  }

}

#endif

