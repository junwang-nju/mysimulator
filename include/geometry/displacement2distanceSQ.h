
#ifndef _Geometry_Displacement_To_DistanceSQ_H_
#define _Geometry_Displacement_To_DistanceSQ_H_

#include "intrinsic-type/constant.h"
#include "linear-algebra/blas.h"

namespace mysimulator {

  double displacement2distanceSq(
      const double* dsp, const unsigned int n,
      const int off=iZero, const long step=lOne) {
    return ddot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
                 const_cast<double*>(dsp)+off,const_cast<long*>(&step),
                 const_cast<double*>(dsp)+off,const_cast<long*>(&step));
  }

  double displacement2distanceSq(
      const float* dsp, const unsigned int n,
      const int off=iZero, const long step=lOne) {
    return sdot_(reinterpret_cast<long*>(const_cast<unsigned int*>(&n)),
                 const_cast<float*>(dsp)+off,const_cast<long*>(&step),
                 const_cast<float*>(dsp)+off,const_cast<long*>(&step));
  }

  unsigned int displacement2distanceSq(
      const unsigned int* dsp, const unsigned int n,
      const int off=iZero, const long step=lOne) {
    unsigned int s=0;
    unsigned int *p=const_cast<unsigned int*>(dsp)+off;
    unsigned int *pend=p+n*step;
    for(;p!=pend;p+=step) s+=(*p)*(*p);
    return s;
  }

}

#include "vector/norm.h"

namespace mysimulator {

  template <typename T>
  T displacement2distanceSq(const Vector<T>& dsp) { return normSQ(dsp); }

}

#endif

