
#ifndef _Array_1D_Norm_H_
#define _Array_1D_Norm_H_

#include "array/1d/dot.h"
#include <cmath>

namespace mysimulator {

  template <typename T>
  T normSQ(const Array1D<T>& v) { return dot(v,v); }

  long double norm(const Array1D<long double>& v) { return sqrtl(normSQ(v)); }

  template <typename T>
  T _norm(const Array1D<T>& v) {
    assert(IsValid(v));
    return BLAS<T>::Norm(
        reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
        const_cast<T*>(v.start),const_cast<long*>(&lOne));
  }

  double norm(const Array1D<double>& v) { return _norm(v); }

  float norm(const Array1D<float>& v) { return _norm(v); }

}

#endif

