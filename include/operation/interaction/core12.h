
#ifndef _Interaction_Pairwise_Core12_H_
#define _Interaction_Pairwise_Core12_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/core12.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncCore12(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncCore12);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncCore12(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffCore12);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncCore12(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothCore12);
  }

}

#endif
