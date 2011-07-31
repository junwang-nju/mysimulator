
#ifndef _Array_1D_Content_Init_H_
#define _Array_1D_Content_Init_H_

#include "array/1d/content/interface.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T>
  void init(Array1DContent<T>& A, const T* const& ptr, const unsigned int& n) {
    assert(IsValid(ptr)&&(n>0));
    copy(A.size,n);
    copy(A.first,0);
    copy(A.last,static_cast<int>(A.size-1));
    copy(A.start,ptr);
    copy(A.head,A.start);
  }

  template <typename T>
  void init(Array1DContent<T>& A, const T* const& ptr, const int& fst,
            const int& lst) {
    assert(IsValid(ptr)&&(fst<lst));
    copy(A.size,static_cast<unsigned int>(lst-fst+1));
    copy(A.first,fst);
    copy(A.last,lst);
    copy(A.start,ptr);
    copy(A.head,A.start-fst);
  }

}

#endif

