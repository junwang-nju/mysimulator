
#ifndef _Interaction_Pairwise_LJ1012Cut_H_
#define _Interaction_Pairwise_LJ1012Cut_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/lj1012cut.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncLJ1012Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncLJ1012Cut);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncLJ1012Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffLJ1012Cut);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncLJ1012Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ1012Cut);
  }

}

#endif

