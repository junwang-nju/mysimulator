
#ifndef _Array_2D_Content_Dot_H_
#define _Array_2D_Content_Dot_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/dot.h"
#include "intrinsic-type/reflection/dual.h"

#define _DotTYPE(T1,T2)  typename _Dual<T1,T2>::CombineType

namespace mysimulator {

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array2DContent<T2>& A2) {
    return dot(A1.base,A2.base);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array2DContent<T1>& A1, const Array1DContent<T2>& A2) {
    return dot(A1.base,A2);
  }

  template <typename T1, typename T2>
  _DotTYPE(T1,T2)
  dot(const Array1DContent<T1>& A1, const Array2DContent<T2>& A2) {
    return dot(A1,A2.base);
  }
  
}

#endif

