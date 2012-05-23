
#ifndef _Distance_Calc_H_
#define _Distance_Calc_H_

#include "distance/displacement-2-distance.h"

namespace mysimulator {

  template <typename T,typename T2,typename T3,typename GeomType>
  T DistanceSQ(ArrayNumeric<T>& Dsp,const ArrayNumeric<T1>& X,
               const ArrayNumeric<T2>& Y,const GeomType& Geo) {
    DisplacementCalc(Dsp,X,Y,Geo);
    return Displacement2DistanceSQ(Dsp);
  }

  template <typename T,typename T2,typename T3,typename GeomType>
  T Distance(ArrayNumeric<T>& Dsp,const ArrayNumeric<T1>& X,
             const ArrayNumeric<T2>& Y,const GeomType& Geo) {
    DisplacementCalc(Dsp,X,Y,Geo);
    return Displacement2Distance(Dsp);
  }

}

#endif

