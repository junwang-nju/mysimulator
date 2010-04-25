
#ifndef _Distance_Displacement_Calculation_H_
#define _Distance_Displacement_Calculation_H_

#include "vector-op.h"

namespace std {

  template <typename GeomType>
  void DistanceDisplacementFunc(const VectorBase<double>& va,
                                const VectorBase<double>& vb,
                                VectorBase<double>& Dsp, double& DstSQ,
                                GeomType& Geo) {
    DisplacementFunc(va,vb,Dsp,Geo);
    DstSQ=normSQ(Dsp);
  }

}

#endif

