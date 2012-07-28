
/**
 * @file basic/inverse.h
 * @brief calculate inverse for data of basic type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Inverse_H_
#define _Basic_Inverse_H_

#include "type/is-float-point.h"

namespace mysimulator {

  template <typename T>
  void _Inverse(T& d) {
    typedef typename IsFloatPoint<T>::Type  FloatPointCheck;
    assert(d!=0);
    d=1./d;
  }

}

#endif

