
#ifndef _Geometry_Distance_Calc_H_
#define _Geometry_Distance_Calc_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename T,ArrayKernelName K>
  T __displacement_2_distance_sq(Array<Intrinsic<T>,K> const& Dsp) {
    return NormSQ(Dsp);
  }

  template <typename T,ArrayKernelName K>
  T __displacement_2_distance(Array<Intrinsic<T>,K> const& Dsp) {
    return Norm(Dsp);
  }

}

#include "geometry/displacement/calc.h"

namespace mysimulator {

  template <SystemKindName KA,SystemKindName KB,
            typename T,ArrayKernelName K,typename T1,ArrayKernelName K1,
            typename T2,ArrayKernelName K2,typename BdType>
  T DistanceSQ(Array<Intrinsic<T>,K>& Dsp, Array<Intrinsic<T1>,K1> const& B,
               Array<Intrinsic<T2>,K2> const& C, BdType const& Bdy) {
    DisplacementCalc<KA,KB>(Dsp,B,C,Bdy);
    return __displacement_2_distance_sq(Dsp);
  }

  template <SystemKindName KA,SystemKindName KB,
            typename T,ArrayKernelName K,typename T1,ArrayKernelName K1,
            typename T2,ArrayKernelName K2,typename BdType>
  T Distance(Array<Intrinsic<T>,K>& Dsp, Array<Intrinsic<T1>,K1> const& B,
             Array<Intrinsic<T2>,K2> const& C, BdType const& Bdy) {
    DisplacementCalc<KA,KB>(Dsp,B,C,Bdy);
    return __displacement_2_distance(Dsp);
  }

}

#endif

