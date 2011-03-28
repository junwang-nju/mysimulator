
#ifndef _Vector_Norm_H_
#define _Vector_Norm_H_

#include "vector/dot.h"
#include <cmath>

namespace mysimulator {

  template <typename T>
  T normSQ(const Vector<T>& v) { return dot(v,v); }

  long double norm(const Vector<long double>& v) {
    return sqrtl(normSQ(v));
  }

  double norm(const Vector<double>& v) {
    assert(IsValid(v));
    return dnrm2_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                  const_cast<double*>(v()),const_cast<long*>(&lOne));
  }

  float norm(const Vector<float>& v) {
    assert(IsValid(v));
    return snrm2_(reinterpret_cast<long*>(const_cast<unsigned int*>(&(v.size))),
                  const_cast<float*>(v()),const_cast<long*>(&lOne));
  }

}

#endif

