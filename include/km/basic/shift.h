
#ifndef _Basic_Shift_H_
#define _Basic_Shift_H_

#include "type/is-shiftable.h"

namespace mysimulator {

  template <typename T, typename T1>
  void _Shift(T& a, const T1& b) {
    typedef typename IsShiftable<T,T1>::Type  ShiftCheck;
    a+=static_cast<T>(b);
  }

  template <typename T, typename T1>
  void _NegShift(T& a, const T1& b) {
    typedef typename IsNegShiftable<T,T1>::Type  NegShiftCheck;
    a-=static_cast<T&>(b);
  }

  template <typename T,typename T1,typename T2>
  void _Shift(T& a, const T1& b, const T2& c) {
    typedef typename IsShiftable3<T,T1,T2>::Type  ShiftCheck;
    a+=b*c;
  }

  template <typename T,typename T1,typename T2,typename T3>
  void _Shift(T& a, const T1& b, const T2& c, const T3& d) {
    typedef typename IsShiftable4<T,T1,T2,T3>::Type ShiftCheck;
    a+=b*c*d;
  }

}

#endif

