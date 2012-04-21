
#ifndef _Intrinsic_Type_Allocate_H_
#define _Intrinsic_Type_Allocate_H_

#ifndef _IMPRINT
#define _IMPRINT(type) void Imprint(type&,const type&) {}
#else
#error "Duplicate Definition of _IMPRINT"
#endif

namespace mysimulator {

  _IMPRINT(long double)
  _IMPRINT(double)
  _IMPRINT(float)
  _IMPRINT(long long)
  _IMPRINT(unsigned long long)
  _IMPRINT(int)
  _IMPRINT(unsigned int)
  _IMPRINT(long)
  _IMPRINT(unsigned long)
  _IMPRINT(short)
  _IMPRINT(unsigned short)
  _IMPRINT(char)
  _IMPRINT(unsigned char)
  _IMPRINT(bool)

}

#ifdef _IMPRINT
#undef _IMPRINT
#endif

#endif

