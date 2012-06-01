
#ifndef _Array_Numeric_Base_Dot_H_
#define _Array_Numeric_Base_Dot_H_

#include "array/numeric/base/interface.h"

namespace mysimulator {

  template <typename T>
  typename DataType<ArrayNumeric<T> >::Type
  _Dot(const ArrayNumeric<T>& A, const ArrayNumeric<T>& B) {
    typedef typename IsNumeric<ArrayNumeric<T> >::Type  DotCheck;
    assert(A.IsValid());
    T *p=A.Head(), *pEnd=p+A.Size();
    typename DataType<ArrayNumeric<T> >::Type sum=0;
    for(;p!=pEnd;)  sum+=_Dot(
  }

}

#endif

