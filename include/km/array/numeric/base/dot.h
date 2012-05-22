
#ifndef _Array_Numeric_Base_Dot_H_
#define _Array_Numeric_Base_Dot_H_

#include "array/numeric/base/interface.h"
#include "basic/dot.h"

namespace mysimulator {

  template <typename T1, typename T2>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  _Dot(const ArrayNumeric<T1>& A, const ArrayNumeric<T2>& B) {
    typedef typename IsNumeric<ArrayNumeric<T1> >::Type  DotCheck1;
    typedef typename IsNumeric<ArrayNumeric<T2> >::Type  DotCheck2;
    assert(A.IsValid());
    typename CombineType<typename DataType<T1>::Type,
                         typename DataType<T2>::Type>::Type sum=0;
    T1 *p=A.Head(), *pEnd=p+A.Size();
    T2 *q=B.Head();
    for(;p!=pEnd;)  sum+=_Dot(*(p++),*(q++));
    return sum;
  }

}

#endif

