
#ifndef _Distance_Calc_H_
#define _Distance_Calc_H_

#include "distance/displacement-2-distance.h"

namespace mysimulator {

  template <typename T1,typename T2,typename T3,typename GeomType>
  T1 DistanceSQ(Array1D<T1>& Disp,const Array1D<T2>& X,const Array1D<T3>& Y,
                const GeomType& Geo, unsigned int dim) {
    DisplacementCalc(Disp,X,Y,Geo,dim);
    return Displacement2DistanceSQ(Disp,dim);
  }

  template <typename T1,typename T2,typename T3,typename GeomType>
  T1 Distance(Array1D<T1>& Disp,const Array1D<T2>& X,const Array1D<T3>& Y,
              const GeomType& Geo, unsigned int dim) {
    DisplacementCalc(Disp,X,Y,Geo,dim);
    return Displacement2Distance(Disp,dim);
  }

}

#endif

