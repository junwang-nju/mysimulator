
#ifndef _Displacement_DIrect_H_
#define _Displacement_DIrect_H_

#include "vector.h"

namespace std {

  void DisplacementFunc(const double* va, const double* vb,
                        const unsigned int dim, double* Dsp,
                        const int aoff=iZero, const long astep=lOne,
                        const int boff=iZero, const long bstep=lOne,
                        const int doff=iZero, const long dstep=lOne) {
    assign(Dsp,va,dim,aoff,astep,doff,dstep);
    shift(Dsp,-1.,vb,dim,boff,bstep,doff,dstep);
  }

  void DisplacementFunc(const Vector<double>& va, const Vector<double>& vb,
                        Vector<double>& Dsp) {
    assign(Dsp,va);
    shift(Dsp,-1.,vb);
  }

}

#endif

