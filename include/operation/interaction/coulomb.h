
#ifndef _Interaction_Pairwise_Coulomb_H_
#define _Interaction_Pairwise_Coulomb_H_

#include "operation/interaction/pairwise-base.h"
#include "operation/functional/coulomb.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncCoulomb(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPairwiseBase(X,idx,P,B,Geo,Energy,FuncCoulomb);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncCoulomb(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPairwiseBase(X,idx,P,B,Geo,Gradient,DiffCoulomb);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncCoulomb(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPairwiseBase(X,idx,P,B,Geo,Energy,Gradient,BothCoulomb);
  }

}

#endif

