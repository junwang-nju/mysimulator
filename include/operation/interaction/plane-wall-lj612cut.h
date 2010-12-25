
#ifndef _Interaction_Plane_Wall_LJ612Cut_H_
#define _Interaction_Plane_Wall_LJ612Cut_H_

#include "operation/interaction/plane-wall-base.h"
#include "data/name/external-object-lj612cut.h"
#include "operation/functional/lj612cut.h"

namespace std {

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncPlaneWallLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncPlaneWallBase(X,idx,P,B,Geo,Energy,FuncLJ612Cut);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncPlaneWallLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    GFuncPlaneWallBase(X,idx,P,B,Geo,Gradient,DiffLJ612Cut);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncPlaneWallLJ612Cut(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    BFuncPlaneWallBase(X,idx,P,B,Geo,Energy,Gradient,BothLJ612Cut);
  }

}

#endif

