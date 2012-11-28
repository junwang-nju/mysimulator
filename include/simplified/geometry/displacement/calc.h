
#ifndef _Geometry_Displacement_Calc_H_
#define _Geometry_Displacement_Calc_H_

#include "geometry/displacement/operation.h"

namespace mysimulator {

  template <SystemKindName KA,SystemKindName KB,
            typename T,ArrayKernelName K,typename T1,ArrayKernelName K1,
            typename T2,ArrayKernelName K2,typename BdType>
  void DisplacementCalc(
      Array<Intrinsic<T>,K>& A, Array<Intrinsic<T1>,K1> const& A1,
      Array<Intrinsic<T2>,K2> const& A2, BdType const& Bdy) {
    __Displacement<KA,KB,BdType::Dimension>::Calc(A,A1,A2,Bdy);
  }

}

#endif

