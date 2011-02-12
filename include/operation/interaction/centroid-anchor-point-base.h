
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
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    Displacement(tmvec[0],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee;
    efunc(dsq,P+ExtObjectBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncCentroidAnchorPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    Displacement(tmvec[0],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ef;
    gfunc(dsq,P+ExtObjectBaseNumberParameter,ef);
    ef/=idx[1];
    unsigned int nb=idx[0],ne=nb+idx[1];
    for(unsigned int n=nb;n<ne;++n)
      shift(Gradient[idx[n]],ef,B.DisplaceVec);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncCentroidAnchorPointBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    Vector<T>& vP=
      *reinterpret_cast<Vector<T>*>(P[ExtObjectLocationPointer].ptr);
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    Displacement(tmvec[0],vP,B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee,ef;
    bfunc(dsq,P+ExtObjectBaseNumberParameter,ee,ef);
    Energy+=ee;
    ef/=idx[1];
    unsigned int nb=idx[0],ne=nb+idx[1];
    for(unsigned int n=nb;n<ne;++n)
      shift(Gradient[idx[n]],ef,B.DisplaceVec);
  }

}

#endif
