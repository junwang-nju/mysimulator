
#ifndef _Basic_AbsoluteValue_H_
#define _Basic_AbsoluteValue_H_

#include <cmath>
#include <cstdlib>

#ifndef _AbsValDEF_
#define _AbsValDEF_(T,Func)  T AbsVal(const T& d) { return Func(d); }
#else
#error "Duplicate _AbsValDEF_"
#endif

namespace mysimulator {

  _AbsValDEF_(long double,fabsl)
  _AbsValDEF_(double,fabs)
  _AbsValDEF_(float,fabsf)
  _AbsValDEF_(long long,llabs)
  _AbsValDEF_(int,abs)
  _AbsValDEF_(long,labs)

}

#ifdef _AbsValDEF_
#undef _AbsValDEF_
#endif

#ifndef _AbsValDEF_
#define _AbsValDEF_(T) T AbsVal(const T& d) { return d>0?d:-d; }
#else
#error "Duplicate _AbsValDEF_"
#endif

namespace mysimulator {

  _AbsValDEF_(short)
  _AbsValDEF_(char)

}

#ifdef _AbsValDEF_
#undef _AbsValDEF_
#endif

#ifndef _AbsValDEF_
#define _AbsValDEF_(T) T AbsVal(const T& d) { return d; }
#else
#error "Duplicate _AbsValDEF_"
#endif

namespace mysimulator {

  _AbsValDEF_(unsigned long long)
  _AbsValDEF_(unsigned int)
  _AbsValDEF_(unsigned long)
  _AbsValDEF_(unsigned short)
  _AbsValDEF_(unsigned char)

}

#ifdef _AbsValDEF_
#undef _AbsValDEF_
#endif

#endif

