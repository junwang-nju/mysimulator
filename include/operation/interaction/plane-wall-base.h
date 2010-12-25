
#ifndef _Interaction_Plane_Wall_Base_H_
#define _Interaction_Plane_Wall_Base_H_

#include "data/name/external-object-base.h"
#include "data/name/plane-wall-property.h"
#include "data/basic/unique-parameter.h"
#include "data/geometry/distance-buffer-simple.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncPlaneWallBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&, const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    Vector<T>& nP=
      *reinterpret_cast<Vector<T>*>(
          (*reinterpret_cast<Vector<UniqueParameter>*>(
            P[ExtObjectPropertyPointer].ptr))[PlaneWallNormalDirectionPointer].ptr);
    T d=dot(B.DisplaceVec,nP);
    T dsq=d*d;
    T ee;
    efunc(dsq,P+ExtObjectBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncPlaneWallBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      void (*gfunc)(const T&, const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    Vector<T>& nP=
      *reinterpret_cast<Vector<T>*>(
          (*reinterpret_cast<Vector<UniqueParameter>*>(
            P[ExtObjectPropertyPointer].ptr))[PlaneWallNormalDirectionPointer].ptr);
    T d=dot(B.DisplaceVec,nP);
    T dsq=d*d;
    T ef;
    gfunc(dsq,P+ExtObjectBaseNumberParameter,ef);
    ef*=d;
    shift(Gradient[I],ef,nP);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncPlaneWallBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      void (*bfunc)(const T&, const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    Vector<T>& nP=
      *reinterpret_cast<Vector<T>*>(
          (*reinterpret_cast<Vector<UniqueParameter>*>(
            P[ExtObjectPropertyPointer].ptr))[PlaneWallNormalDirectionPointer].ptr);
    T d=dot(B.DisplaceVec,nP);
    T dsq=d*d;
    T ee,ef;
    bfunc(dsq,P+ExtObjectBaseNumberParameter,ee,ef);
    Energy+=ee;
    ef*=d;
    shift(Gradient[I],ef,nP);
  }

}

#endif

