
/**
 * @file basic/abs-value.h
 * @brief calculate absolute value for data of basic type
 *
 * this module calculates the absolute value of data of intrinsic type.
 * this is a basic mathematical operation for various kinds of sign numbers.
 * These functions unify the interface for vatious types of numbers.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Basic_AbsoluteValue_H_
#define _Basic_AbsoluteValue_H_

#include <cmath>
#include <cstdlib>

#ifndef _AbsValDEF_
/** @brief calculate absolute value with pre-defined method
 *
 * For some data types (including float-pointer data, and long long, long,
 * and int), there are some pre-defined methods. This macro implements
 * a unique interface to calculate absolute value of the input data with
 * these pre-defined data.
 *
 * @param T the type of input data
 * @param Func the function to carry out the calculation
 */
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
/** @brief calculate absolute value with comparison
 *
 * For some data types (such as char and short), there are no pre-defined
 * methods to calculate absolute values. The calculation is implemented
 * by comparing the value with zero.
 *
 * @param T the type of input data
 */
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
/**
 * @brief calculate absolute value for unsigned value
 *
 * the absolute value of unsigned number is itself.
 *
 * @param T the type of input data
 */
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

