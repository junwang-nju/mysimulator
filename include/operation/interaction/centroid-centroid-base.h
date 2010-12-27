
#ifndef _Interaction_Centroid_Centroid_Base_H_
#define _Interaction_Centroid_Centroid_Base_H_

#include "data/basic/unique-parameter.h"
#include "operation/geometry/mass-center.h"
#include "operation/geometry/distance-calc.h"

namespace std {

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void EFuncCentroidCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec, 
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    MassCenter(X,idx+idx[2],idx[3],tmvec[1]);
    Displacement(tmvec[0],tmvec[1],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    T ee;
    efunc(dsq,P,ee);
    Energy+=ee;
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void GFuncCentroidCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    MassCenter(X,idx+idx[2],idx[3],tmvec[1]);
    Displacement(tmvec[0],tmvec[1],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    double ef,ef0,ef1;
    gfunc(dsq,P,ef);
    ef0=ef/idx[1];
    ef1=ef/idx[3];
    for(unsigned int i=0,n=idx[0];i<idx[1];++i,++n)
      shift(Gradient[idx[n]],+ef0,B.DisplaceVec);
    for(unsigned int i=0,n=idx[2];i<idx[3];++i,++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncCentroidCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    MassCenter(X,idx+idx[0],idx[1],tmvec[0]);
    MassCenter(X,idx+idx[2],idx[3],tmvec[1]);
    Displacement(tmvec[0],tmvec[1],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    double ee,ef,ef0,ef1;
    bfunc(dsq,P,ee,ef);
    Energy+=ee;
    ef0=ef/idx[1];
    ef1=ef/idx[3];
    for(unsigned int i=0,n=idx[0];i<idx[1];++i,++n)
      shift(Gradient[idx[n]],+ef0,B.DisplaceVec);
    for(unsigned int i=0,n=idx[2];i<idx[3];++i,++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

}

#endif
