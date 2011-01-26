
#ifndef _Interaction_Spheric_Shell_Base_H_
#define _Interaction_Spheric_Shell_Base_H_

#include "data/name/external-object-base.h"
#include "data/name/spheric-shell-property.h"
#include "data/basic/unique-parameter.h"
#include "operation/geometry/distance-calc.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncSphericShellBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
        *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T ddsq=displacement2distanceSQ(B.DisplaceVec);
    Vector<UniqueParameter>& sP=*reinterpret_cast<Vector<UniqueParameter>*>(
        P[ExtObjectPropertyPointer].ptr);
    T fg=sP[SphericShellDirection].value<T>();
    assert((ddsq-sP[SphericShellRadiusSQ].value<T>())*fg>0);
    T d=(sqroot(ddsq)-sP[SphericShellRadius].value<T>())*fg;
    T dsq=d*d;
    T ee;
    efunc(dsq,P+ExtObjectBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncSphericShellBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
        *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T ddsq=displacement2distanceSQ(B.DisplaceVec);
    Vector<UniqueParameter>& sP=*reinterpret_cast<Vector<UniqueParameter>*>(
        P[ExtObjectPropertyPointer].ptr);
    T fg=sP[SphericShellDirection].value<T>();
    assert((ddsq-sP[SphericShellRadiusSQ].value<T>())*fg>0);
    T rd=sqroot(ddsq);
    T d=(rd-sP[SphericShellRadius].value<T>())*fg;
    T dsq=d*d;
    T ef;
    gfunc(dsq,P+ExtObjectBaseNumberParameter,ef);
    ef*=d/rd;
    shift(Gradient[I],ef,B.DisplaceVec);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncSphericShellBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0];
    Vector<T>& vP=
        *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    Displacement(X[I],vP,B.DisplaceVec,Geo);
    T ddsq=displacement2distanceSQ(B.DisplaceVec);
    Vector<UniqueParameter>& sP=*reinterpret_cast<Vector<UniqueParameter>*>(
        P[ExtObjectPropertyPointer].ptr);
    T fg=sP[SphericShellDirection].value<T>();
    assert((ddsq-sP[SphericShellRadiusSQ].value<T>())*fg>0);
    T rd=sqroot(ddsq);
    T d=(rd-sP[SphericShellRadius].value<T>())*fg;
    T dsq=d*d;
    T ee,ef;
    bfunc(dsq,P+ExtObjectBaseNumberParameter,ee,ef);
    Energy+=ee;
    ef*=d/rd;
    shift(Gradient[I],ef,B.DisplaceVec);
  }

}

#endif
