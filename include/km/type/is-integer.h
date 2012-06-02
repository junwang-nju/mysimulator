
/**
 * @file type/is-integer.h
 * @brief check if an object is integer or not
 *
 * Some operations only work for integer (such as bit operation). This file
 * contains objects to check that the type of a certain object is integer or
 * not.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsInteger_H_
#define _Type_IsInteger_H_

namespace mysimulator {

  /**
   * @class IsIntegerFlag
   * @brief the internal object producing flag of integer-type checking
   *
   * It contains a bool flag to indicate the checking result. This could
   * be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsIntegerFlag {
    public:
      /** @brief the static flag indicating the check result
       *
       * true indicates that T is integer-type, otherwise false
       */
      static const bool Flag;
  };

  /** @brief default flag for IsIntegerFlag with is set as false */
  template <typename T> const bool IsIntegerFlag<T>::Flag=false;

}

#ifndef _IntDEF_
/** @brief static flags for specialized IsIntegerFlag object
 *
 * The specialized case, the flag is set as true. The specialized cases
 * include long long, int, long, short, char and their unsigned couterparts.
 */
#define _IntDEF_(T) template <> const bool IsIntegerFlag<T>::Flag=true;
#else
#error "Duplicate _IntDEF_"
#endif

namespace mysimulator {

  _IntDEF_(long long)
  _IntDEF_(unsigned long long)
  _IntDEF_(int)
  _IntDEF_(unsigned int)
  _IntDEF_(long)
  _IntDEF_(unsigned long)
  _IntDEF_(short)
  _IntDEF_(unsigned short)
  _IntDEF_(char)
  _IntDEF_(unsigned char)

}

#ifdef _IntDEF_
#undef _IntDEF_
#endif

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsInteger
   * @brief the object checking if a type is integer or not
   *
   * This object is implemented with Check class. If the type is not char,
   * the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsInteger {
    public:
      /** @brief the definition of default type trait */
      typedef typename Check<IsIntegerFlag<T>::Flag>::Type  Type;
  };

}

#endif

