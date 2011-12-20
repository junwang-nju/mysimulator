
#ifndef _Array_2D_Refer_H_
#define _Array_2D_Refer_H_

#include "array/2d/interface.h"
#include "array/2d/content/refer.h"
#include "pointer/refer.h"

#define _REFER_BASIC(A,cA)  \
  assert(IsValid(cA));\
  release(A);\
  refer(A.data,cA.data);\
  refer(A.subdata,cA.subdata);\
  typedef typename Array2D<T>::ParentType::ParentType   Type;

namespace mysimulator {

  template <typename T>
  void refer(Array2D<T>& A, Array2D<T>& cA,
             const int& partb, const int& parte, const int& newb) {
    _REFER_BASIC(A,cA)
    refer(static_cast<Type&>(A),static_cast<Type&>(cA),partb,parte,newb);
  }

  template <typename T>
  void refer(Array2D<T>& A, Array2D<T>& cA,
             const int& partb, const int& parte) {
    _REFER_BASIC(A,cA)
    refer(static_cast<Type&>(A),static_cast<Type&>(cA),partb,parte);
  }

  template <typename T>
  void refer(Array2D<T>& A, Array2D<T>& cA) {
    _REFER_BASIC(A,cA)
    refer(static_cast<Type&>(A),static_cast<Type&>(cA));
  }

  template <typename T>
  void refer(Array2D<T>& A, Array2D<T>& cA, const unsigned int& n) {
    _REFER_BASIC(A,cA)
    refer(static_cast<Type&>(A),static_cast<Type&>(cA),n);
  }

}

#undef _REFER_BASIC

#endif

