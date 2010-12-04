
#ifndef _Interaction_Core_Expanded_Pairwise_Base_H_
#define _Interaction_Core_Expanded_Pairwise_Base_H_

#include "data/name/core-expanded-base.h"
#include "data/basic/unique-parameter.h"
#include "operation/basic/vector-op.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncCEPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      void (*efunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T cdsq=Distance(X[I],X[J],I,J,Geo,B);
    T cd=sqroot(cdsq);
    T d=cd-P[CoreExpandedCoreRadius].value<T>();
    assert(d>=0.);
    T dsq=d*d,ee;
    efunc(dsq,P+CoreExpandedBaseNumberParameter,ee);
    Energy+=ee;
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncCEPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      void (*gfunc)(const T&,const UniqueParameter*,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T cdsq=Distance(X[I],X[J],I,J,Geo,B);
    T cd=sqroot(cdsq);
    T d=cd-P[CoreExpandedCoreRadius].value<T>();
    assert(d>=0.);
    T dsq=d*d,ef;
    gfunc(dsq,P+CoreExpandedBaseNumberParameter,ef);
    ef*=d/cd;
    shift(Gradient[I],+ef,B.DisplaceVec);
    shift(Gradient[J],-ef,B.DisplaceVec);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncCEPairwiseBase(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      void (*bfunc)(const T&,const UniqueParameter*,T&,T&)) {
    unsigned int I=idx[0], J=idx[1];
    T cdsq=Distance(X[I],X[J],I,J,Geo,B);
    T cd=sqroot(cdsq);
    T d=cd-P[CoreExpandedCoreRadius].value<T>();
    assert(d>=0.);
    T dsq=d*d,ee,ef;
    bfunc(dsq,P+CoreExpandedBaseNumberParameter,ee,ef);
    Energy+=ee;
    ef*=d/cd;
    shift(Gradient[I],+ef,B.DisplaceVec);
    shift(Gradient[J],-ef,B.DisplaceVec);
  }

}

#endif
