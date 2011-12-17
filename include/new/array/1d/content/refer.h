
#ifndef _Array_1D_Content_Refer_H_
#define _Array_1D_Content_Refer_H_

#include "array/1d/content/init.h"
#include "intrinsic-type/refer.h"

namespace mysimulator {

  template <typename T>
  void refer(Array1DContent<T>& A, const Array1DContent<T>& cA,
             const int& partb, const int& parte, const int& newb) {
    assert(IsValid(cA));
    assert(partb<=parte);
    assert((partb>=cA.first)&&(parte<=cA.last));
    release(A);
    init(A,cA.head+partb,newb,newb+parte-partb);
  }

  template <typename T>
  void refer(Array1DContent<T>& A, const Array1DContent<T>& cA,
             const int& partb, const int& parte) {
    refer(A,cA,partb,parte,partb);
  }

  template <typename T>
  void refer(Array1DContent<T>& A, const Array1DContent<T>& cA) {
    refer(A,cA,cA.first,cA.last);
  }

  template <typename T>
  void refer(Array1DContent<T>& A, const Array1DContent<T>& cA,
             const unsigned int& n) {
    assert(cA.size>=n);
    refer(A,cA,cA.first,cA.first+n-1);
  }

}

#endif

