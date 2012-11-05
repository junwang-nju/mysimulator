
#ifndef _Geometry_Displacement_Calc_H_
#define _Geometry_Displacement_Calc_H_

#include "geometry/displacement/_calc.h"

namespace mysimulator {

  template <SystemKindName KA,SystemKindName KB,
            typename T,typename T1,typename T2,typename BoundaryType>
  void DisplacementCalc(Array<T>& A,Array<T1> const& A1,Array<T2> const& A2,
                        BoundaryType const& Bdy) {
    _Displacement<KA,KB>::Calc(A,A1,A2,Bdy);
  }

}

#endif

