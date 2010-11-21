
#ifndef _Interaction_Pairwise_LJ612Cut_H_
#define _Interaction_Pairwise_LJ612Cut_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/lj612cut.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncLJ612Cut);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffLJ612Cut);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ612Cut);
  }

}

#endif

