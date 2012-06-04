
/**
 * @file type/is-char.h
 * @brief check if an object is \c char or not
 *
 * Some operations only work for char (such as string operation). This file
 * contains objects to check that the type of a certain object is char or not.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsChar_H_
#define _Type_IsChar_H_

namespace mysimulator {

  /**
   * @class IsCharFlag
   * @brief the internal object producing flag of char-type checking
   *
   * It contains a \c bool flag to indicate the check result. This could
   * be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsCharFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       *
       * \c true indicates that \c T is \c char -like, otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsCharFlag::Flag
   * the default flag for \c IsCharFlag which is set as \c false
   */
  template <typename T>
  const bool IsCharFlag<T>::Flag=false;

  /**
   * @brief the specialization for clas \c IsCharFlag for \c char
   *
   * This is the specialization for the class \c IsCharFlag. It has the
   * same interface as the default case.
   */
  template <>
  class IsCharFlag<char> {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       */
      static const bool Flag;
  };

  /** @var IsCharFlag<char>::Flag
   * this is the flag for specialized class with input type of \c char, which
   * is set as \c true.
   */
  template <>
  const bool IsCharFlag<char>::Flag=true;

  /**
   * @brief the specialization for clas \c IsCharFlag for \c unsigned \c char
   *
   * This is the specialization for the class \c IsCharFlag. It has the
   * same interface as the default case.
   */
  template <>
  class IsCharFlag<unsigned char> {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       */
      static const bool Flag;
  };
  /** @var IsCharFlag<unsigned char>::Flag 
   * the flag for specialized class with input type of \c unsigned \c char,
   * which is set as \c true
   */
  template <> const bool IsCharFlag<unsigned char>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsChar
   * @brief the object checking if a type is \c char or not
   *
   * This object is implemented with \c Check class. If the type is not \c char,
   * the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsChar {
    public:
      /** @typedef Type
       * @brief the definition of default type trait
       *
       * It is implemented with \c Check and \c IsCharFlag
       */
      typedef typename Check<IsCharFlag<T>::Flag>::Type   Type;
  };

}

#endif

