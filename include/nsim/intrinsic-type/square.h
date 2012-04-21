
#ifndef _Intrinsic_Type_Square_H_
#define _Intrinsic_Type_Square_H_

#define _SQUARE(type) \
  type square(const type& d) { return d*d; }

namespace mysimulator {

  _SQUARE(long double)
  _SQUARE(double)
  _SQUARE(float)
  _SQUARE(long long)
  _SQUARE(unsigned long long)
  _SQUARE(long)
  _SQUARE(unsigned long)
  _SQUARE(int)
  _SQUARE(unsigned int)
  _SQUARE(short)
  _SQUARE(unsigned short)
  _SQUARE(char)
  _SQUARE(unsigned char)

}

#endif

