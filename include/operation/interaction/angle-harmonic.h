
#ifndef _Interaction_Angle_Harmonic_H_
#define _Interaction_Angle_Harmonic_H_

#include "operation/interaction/angle-base.h"
#include "operation/functional/angle-harmonic.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
    EFuncAngleBase(X,idx,P,B,Geo,Energy,FuncAngleHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec) {
    GFuncAngleBase(X,idx,P,B,Geo,Gradient,tmvec,DiffAngleHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec) {
    BFuncAngleBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,BothAngleHarmonic);
  }

}

#endif
