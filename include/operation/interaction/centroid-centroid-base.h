
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
    MassCenter(X,idx+idx[0]+idx[1],idx[2],tmvec[1]);
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
    unsigned int nb1=idx[0],ne1=nb1+idx[1];
    unsigned int nb2=ne1,ne2=nb2+idx[2];
    MassCenter(X,idx+nb1,idx[1],tmvec[0]);
    MassCenter(X,idx+nb2,idx[2],tmvec[1]);
    Displacement(tmvec[0],tmvec[1],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    double ef,ef0,ef1;
    gfunc(dsq,P,ef);
    ef0=ef/idx[1];
    ef1=ef/idx[2];
    for(unsigned int n=nb1;n<ne1;++n)
      shift(Gradient[idx[n]],+ef0,B.DisplaceVec);
    for(unsigned int n=nb2;n<ne2;++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

  template <typename T,template<typename> class DBuffer,typename GeomType>
  void BFuncCentroidCentroidBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int nb1=idx[0],ne1=nb1+idx[1];
    unsigned int nb2=ne1,ne2=nb2+idx[2];
    MassCenter(X,idx+nb1,idx[1],tmvec[0]);
    MassCenter(X,idx+nb2,idx[2],tmvec[1]);
    Displacement(tmvec[0],tmvec[1],B.DisplaceVec,Geo);
    T dsq=displacement2distanceSQ(B.DisplaceVec);
    double ee,ef,ef0,ef1;
    bfunc(dsq,P,ee,ef);
    Energy+=ee;
    ef0=ef/idx[1];
    ef1=ef/idx[2];
    for(unsigned int n=nb1;n<ne1;++n)
      shift(Gradient[idx[n]],+ef0,B.DisplaceVec);
    for(unsigned int n=nb2;n<ne2;++n)
      shift(Gradient[idx[n]],-ef1,B.DisplaceVec);
  }

}

#endif
