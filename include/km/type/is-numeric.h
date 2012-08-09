
/**
 * @file type/is-numeric.h
 * @brief check if an object is a number
 *
 * For some operations, only number can be used. A check is necessary if
 * an object is a number. This file implements the related object.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsNumeric_H_
#define _Type_IsNumeric_H_

#include "type/is-float-point.h"
#include "type/is-integer.h"

namespace mysimulator {

  /** @class IsNumericFlag
   * @brief the class to produce flag indicating if the type is a number
   *
   * This class produces a \c bool flag which indicates if the input type
   * is a number. This is a basic component to check the input type, and
   * could be used in other operations.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsNumericFlag {
    public:
      /** @var Flag
       * @brief the static flag if the \c T -type data is a number
       *
       * When \c T -type data is a number, the flag is set as \c true,
       * otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsNumericFlag::Flag
   *
   * The floating-point data and integer data are all numbers. The flag
   * is implemented with \c IsFloatPointFlag and \c IsIntegerFlag.
   */
  template <typename T> const bool IsNumericFlag<T>::Flag=
    IsFloatPointFlag<T>::Flag||IsIntegerFlag<T>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsNumeric
   * @brief the class to check if the input type is a number
   *
   * This class is implemented with \c Check. When the input type \c T is
   * a number, a trait type id defined. Otherwise, the trait type would be
   * not defined, which would throw an error during compilation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsNumeric {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsNumericFlag.
       */
      typedef typename Check<IsNumericFlag<T>::Flag>::Type   Type;
  };

}

#endif

