
#ifndef _Distance_Calc_H_
#define _Distance_Calc_H_

#include "distance/displacement-2-distance.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename GeomType>
  T1 DistanceSQ(Array1DContent<T1>& A, const Array1DContent<T2>& B,
                const Array1DContent<T3>& C, const GeomType& Geo) {
    DisplacementCalc(A,B,C,Geo);
    return Displacement2DistanceSQ(A);
  }

  template <typename T1, typename T2, typename T3, typename GeomType>
  T1 Distance(Array1DContent<T1>& A, const Array1DContent<T2>& B,
              const Array1DContent<T3>& C, const GeomType& Geo) {
    DisplacementCalc(A,B,C,Geo);
    return Displacement2Distance(A);
  }

}

#if defined(_Boundary_Free_Interface_H_)
#include "displacement/free/calc.h"
#elif defined(_Boundary_PeriodBox_Interface_H_)
#include "displacement/period-box/calc.h"
#endif

#endif

