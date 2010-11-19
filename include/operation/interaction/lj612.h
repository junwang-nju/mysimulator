
#ifndef _Interaction_Pairwise_LJ612_H_
#define _Interaction_Pairwise_LJ612_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/lj612.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, double& Energy,
      Vector<double>* Gradient) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ612);
  }

}

#endif

