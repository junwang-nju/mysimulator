
#ifndef _Intrinsic_Type_Copy_H_
#define _Intrinsic_Type_Copy_H_

#define _COPY_(T1,T2) \
  void _Copy(T1& a,const T2& b) { a=static_cast<T1>(b); }

namespace mysimulator {

  _COPY_(long double, long double)
  _COPY_(long double, double)
  _COPY_(long double, float)
  _COPY_(long double, long long)
  _COPY_(long double, unsigned long long)
  _COPY_(long double, int)
  _COPY_(long double, unsigned int)
  _COPY_(long double, long)
  _COPY_(long double, unsigned long)
  _COPY_(long double, short)
  _COPY_(long double, unsigned short)
  _COPY_(long double, char)
  _COPY_(long double, unsigned char)

  _COPY_(double, double)
  _COPY_(double, float)
  _COPY_(double, long long)
  _COPY_(double, unsigned long long)
  _COPY_(double, int)
  _COPY_(double, unsigned int)
  _COPY_(double, long)
  _COPY_(double, unsigned long)
  _COPY_(double, short)
  _COPY_(double, unsigned short)
  _COPY_(double, char)
  _COPY_(double, unsigned char)

  _COPY_(float, float)
  _COPY_(float, long long)
  _COPY_(float, unsigned long long)
  _COPY_(float, int)
  _COPY_(float, unsigned int)
  _COPY_(float, long)
  _COPY_(float, unsigned long)
  _COPY_(float, short)
  _COPY_(float, unsigned short)
  _COPY_(float, char)
  _COPY_(float, unsigned char)

}

#undef _COPY_

#endif

