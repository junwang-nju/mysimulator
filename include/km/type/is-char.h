
/**
 * @file type/is-char.h
 * @brief check if an object is char or not
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
   * It contains a bool flag to indicate the check result. This could
   * be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsCharFlag {
    public:
      /** @brief the static flag indicating the check result
       *
       * true indicates that T is char-like, otherwise false.
       */
      static const bool Flag;
  };

  /** @brief the default flag for IsCharFlag which is set as false */
  template <typename T>
  const bool IsCharFlag<T>::Flag=false;

  /** @brief the flag for specialized class with input type of char */
  template <> const bool IsCharFlag<char>::Flag=true;
  /** @brief the flag for specialized class with input type of unsigned char */
  template <> const bool IsCharFlag<unsigned char>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsChar
   * @brief the object checking if a type is char or not
   *
   * This object is implemented with Check class. If the type is not char,
   * the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsChar {
    public:
      /** @brief the definition of default type trait */
      typedef typename Check<IsCharFlag<T>::Flag>::Type   Type;
  };

}

#endif

