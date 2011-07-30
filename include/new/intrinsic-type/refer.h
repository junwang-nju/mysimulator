
#ifndef _Intrinsic_Type_Refer_H_
#define _Intrinsic_Type_Refer_H_

#include "intrinsic-type/copy.h"

#define _REFER(type) void refer(type& a, const type& b) { copy(a,b); }

namespace mysimulator {

  _REFER(long double)
  _REFER(double)
  _REFER(float)
  _REFER(long long)
  _REFER(unsigned long long)
  _REFER(int)
  _REFER(unsigned int)
  _REFER(long)
  _REFER(unsigned long)
  _REFER(short)
  _REFER(unsigned short)
  _REFER(char)
  _REFER(unsigned char)
  _REFER(bool)

  template <typename T>
  void refer(T*& a, const T* const& b) { copy(a,b); }

}

#undef _REFER

#endif

