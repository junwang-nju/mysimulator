
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
   * It contains a \c bool flag to indicate the checking result. This could
   * be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsIntegerFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       *
       * \c true indicates that \c T is integer-type, otherwise \c false
       */
      static const bool Flag;
  };

  /** @var IsIntegerFlag::Flag
   *
   * default flag for \c IsIntegerFlag with is set as \c false
   */
  template <typename T> const bool IsIntegerFlag<T>::Flag=false;

}

#ifndef _IntDEF_
/** @def _IntDEF_
 * @brief static flags for specialized IsIntegerFlag object
 *
 * The specialized case, the flag is set as \c true. The specialized cases
 * include \c long \c long, \c int, \c long, \c short, \c char and
 * their \c unsigned couterparts.
 *
 * @param RT the input type for the macro
 */
#define _IntDEF_(RT) \
  template <> \
  class IsIntegerFlag<RT> { public: static const bool Flag; }; \
  const bool IsIntegerFlag<RT>::Flag=true;
#else
#error "Duplicate _IntDEF_"
#endif

namespace mysimulator {

  /** @var IsIntegerFlag<long long>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c long
   * \c long type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c long \c long
   *
   * This is a specialization of class IsIntegerFlag for \c long \c long
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(long long)
  /** @var IsIntegerFlag<unsigned long long>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c unsigned
   * \c long \c long type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c unsigned \c long \c long
   *
   * This is a specialization of class IsIntegerFlag for \c unsigned \c long
   * \c long type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(unsigned long long)
  /** @var IsIntegerFlag<int>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c int
   * type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c int
   *
   * This is a specialization of class IsIntegerFlag for \c int
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(int)
  /** @var IsIntegerFlag<unsigned int>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c unsigned
   * \c int type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c unsigned \c int
   *
   * This is a specialization of class IsIntegerFlag for \c unsigned \c int
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(unsigned int)
  /** @var IsIntegerFlag<long>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c long
   * type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c long
   *
   * This is a specialization of class IsIntegerFlag for \c long
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(long)
  /** @var IsIntegerFlag<unsigned long>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for
   * \c unsigned \c long type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c unsigned \c long
   *
   * This is a specialization of class IsIntegerFlag for \c unsigned \c long
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(unsigned long)
  /** @var IsIntegerFlag<short>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c short
   * type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c short
   *
   * This is a specialization of class IsIntegerFlag for \c short
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(short)
  /** @var IsIntegerFlag<unsigned short>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for
   * \c unsigned \c short type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c unsigned \c short
   *
   * This is a specialization of class IsIntegerFlag for \c unsigned \c short
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(unsigned short)
  /** @var IsIntegerFlag<char>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for \c char
   * type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c char
   *
   * This is a specialization of class IsIntegerFlag for \c char
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
  _IntDEF_(char)
  /** @var IsIntegerFlag<unsigned char>::Flag
   * @brief the static flag indicating the check result
   *
   * This takes the value \c true and is the specialization for
   * \c unsigned \c char type.
   */
  /**
   * @brief the specialization of \c IsIntegerFlag for \c unsigned \c char
   *
   * This is a specialization of class IsIntegerFlag for \c unsigned \c char
   * type. The definition of this specialization is used for the
   * implementation of documnets related to the specialized member.
   */
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
   * This object is implemented with Check class. If the type is not integer,
   * the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsInteger {
    public:
      /** @typedef Type
       * @brief the definition of default type trait
       *
       * It is implemented with \c Check and \c IsIntegerFlag.
       */
      typedef typename Check<IsIntegerFlag<T>::Flag>::Type  Type;
  };

}

#endif

