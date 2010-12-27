
#ifndef _Interaction_Particle_Centroid_Base_H_
#define _Interaction_Particle_Centroid_Base_H_

#include "data/basic/unique-parameter.h"
#include "operation/geometry/mass-center.h"
#include "operation/geometry/distance-calc.h"

namespace std {

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void EFuncParticleCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    MassCenter(X,idx+idx[1],idx[2],tmvec[0]);
    Displacement(X[I],tmvec[0],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee;
    efunc(dsq,P,ee);
    Energy+=ee;
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void GFuncParticleCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0];
    MassCenter(X,idx+idx[1],idx[2],tmvec[0]);
    Displacement(X[I],tmvec[0],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ef,ef1;
    gfunc(dsq,P,ef);
    ef1=ef/idx[2];
    shift(Gradient[I],+ef,B.DisplaceVec);
    for(unsigned int i=0,n=idx[1];i<idx[2];++i,++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

  template <typename T, template<typename> class DBuffer, typename GeomType>
  void BFuncParticleCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0];
    MassCenter(X,idx+idx[1],idx[2],tmvec[0]);
    Displacement(X[I],tmvec[0],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee,ef,ef1;
    bfunc(dsq,P,ee,ef);
    Energy+=ee;
    ef1=ef/idx[2];
    shift(Gradient[I],+ef,B.DisplaceVec);
    for(unsigned int i=0,n=idx[1];i<idx[2];++i,++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

}

#endif
