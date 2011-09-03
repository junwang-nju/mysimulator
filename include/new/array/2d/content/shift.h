
#ifndef _Array_2D_Content_Shift_H_
#define _Array_2D_Content_Shift_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/shift.h"

#define _SHIFT(type) \
  template <typename T>\
  void shift(Array2DContent<T>& A, const type& d, const Array2DContent<T>& B) {\
    shift(A.base,d,B.base);\
  }

namespace mysimulator {

  _SHIFT(long double)
  _SHIFT(double)
  _SHIFT(float)
  _SHIFT(long long)
  _SHIFT(unsigned long long)
  _SHIFT(int)
  _SHIFT(unsigned int)
  _SHIFT(long)
  _SHIFT(unsigned long)
  _SHIFT(short)
  _SHIFT(unsigned short)
  _SHIFT(char)
  _SHIFT(unsigned char)

}

#undef _SHIFT

#endif

