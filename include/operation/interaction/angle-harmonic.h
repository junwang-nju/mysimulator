
#ifndef _Interaction_Angle_Harmonic_H_
#define _Interaction_Angle_Harmonic_H_

#include "operation/interaction/interaction-angle-base.h"
#include "operation/functional/functional-angle-harmonic.h"

namespace std {

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void EFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL, const unsigned int idxsize=0) {
    EFuncAngleBase(X,idx,P,B,Geo,Energy,FuncAngleHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void GFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    GFuncAngleBase(X,idx,P,B,Geo,Gradient,tmvec,DiffAngleHarmonic);
  }

  template <typename T,template <typename> class DistBuffer,typename GeomType>
  void BFuncAngleHarmonic(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec, const unsigned int idxsize=0) {
    BFuncAngleBase(X,idx,P,B,Geo,Energy,Gradient,tmvec,DiffAngleHarmonic);
  }

}

#endif
