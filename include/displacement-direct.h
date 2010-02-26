
#ifndef _Displacement_Direct_H_
#define _Displacement_Direct_H_

#include "vector-base.h"

namespace std {

  void DisplacementFunc(const VectorBase<double>& va,
                        const VectorBase<double>& vb,
                        VectorBase<double>& Dsp) {
    Dsp=va;
    Dsp.shift(-1.,vb);
  }

}

#endif

