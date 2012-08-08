
/**
 * @file type/is-intrinsic.h
 * @brief check if a type is an intrinsic type
 *
 * Some operations only works for intrinsic types (such as the operations
 * in \a basic directory. This is because that the intrinsic type in c++ is
 * not same as an object. Some checks are necessary to check if the data
 * is of intrinsic type. This file implements the related objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsIntrinsic_H_
#define _Type_IsIntrinsic_H_

#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsIntrinsicFlag
   * @brief the class to produce flag indicating if a type is intrinsic
   *
   * This class could produce a flag based on the input type. This is
   * the basic component to determine if a type is an intrinsic type
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsIntrinsicFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if the type is intrinsic
       *
       * When the type \c T is an intrinsic type (including \c long \c double,
       * \c double, \c float, \c unsigned \c long \c long, \c long \c long,
       * \c unsigned \c int, \c int, \c unsigned \c long, \c long,
       * \c unsigned \c short, \c short, \c unsigned \c char, \c char),
       * the flag would be set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsIntrinsicFlag::Flag
   *
   * the default flag is assigned based on \c IsNumericFlag. This
   * ensures that the type of number is intrinsic.
   */
  template <typename T>
  const bool IsIntrinsicFlag<T>::Flag=IsNumericFlag<T>::Flag;

  /**
   * @brief the specialization of \c IsIntrinsicFlag for \c bool type
   *
   * This is a specialization of the class \c IsIntrinsicFlag. the concerned
   * type is \c bool. This type is introduced into c++ standard in C++0x.
   * Here the \c bool type is taken as an intrinsic type.
   */
  template <>
  class IsIntrinsicFlag<bool> {
    public:
      /** @var Flag
       * @brief the static flag indicating if the type is intrinsic
       *
       * This is the flag for the specialization for \c bool type.
       */
      static const bool Flag;
  };

  /** @var IsIntrinsicFlag<bool>::Flag
   *
   * Since \c bool is regarded as an intrinsic type, the flag is set
   * as \c true.
   */
  const bool IsIntrinsicFlag<bool>::Flag=true;

  /**
   * @brief the specialization of \c IsIntrinsicFlag for pointer type
   *
   * This is a specialization of the class \c IsIntrinsicFlag. the concerned
   * type is pointer of \c T -type data. The pointer is an intrinsic type.
   *
   * @tparam the type of data which is pointed by pointer.
   */
  template <typename T>
  class IsIntrinsicFlag<T*> {
    public:
      /** @var Flag
       * @brief the static flag indicating if the type is intrinsic
       *
       * This is the flag for the specialization for pointer pointing to
       * \c T -type data
       */
      static const bool Flag;
  };

  /** @var IsIntrinsicFlag<T*>::Flag
   *
   * Since the pointer type is an intrinsic type, the flag is set as
   * \c true.
   */
  template <typename T>
  const bool IsIntrinsicFlag<T*>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsIntrinsic
   * @brief the class to check if the type is intrinsic
   *
   * This class is implemented with \c Check. When the input type \c T is
   * intrinsic, a trait type would be defined. Otherwise, there would be
   * no trait type defined, which would throw an error during compilation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsIntrinsic {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsIntrinsicFlag.
       */
      typedef typename Check<IsIntrinsicFlag<T>::Flag>::Type  Type;
  };

}

#endif

