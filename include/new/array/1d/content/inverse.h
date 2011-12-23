
#ifndef _Array_1D_Content_Inverse_H_
#define _Array_1D_Content_Inverse_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/inverse.h"

namespace mysimulator {

  template <typename T>
  void inverse(Array1DContent<T>& A, const int& b, const unsigned int& d,
               const unsigned int& n) {
    assert(IsValid(A,b,d,n));
    T* p=A.head+b;
    T* pend=p+d*n;
    for(;p!=pend;)  { inverse(*p); p+=d; }
  }

  template <typename T>
  void inverse(Array1DContent<T>& A, const int& b, const unsigned int& n) {
    assert(IsValid(A,b,n));
    T* p=A.head+b;
    T* pend=p+n;
    for(;p!=pend;)  { inverse(*p); ++p; }
  }

  template <typename T>
  void inverse(Array1DContent<T>& A, const unsigned int& n) {
    assert(IsValid(A,n));
    T* p=A.start;
    T* pend=p+n;
    for(;p!=pend;)  { inverse(*p); ++p; }
  }

  template <typename T>
  void inverse(Array1DContent<T>& A) { inverse(A,A.size); }

}

#endif

