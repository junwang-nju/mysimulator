
/**
 * @file type/is-numeric-object.h
 * @brief the class to check if an object is related to numeric operation
 *
 * In simulations, the numeric operations could only be applied to some certain
 * objects. To avoid incorrect usage of numeric operations, we need a check
 * if an object is compatible to the numeric operations. This file implements
 * the related objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsNumericObject_H_
#define _Type_IsNumericObject_H_

#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsNumericObjectFlag
   * @brief the class to produce flag indicating if an object is numeric-related
   *
   * This class produces a \c bool flag which indicats that the input type is
   * compatible with numeric operation. This is the basic component to check
   * the input type, and could be used in other type operations.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsNumericObjectFlag {
    public:
      /** @var Flag
       * @brief the static flag checking if the input is numeric-related
       *
       * When the type \c T is compatible with numeric operations, the flag
       * is set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsNumericObjectFlag::Flag
   *
   * The default flag is implemented with \c IsNumericFlag. This enusures
   * that the input type \c T is a number.
   */
  template <typename T>
  const bool IsNumericObjectFlag<T>::Flag=IsNumericFlag<T>::Flag;

  template <typename T> class ArrayNumeric;
  /**
   * @brief the specialization of \c IsNumericObjectFlag for \c ArrayNumeric
   *
   * This is a specialization of the class \c IsNumericObjectFlag for
   * \c ArrayNumeric. The object \c ArrayNumeric with numeric object could
   * be operated with some numerical operations.  This requires that the
   * type of elements is numeric object (such as number or array of numbers)
   *
   * @tparam T the type of the elements of \c ArrayNumeric
   */
  template <typename T>
  class IsNumericObjectFlag<ArrayNumeric<T> > {
    public:
      /** @var Flag
       * @brief the static flag checking if the input is numeric-related
       *
       * This is the flag in the specializationof \c IsNumericObjectFlag for
       * the type \c ArrayNumeric\<T\>.
       */
      static const bool Flag;
  };

  /** @var IsNumericObjectFlag<ArrayNumeric<T> >::Flag
   *
   * Only when the elements of \c ArrayNumeric is numeric object, the flag is
   * set as \c true. Therefore, this flag is implemented by checking if the
   * element type \c T is a numeric object.
   */
  template <typename T>
  const bool IsNumericObjectFlag<ArrayNumeric<T> >::Flag=
    IsNumericObjectFlag<T>::Flag;

  template <typename T> class Array2DNumeric;
  /**
   * @brief the specialization of \c IsNumericObjectFlag for \c Array2DNumeric
   *
   * This is a specialization of the class \c IsNumericObjectFlag for
   * \c Array2DNumeric. The object \c Array2DNumeric with numeric object could
   * be operated with some numerical operations.  This requires that the
   * type of elements is numeric object (such as number or array of numbers)
   *
   * @tparam T the type of the elements of \c Array2DNumeric
   */
  template <typename T>
  class IsNumericObjectFlag<Array2DNumeric<T> > {
    public:
      /** @var Flag
       * @brief the static flag checking if the input is numeric-related
       *
       * This is the flag in the specializationof \c IsNumericObjectFlag for
       * the type \c Array2DNumeric\<T\>.
       */
      static const bool Flag;
  };

  /** @var IsNumericObjectFlag<Array2DNumeric<T> >::Flag
   *
   * Only when the elements of \c Array2DNumeric is numeric object, the flag is
   * set as \c true. Therefore, this flag is implemented by checking if the
   * element type \c T is a numeric object.
   */
  template <typename T>
  const bool IsNumericObjectFlag<Array2DNumeric<T> >::Flag=
    IsNumericObjectFlag<T>::Flag;

  union Unique64Bit;
  /**
   * @brief the specialization of \c IsNumericObjectFlag for \c Unique64Bit
   *
   * This is a specialization of the class \c IsNumericObjectFlag for
   * \c Unique64Bit. \c Unique64Bit is a collection of various numeric
   * objects. Therefore, this check is approved.
   */
  template <>
  class IsNumericObjectFlag<Unique64Bit> {
    public:
      /** @var Flag
       * @brief the static flag checking if the input is numeric-related
       *
       * This is the flag in the specializationof \c IsNumericObjectFlag for
       * the type \c Unique64Bit.
       */
      static const bool Flag;
  };
  /** @var IsNumericObjectFlag<Unique64Bit>::Flag
   *
   * Since \c Unique64Bit is an object containing various kinds of numeric
   * objects, this flag is set as \c true explicitly.
   */
  const bool IsNumericObjectFlag<Unique64Bit>::Flag=true;

  union Unique128Bit;
  /**
   * @brief the specialization of \c IsNumericObjectFlag for \c Unique128Bit
   *
   * This is a specialization of the class \c IsNumericObjectFlag for
   * \c Unique128Bit. \c Unique128Bit is a collection of various numeric
   * objects. Therefore, this check is approved.
   */
  template <>
  class IsNumericObjectFlag<Unique128Bit> {
    public:
      /** @var Flag
       * @brief the static flag checking if the input is numeric-related
       *
       * This is the flag in the specializationof \c IsNumericObjectFlag for
       * the type \c Unique128Bit.
       */
      static const bool Flag;
  };
  /** @var IsNumericObjectFlag<Unique128Bit>::Flag
   *
   * Since \c Unique128Bit is an object containing various kinds of numeric
   * objects, this flag is set as \c true explicitly.
   */
  const bool IsNumericObjectFlag<Unique128Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsNumericObject
   * @brief the class checking if the input type is numeric-related
   *
   * This class is implemented with \c Check. If the input type \c T
   * is compatible with numeric operations, the trait type would be
   * defined. Otherwise, no trait type are defined, which would throw
   * an error during compilation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsNumericObject {
    public:
      /** @typedef Type
       * @brief the definition of the default trait type
       *
       * This definition is implemented with \c Check and \c IsNumericObjectFlag.
       */
      typedef typename Check<IsNumericObjectFlag<T>::Flag>::Type Type;
  };

}

#endif

