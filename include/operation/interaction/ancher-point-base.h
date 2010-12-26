
#ifndef _Interaction_Ancher_Point_Base_H_
#define _Interaction_Ancher_Point_Base_H_

#include "data/name/external-object-base.h"
#include "data/basic/unique-parameter.h"
#include "operation/geometry/distance-calc.h"

namespace std {

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncAncherPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&, const UniqueParameter*, T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee;
    efunc(dsq,P+ExtObjectBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncAncherPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      void (*gfunc)(const T&, const UniqueParameter*, T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ef;
    gfunc(dsq,P+ExtObjectBaseNumberParameter,ef);
    shift(Gradient[I],ef,B.DisplaceVec);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncAncherPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee,ef;
    bfunc(dsq,P+ExtObjectBaseNumberParameter,ee,ef);
    Energy+=ee;
    shift(Gradient[I],ef,B.DisplaceVec);
  }

}

#endif

