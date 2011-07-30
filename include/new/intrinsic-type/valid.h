
#ifndef _Intrinsic_Type_Valid_H_
#define _Intrinsic_Type_Valid_H_

#define _VALID(type) bool IsValid(const type&) { return true; }

namespace mysimulator {

  _VALID(long double)
  _VALID(double)
  _VALID(float)
  _VALID(long long)
  _VALID(unsigned long long)
  _VALID(int)
  _VALID(unsigned int)
  _VALID(long)
  _VALID(unsigned long)
  _VALID(short)
  _VALID(unsigned short)
  _VALID(char)
  _VALID(unsigned char)
  _VALID(bool)

}

#undef _VALID

#include <cstdlib>

namespace mysimulator {

  bool IsValid(const void* const& ptr) { return ptr!=NULL; }

  template <typename T>
  bool IsValid(const T* const& ptr) { return ptr!=NULL; }

}

#endif

