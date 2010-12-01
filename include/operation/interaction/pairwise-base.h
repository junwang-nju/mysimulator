
#ifndef _Interaction_Pairwise_Base_H_
#define _Interaction_Pairwise_Base_H_

#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=Distance(X[I],X[J],I,J,Geo,B),ee;
    efunc(dsq,P,ee);
    Energy+=ee;
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      void (*gfunc)(const T&,const UniqueParameter*,double&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=Distance(X[I],X[J],I,J,Geo,B),ef;
    gfunc(dsq,P,ef);
    shift(Gradient[I],+ef,B.DisplaceVec);
    shift(Gradient[J],-ef,B.DisplaceVec);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      void (*bfunc)(const double&,const UniqueParameter*,double&,double&)) {
    unsigned int I=idx[0], J=idx[1];
    T dsq=Distance(X[I],X[J],I,J,Geo,B),ee,ef;
    bfunc(dsq,P,ee,ef);
    Energy+=ee;
    shift(Gradient[I],+ef,B.DisplaceVec);
    shift(Gradient[J],-ef,B.DisplaceVec);
  }

}

#endif

