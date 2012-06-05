
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

  /** @class IsFloatPointFlag
   * @brief the internal object producing flag of floating-point-type checking
   *
   * It contains a \c bool flag to indicate the check result. This could be
   * incorporated into other checking
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsFloatPointFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       *
       * \c true indicating that \c T is a floating-point type, otherwise
       * \c false
       */
      static const bool Flag;
  };

  /** @var IsFloatPointFlag::Flag
   *
   * The default flag for \c IsFloatPointFlag which is set as \c false
   */
  template <typename T>
  const bool IsFloatPointFlag<T>::Flag=false;

  /**
   * @brief the specialization for class \c IsFloatPointFlag for \c long \c double
   *
   * This is the specialization for the class \c IsFloatPointFlag. It has the
   * same interface as the default case.
   */
  template <>
  class IsFloatPointFlag<long double> {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       */
      static const bool Flag;
  };
  /** @var IsFloatPointFlag<long double>::Flag
   *
   * This is the flag for specialized class with input type of \c long
   * \c double, which is set as \c true.
   */
  const bool IsFloatPointFlag<long double>::Flag=true;

  /**
   * @brief the specialization for class \c IsFloatPointFlag for \c double
   *
   * This is the specialization for the class \c IsFloatPointFlag. It has
   * the same interface as the default case.
   */
  template <>
  class IsFloatPointFlag<double> {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       */
      static const bool Flag;
  };
  /** @var IsFloatPointFlag<double>::Flag
   *
   * This is the flag for specialized class with input type of \c double,
   * which is set as \c true.
   */
  const bool IsFloatPointFlag<double>::Flag=true;

  /**
   * @brief the specialization for class \c IsFloatPointFlag for \c float
   *
   * This is the specialization for the class \c IsFloatPointFlag. It has
   * the same interface as the default case.
   */
  template <>
  class IsFloatPointFlag<float> {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       */
      static const bool Flag;
  };
  /** @var IsFloatPointFlag<float>::Flag
   *
   * This is the flag for specialized class with input type of \c float,
   * which is set as \c true.
   */
  const bool IsFloatPointFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsFloatPoint
   * @brief the object checking if a type is floating-point object or not
   *
   * This object is implemented with \c Chech class. If the type is not
   * floating-point object, the trait definition of \c Type would fail,
   * and throw an error during compilation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsFloatPoint {
    public:
      /** @typedef Type
       * @brief the definition of default type trait
       *
       * It is implemented with \c Check and \c IsFloatPointFlag.
       */
      typedef typename Check<IsFloatPointFlag<T>::Flag>::Type   Type;
  };

}

#endif

