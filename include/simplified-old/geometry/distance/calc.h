
#ifndef _Geometry_Distance_Calc_H_
#define _Geometry_Distance_Calc_H_

#include "array/interface.h"

namespace mysimulator {

  template <typename T>
  T Displacement2DistanceSQ(Array<Intrinsic<T>> const& A) { return A.NormSQ(); }

  template <typename T>
  T Displacement2Distance(Array<Intrinsic<T>> const& A) { return A.Norm(); }

}

#include "geometry/displacement/calc.h"

namespace mysimulator {

  template <SystemKindName KA,SystemKindName KB,
            typename T,typename T1,typename T2,typename BoundaryType>
  T DistanceSQ(Array<Intrinsic<T>>& Dsp, Array<Intrinsic<T1>> const& B,
                                         Array<Intrinsic<T2>> const& C,
               BoundaryType const& Bdy) {
    DisplacementCalc<KA,KB>(Dsp,B,C,Bdy);
    return Displacement2DistanceSQ(Dsp);
  }

  template <SystemKindName KA,SystemKindName KB,
            typename T,typename T1,typename T2,typename BoundaryType>
  T Distance(Array<Intrinsic<T>>& Dsp, Array<Intrinsic<T1>> const& B,
                                       Array<Intrinsic<T2>> const& C,
             BoundaryType const& Bdy) {
    DisplacementCalc<KA,KB>(Dsp,B,C,Bdy);
    return Displacement2Distance(Dsp);
  }

}

#endif

