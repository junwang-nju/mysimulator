
#ifndef _Interaction_Core_Expanded_Pairwise_LJ612_H_
#define _Interaction_Core_Expanded_Pairwise_LJ612_H_

#include "operation/interaction/core-expanded-pairwise-base.h"
#include "operation/functional/lj612.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncCELJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncCEPairwiseBase(X,idx,P,B,Energy,FuncLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncCELJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncCEPairwiseBase(X,idx,P,B,Gradient,DiffLJ612);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncCELJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncCEPairwiseBase(X,idx,P,B,Energy,Gradient,BothLJ612);
  }

}

#endif
