
#ifndef _Intrinsic_Type_Exchange_H_
#define _Intrinsic_Type_Exchange_H_

#define _EXG(type) void exchange(type& a, type& b) { type c; c=a; a=b; b=c; }

namespace mysimulator {

  _EXG(long double)
  _EXG(double)
  _EXG(float)
  _EXG(long long)
  _EXG(unsigned long long)
  _EXG(int)
  _EXG(unsigned int)
  _EXG(long)
  _EXG(unsigned long)
  _EXG(short)
  _EXG(unsigned short)
  _EXG(char)
  _EXG(unsigned char)
  _EXG(bool)
  _EXG(void*)
  template <typename T> _EXG(T*)

}

#undef _EXG

#endif

