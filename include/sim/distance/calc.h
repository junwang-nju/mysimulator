
#define _Distance_Calc_H_
#define _Distance_Calc_H_

#include "distance/displacement-2-distance.h"

namespace mysimulator {

  template <typename T1, typename T2, typename T3, typename GeomType>
  T1 DistanceSQ(T1* p, const T2* q, const T3* r, const GeomType& Geo,
                unsigned int n) {
    DisplacementCalc(p,q,r,Geo,n);
    return Displacement2DistanceSQ(p,n);
  }

  template <typename T1, typename T2, typename T3, typename GeomType>
  T1 Distance(T1* p, const T2* q, const T3* r, const GeomType& Geo,
              unsigned int n) {
    DisplacementCalc(p,q,r,Geo,n);
    return Displacement2Distance(p,n);
  }

}

#endif

