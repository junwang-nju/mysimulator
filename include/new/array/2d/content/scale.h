
#ifndef _Array_2D_Content_Scale_H_
#define _Array_2D_Content_Scale_H_

#include "array/2d/content/interface.h"
#include "array/1d/content/scale.h"

#define _SCALE(type) \
  template <typename T>\
  void scale(Array2DContent<T>& A, const type& d) { scale(A.base,d); }

namespace mysimulator {

  _SCALE(long double)
  _SCALE(double)
  _SCALE(float)
  _SCALE(long long)
  _SCALE(unsigned long long)
  _SCALE(int)
  _SCALE(unsigned int)
  _SCALE(long)
  _SCALE(unsigned long)
  _SCALE(short)
  _SCALE(unsigned short)
  _SCALE(char)
  _SCALE(unsigned char)

}

#undef _SCALE

#endif

