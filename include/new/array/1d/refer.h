
#ifndef _Array_1D_Refer_H_
#define _Array_1D_Refer_H_

#include "array/1d/interface.h"
#include "array/1d/content/refer.h"
#include "pointer/refer.h"

#define _REFER_BASIC(A,cA) \
  assert(IsValid(cA));\
  release(A);\
  refer(A.data,cA.data);\
  typedef typename Array1D<T>::ParentType::ParentType   Type;

namespace mysimulator {

  template <typename T>
  void refer(Array1D<T>& A, Array1D<T>& cA, const int& partb, const int& parte,
             const int& newb) {
    _REFER_BASIC(A,cA);
    refer(static_cast<Type&>(A),static_cast<const Type&>(cA),partb,parte,newb);
  }

  template <typename T>
  void refer(Array1D<T>& A, Array1D<T>& cA, const int& partb, const int& parte){
    _REFER_BASIC(A,cA);
    refer(static_cast<Type&>(A),static_cast<const Type&>(cA),partb,parte);
  }

  template <typename T>
  void refer(Array1D<T>& A, Array1D<T>& cA) {
    _REFER_BASIC(A,cA);
    refer(static_cast<Type&>(A),static_cast<const Type&>(cA));
  }

  template <typename T>
  void refer(Array1D<T>& A, Array1D<T>& cA, const unsigned int& n) {
    _REFER_BASIC(A,cA);
    refer(static_cast<Type&>(A),static_cast<const Type&>(cA),n);
  }

}

#endif
