
#ifndef _Interaction_Driving_Constant_Force_H_
#define _Interaction_Driving_Constant_Force_H_

#include "data/name/driving-constant.h"
#include "data/basic/unique-parameter.h"

namespace std {

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void EFuncDrivingConstant(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy,
      Vector<T>* tmvec=NULL) {
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void GFuncDrivingConstant(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    unsigned int I=idx[0];
    Vector<T>& fV=*reinterpret_cast<Vector<T>*>(P[ConstantDrivingForce].ptr);
    shift(Gradient[I],+1.,fV);
  }

  template <typename T,template<typename> class DistBuffer,typename GeomType>
  void BFuncDrivingConstant(
      const Vector<T>* X, const unsigned int* idx, const UniqueParameter* P,
      DistBuffer<T>& B, const GeomType& Geo, T& Energy, Vector<T>* Gradient,
      Vector<T>* tmvec=NULL) {
    GFuncDrivingConstant(X,idx,P,B,Geo,Gradient);
  }

}

#endif

