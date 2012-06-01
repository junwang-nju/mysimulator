
#ifndef _Basic_NormSquare_H_
#define _Basic_NormSquare_H_

#include "type/is-numeric.h"
#include "type/data.h"

namespace mysimulator {

  template <typename T>
  typename DataType<T>::Type _NormSQ(const T& v) {
    typedef typename IsNumeric<T>::Type NormSQCheck;
    return v*v;
  }

}

#endif

