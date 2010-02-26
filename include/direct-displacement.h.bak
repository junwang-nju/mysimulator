
#ifndef _Direct_Displacement_H_
#define _Direct_Displacement_H_

#include "vector-base.h"

namespace std {

  void DirectDisplacement(const VectorBase<double>& va,
                          const VectorBase<double>& vb,
                          VectorBase<double>& Dsp) {
    Dsp=va;
    Dsp.shift(-1.,vb);
  }

}

#endif

