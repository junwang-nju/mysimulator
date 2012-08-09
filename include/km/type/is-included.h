
/** @file type/is-included.h
 * @brief the objects to check if range of one type can cover another
 *
 * In many operations, we need to compare two types and check which kind
 * of type has larger range. This information may help the type conversion.
 * This need requires the comparison of the types to determine if the
 * range of one type is larger than (thus could cover) the range of another
 * type. This file implements the related objects
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsIncluded_H_
#define _Type_IsIncluded_H_

namespace mysimulator {

  /** @class IsIncludedFlag
   * @brief the class to produce the flag indicating the type relation
   *
   * This class contains a flag based on the comparison of various
   * properties of two input types. This is the basic component to
   * evaluate the inclusion relationship of types.
   *
   * @tparam T1 the first type, which is assumed to have a larger range
   *            when \a Flag is \c true
   * @tparam T2 the second type, this is assumes to have a smaller range
   *            when \a Flag is \c true
   */
  template <typename T1, typename T2>
  class IsIncludedFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the inclusion relation
       *
       * When the type \c T1 has a larger range than that of the type
       * \c T2, the flag is set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };

}

#include "type/is-float-point.h"
#include "type/is-integer.h"
#include "type/is-unsigned.h"

namespace mysimulator {

  /** @var IsIncludedFlag::Flag
   *
   * In detail, the flag is calculated based on the following cases:
   *
   * @arg \c T1 and \c T2 are all floating-point, and \c T1 is not
   *      smaller rthan \ c T2
   * @arg \c T1 is floating-point, and \c T2 is an integer
   * @arg \c T1 and \c T2 are both integers, and \c T1 is not \c unsigned,
   *      and \c T1 is larger than \c T2
   * @arg \c T1 and \c T2 are neither \c unsigned integer, and their
   *      sizes equal to each other
   * @arg \c T1 and \c T2 are both \c unsigned integer, and \c T1
   *      is not smaller than \c T2.
   *
   * Other cases (including \c T1 or \c T2 is not a number) would
   * give out a \c false flag. Using these rules, the specializations
   * are avoided.
   */
  template <typename T1, typename T2>
  const bool IsIncludedFlag<T1,T2>::Flag=
    ( IsFloatPointFlag<T1>::Flag && IsFloatPointFlag<T2>::Flag 
                                 && (sizeof(T1)>=sizeof(T2)) ) ||
    ( IsFloatPointFlag<T1>::Flag && IsIntegerFlag<T2>::Flag ) ||
    ( IsIntegerFlag<T1>::Flag && (!IsUnsignedFlag<T1>::Flag)
                              && IsIntegerFlag<T2>::Flag
                              && (sizeof(T1)>sizeof(T2)) ) ||
    ( IsIntegerFlag<T1>::Flag && IsIntegerFlag<T2>::Flag && (sizeof(T1)==sizeof(T2))
                              && (!IsUnsignedFlag<T1>::Flag)
                              && (!IsUnsignedFlag<T2>::Flag) ) ||
    ( IsUnsignedFlag<T1>::Flag && IsUnsignedFlag<T2>::Flag
                               && (sizeof(T1)>=sizeof(T2)) );

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsIncluded
   * @brief the class to check if the type inclusion relation exists
   *
   * This is class is implemented with \c Check. When the first type \c T1
   * has a larger range than that of the second type \c T2, a trait type
   * would be defined. Otherwise, the trait is not defined, which would
   * throw an error to access the trait of this class during compilation.
   *
   * @tparam T1 the first type, which is assumed to have a larger range
   *            when the trait type is defined
   * @tparam T2 the second type, this is assumes to have a smaller range
   *            when the trait type is defined
   */
  template <typename T1,typename T2>
  class IsIncluded {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsIncludedFlag.
       */
      typedef typename Check<IsIncludedFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

