
/** @file type/is-float-point.h
 * @brief check if an object is floating-point
 *
 * Some operations only work for floating-point numbers (such as \c BLAS
 * operations). This file contains objects to check that the type of
 * a certain object is floating-point or not.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsFloatPoint_H_
#define _Type_IsFloatPoint_H_

namespace mysimulator {

  template <typename T>
  class IsFloatPointFlag {
    public:
      static const bool Flag;
  };

  template <typename T>
  const bool IsFloatPointFlag<T>::Flag=false;

  template <>
  class IsFloatPointFlag<long double> {
    public:
      static const bool Flag;
  };
  template <> const bool IsFloatPointFlag<long double>::Flag=true;

  template <>
  class IsFloatPointFlag<double> {
    public:
      static const bool Flag;
  };
  template <> const bool IsFloatPointFlag<double>::Flag=true;

  template <>
  class IsFloatPointFlag<float> {
    public:
      static const bool Flag;
  };
  template <> const bool IsFloatPointFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsFloatPoint {
    public:
      typedef typename Check<IsFloatPointFlag<T>::Flag>::Type   Type;
  };

}

#endif

