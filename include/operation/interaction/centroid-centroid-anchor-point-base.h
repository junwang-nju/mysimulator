
#ifndef _Interaction_Centroid_Anchor_Point_Base_H_
#define _Interaction_Centroid_Anchor_Point_Base_H_

#include "data/name/external-object-base.h"
#include "data/basic/unique-parameter.h"
#include "operation/geometry/mass-center.h"
#include "operation/geometry/distance-calc.h"

namespace std {
  
  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncCentroidAnchorPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    T ee;
    Energy+=ee;
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncCentroidAnchorPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncCentroidAnchorPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
  }

}

#endif
