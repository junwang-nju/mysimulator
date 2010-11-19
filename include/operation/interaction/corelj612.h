
#ifndef _Interaction_Pairwise_CoreLJ612_H_
#define _Interaction_Pairwise_CoreLJ612_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/corelj612.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncCoreLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

