
#ifndef _Intrinsic_Type_Duplicate_H_
#define _Intrinsic_Type_Duplicate_H_

#include "intrinsic-type/allocate.h"
#include "intrinsic-type/copy.h"

#define _DUP(type) void duplicate(type& a, const type& b) { copy(a,b); }

namespace mysimulator {

  _DUP(long double)
  _DUP(double)
  _DUP(float)
  _DUP(long long)
  _DUP(unsigned long long)
  _DUP(int)
  _DUP(unsigned int)
  _DUP(long)
  _DUP(unsigned long)
  _DUP(short)
  _DUP(unsigned short)
  _DUP(char)
  _DUP(unsigned char)
  _DUP(bool)

}

#undef _DUP

#endif

