
#ifndef _Intrinsic_Type_AbsoluteValue_H_
#define _Intrinsic_Type_AbsoluteValue_H_

#include <cmath>
#include <cstdlib>

#define ABSVAL(type)  type absval(const type& d)

namespace mysimulator {

  ABSVAL(long double) { return fabsl(d); }
  ABSVAL(double) { return fabs(d); }
  ABSVAL(float) { return fabsf(d); }
  ABSVAL(long long) { return llabs(d); }
  ABSVAL(unsigned long long) { return d; }
  ABSVAL(int) { return abs(d); }
  ABSVAL(unsigned int) { return d; }
  ABSVAL(long) { return labs(d); }
  ABSVAL(unsigned long) { return d; }
  ABSVAL(short) { return (d>0?d:-d); }
  ABSVAL(unsigned short) { return d; }
  ABSVAL(char) { return (d>0?d:-d); }
  ABSVAL(unsigned char) { return d; }

}

#undef ABSVAL

#endif

