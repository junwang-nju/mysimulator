
#ifndef _Interaction_Ancher_Point_Harmonic_H_
#define _Interaction_Ancher_Point_Harmonic_H_

#include "operation/interaction/ancher-point-base.h"
#include "data/name/external-object-harmonic.h"
#include "operation/functional/harmonic.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncAncherPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncAncherPointBase(X,idx,P,B,Geo,Energy,FuncHarmonic);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncAncherPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncAncherPointBase(X,idx,P,B,Geo,Gradient,DiffHarmonic);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncAncherPointHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncAncherPointBase(X,idx,P,B,Geo,Energy,Gradient,BothHarmonic);
  }

}

#endif

