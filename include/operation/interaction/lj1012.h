
#ifndef _Interaction_Pairwise_LJ1012_H_
#define _Interaction_Pairwise_LJ1012_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/lj1012.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncLJ1012(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncLJ1012);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncLJ1012(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffLJ1012);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncLJ1012(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ1012);
  }

}

#endif

