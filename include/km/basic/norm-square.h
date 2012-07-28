
/**
 * @file basic/norm-square.h"
 * @brief calculate square for data of basic type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_NormSquare_H_
#define _Basic_NormSquare_H_

#include "type/is-numeric.h"

namespace mysimulator {

  template <typename T>
  T _NormSQ(const T& v) {
    typedef typename IsNumeric<T>::Type NormSQCheck;
    return v*v;
  }

}

#endif

