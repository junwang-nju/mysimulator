
#ifndef _Interaction_Function_Component_Method_Pairwise_Gradient_H_
#define _Interaction_Function_Component_Method_Pairwise_Gradient_H_

#include "unique-parameter/64bit/interface.h"
#include "vector/shift.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  void GFuncMethodPairwise(
      const Vector<T>* X,const unsigned int* idx,const UniqueParameter64Bit* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient, Vector<T>* tmvec,
      void (*dfunc)(const T&,const UniqueParameter64Bit*,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=DistanceSqCalc(X[I],X[J],I,J,Geo,B);
    T ef;
    dfunc(dsq,P,ef);
    shift(Gradient[I],+ef,B.DisplaceVector);
    shift(Gradient[J],-ef,B.DisplaceVector);
  }

}

#endif

