
#ifndef _Intrinsic_Type_Shift_H_
#define _Intrinsic_Type_Shift_H_

#include "intrinsic-type/copy.h"
#include "intrinsic-type/scale.h"

#define _SHIFT1(type) \
  template <typename T>\
  void shift(type& a, const T& b) { type a1; copy(a1,b); a+=a1; }

#define _SHIFT2(type) \
  template <typename T1, typename T2>\
  void shift(type& a, const T1& b, const T2& c) {\
    type a1,a2; copy(a1,b); copy(a2,c); a+=a1*a2;\
  }

#define _SHIFT3(type) \
  template <typename T1, typename T2, typename T3>\
  void shift(type& a, const T1& b, const T2& c, const T3& d) {\
    type a1,a2,a3; copy(a1,b); copy(a2,c); copy(a3,d); a+=a1*a2*a3;\
  }

#define _SHIFT(type) \
  _SHIFT1(type)\
  _SHIFT2(type)\
  _SHIFT3(type)

#define _SSHIFT1(type) \
  template <typename T1, typename T2>\
  void scaleshift(type& a, const T1& b, const T2& c) {\
    scale(a,b); shift(a,c);\
  }

#define _SSHIFT2(type) \
  template <typename T1, typename T2, typename T3>\
  void scaleshift(type& a, const T1& b, const T2& c, const T3& d) {\
    scale(a,b); shift(a,c,d);\
  }

#define _SSHIFT3(type) \
  template <typename T1, typename T2, typename T3, typename T4>\
  void scaleshift(type& a, const T1& b, const T2& c, const T3& d, const T4& e){\
    scale(a,b); shift(a,c,d,e);\
  }

#define _SSHIFT(type) \
  _SSHIFT1(type)\
  _SSHIFT2(type)\
  _SSHIFT3(type)

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

  _SSHIFT(long double)
  _SSHIFT(double)
  _SSHIFT(float)
  _SSHIFT(long long)
  _SSHIFT(unsigned long long)
  _SSHIFT(int)
  _SSHIFT(unsigned int)
  _SSHIFT(long)
  _SSHIFT(unsigned long)
  _SSHIFT(short)
  _SSHIFT(unsigned short)
  _SSHIFT(char)
  _SSHIFT(unsigned char)

}

#undef _SSHIFT
#undef _SSHIFT3
#undef _SSHIFT2
#undef _SSHIFT1
#undef _SHIFT
#undef _SHIFT3
#undef _SHIFT2
#undef _SHIFT1

#endif

