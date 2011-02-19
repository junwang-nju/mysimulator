
#ifndef _Interaction_Plane_Wall_CoreLJ612_H_
#define _Interaction_Plane_Wall_CoreLJ612_H_

#include "operation/interaction/plane-wall-base.h"
#include "data/name/external-object-corelj612.h"
#include "operation/functional/corelj612.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncPlaneWallCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncPlaneWallBase(X,idx,P,B,Geo,Energy,FuncCoreLJ612);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncPlaneWallCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncPlaneWallBase(X,idx,P,B,Geo,Gradient,DiffCoreLJ612);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncPlaneWallCoreLJ612(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    BFuncPlaneWallBase(X,idx,P,B,Geo,Energy,Gradient,BothCoreLJ612);
  }

}

#endif

