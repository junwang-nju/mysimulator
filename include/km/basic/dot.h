
#ifndef _Basic_Dot_H_
#define _Basic_Dot_H_

#include "type/combine.h"
#include "type/data.h"
#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T1, typename T2>
  typename CombineType<typename DataType<T1>::Type,
                       typename DataType<T2>::Type>::Type
  _Dot(const T1& a, const T2& b) {
    typedef typename IsNumeric<T1>::Type  DotCheck1;
    typedef typename IsNumeric<T2>::Type  DotCheck2;
    typedef typename CombineType<typename DataType<T1>::Type,
                                 typename DataType<T2>::Type>::Type DType;
    return static_cast<DType>(a)*static_cast<DType>(b);
  }

}

#endif

