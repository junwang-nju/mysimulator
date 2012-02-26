
#ifndef _Interaction_Func_Method_Angle_Gradient_H_
#define _Interaction_Func_Method_Angle_Gradient_H_

#include "unique/64bit/interface.h"
#include "distance/calc.h"

namespace mysimulator {

  template <typename GeomType,typename T>
  void GFuncMethodAngle(
      const Array1DContent<T>* X, const int* idx, const Unique64Bit* P,
      const GeomType& Geo, Array1DContent<T>* Grad, Array1DContent<T>* tmvec,
      void (*dfunc)(const T&,const Unique64Bit*,T&)) {
  }

}

#endif

