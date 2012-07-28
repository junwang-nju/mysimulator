
/**
 * @file basic/sin.h
 * @brief calculate sine for data of basic type
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_Sine_H_
#define _Basic_Sine_H_

#include <cmath>

#ifndef _SIN
#define _SIN(RT,Func) RT _Sin(const RT& d) { return Func(d); }
#else
#error "Duplicate _SIN"
#endif

namespace mysimulator {

  _SIN(double,sin)
  _SIN(float,sinf)
  _SIN(long double,sinl)

}

#ifdef _SIN
#undef _SIN
#endif

#endif

