
#ifndef _Type_Check_IsNumeric_H_
#define _Type_Check_IsNumeric_H_

namespace mysimulator {

  template <typename T>
  class IsNumeric {};

}

#ifndef _NumDEF
#define _NumDEF(T) \
  template <> class IsNumeric<T> { public: typedef IsNumeric<T> Type; };
#else
#error "Duplicate _NumDEF"
#endif

namespace mysimulator {

  _NumDEF(long double)
  _NumDEF(double)
  _NumDEF(float)
  _NumDEF(long long)
  _NumDEF(unsigned long long)
  _NumDEF(int)
  _NumDEF(unsigned int)
  _NumDEF(long)
  _NumDEF(unsigned long)
  _NumDEF(short)
  _NumDEF(unsigned short)
  _NumDEF(char)
  _NumDEF(unsigned char)

}

#ifdef _NumDEF
#undef _NumDEF
#endif

#endif


