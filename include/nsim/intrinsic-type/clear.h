
#ifndef _Intrinsic_Type_Clear_H_
#define _Intrinsic_Type_Clear_H_

#ifndef _CLEAR
#define _CLEAR(Type) void Clear(Type& d) {}
#endif

namespace mysimulator {

  _CLEAR(long double)
  _CLEAR(double)
  _CLEAR(float)
  _CLEAR(long long)
  _CLEAR(unsigned long long)
  _CLEAR(int)
  _CLEAR(unsigned int)
  _CLEAR(long)
  _CLEAR(unsigned long)
  _CLEAR(short)
  _CLEAR(unsigned short)
  _CLEAR(char)
  _CLEAR(unsigned char)
  _CLEAR(bool)

  template <typename T>
  void Clear(T*& ptr) { ptr=NULL; }

}

#ifdef _CLEAR
#undef _CLEAR
#endif

#endif

