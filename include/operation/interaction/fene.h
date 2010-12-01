
#ifndef _Interaction_Pairwise_FENE_H_
#define _Interaction_Pairwise_FENE_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/fene.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void EFuncFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncFENE);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffFENE);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncFENE(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothFENE);
  }

}

#endif
