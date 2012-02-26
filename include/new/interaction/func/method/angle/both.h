
#ifndef _Interaction_Func_Mehtod_Angle_Both_H_
#define _Interaction_Func_Mehtod_Angle_Both_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void BFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, T& Energy, Array1DContent<T>* Grad,
      Array1DContent<T>* tmvec,
      void (*bfunc)(const T&,const Unique64Bit*,T&,T&)) {
  }

}

#endif

