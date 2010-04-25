
#ifndef _Distance_Displacement_Calculation_H_
#define _Distance_Displacement_Calculation_H_

#include "vector.h"

namespace std {

  template <typename GeomType>
  void DistanceDisplacementFunc(const double* va, const double* vb,
                                const unsigned int dim, double* Dsp, double& D2,
                                const GeomType& Geo,
                                const int aoff=iZero, const long astep=lOne,
                                const int boff=iZero, const long bstep=lOne,
                                const int doff=iZero, const long dstep=lOne) {
    DisplacementFunc(va,vb,dim,Dsp,Geo,aoff,astep,boff,bstep,doff,dstep);
    D2=normSQ(Dsp,dim,doff,dstep);
  }

  template <typename GeomType>
  void DistanceDisplacementFunc(const Vector<double>& va,
                                const Vector<double>& vb,
                                Vector<double>& Dsp, double& D2,
                                const GeomType& Geo) {
    DisplacementFunc(va,vb,Dsp,Geo);
    D2=normSQ(Dsp);
  }

}

#endif

