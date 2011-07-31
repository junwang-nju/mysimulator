
#ifndef _Array_2D_Content_Fill_H_
#define _Array_2D_Content_Fill_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/fill.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d) {
    assert(IsValid(A));
    fill(A.base,d);
  }

  template <typename T1, typename T2>
  void fill(Array2DContent<T1>& A, const T2& d, const int& lb,
            const unsigned int& ld, const unsigned int& nl, const int& rb,
            const unsigned int& rd, const unsigned int& nr) {
    assert(IsValid(A,lb,ld,nl,rb,rd,nr));
    Array1DContent<T1>* p=A.infra.head+lb;
    Array1DContent<T1>* e=p+ld*nl;
    for(;p!=e;p+=ld)  fill(*p,rb,rd,nr);
  }

}

#endif

