
#ifndef _Intrinsic_Type_Absolute_Value_H_
#define _Intrinsic_Type_Absolute_Value_H_

#include <cmath>
#include <cstdlib>

namespace mysimulator {

  long double absval(const long double& ld) { return fabsl(ld); }
  double absval(const double& d) { return fabs(d); }
  float absval(const float& f) { return fabsf(f); }
  long long absval(const long long& ll) { return llabs(ll); }
  unsigned long long absval(const unsigned long long& ull) { return ull; }
  int absval(const int& i) { return abs(i); }
  unsigned int absval(const unsigned int& u) { return u; }
  long absval(const long& l) { return labs(l); }
  unsigned long absval(const unsigned long& ul) { return ul; }
  short absval(const short& s) { return (s>0?s:-s); }
  unsigned short absval(const unsigned short& us) { return us; }
  char absval(const char& c) { return (c>0?c:-c); }
  unsigned char absval(const unsigned char& uc) { return uc; }

}

#endif

