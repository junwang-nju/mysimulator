
/**
 * @file is-unsigned.h
 * @brief The Class to check unsigned data type
 *
 * Some operations can only apply for the \c unsigned data. This class is used
 * to check if the data type is \c unsigned. It is implemented by enumerating
 * all possible types.
 *
 * @note Presently, this class works for intrinsic type only.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsUnsigned_H_
#define _Type_IsUnsigned_H_

namespace mysimulator {

  /**
   * @class IsUnsignedFlag
   * @brief the Object checking if the type is \c unsigned
   *
   * This class contains a static flag to indicate checking result, so that it
   * works for all types and can be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsUnsignedFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if \c T is \c unsigned or not
       *
       * \c true when \c T is \c unsigned object, otherwise \c false
       */
      static const bool Flag;
  };

  /** @var IsUnsignedFlag::Flag
   *
   * the default flag for \c IsUnsignedFlag is set as \c false
   */
  template <typename T> const bool IsUnsignedFlag<T>::Flag=false;

}

#ifndef _UnsignDEF_
/** @def _UnsignDEF_
 * @brief static flags for specialized \c IsUnsignedFlag object
 *
 * The specialized case, the flag is set as \c true. The specialized cases
 * include \c unsigned \c long \c long, \c unsigned \c int, \c unsigned \c long,
 * \c unsigned \c short, and \c unsigned \c char. The specialization of class
 * is defined to vaidate the document with doxygen.
 *
 * @param T the input type
 */
#define _UnsignDEF_(T)  \
  template <> class IsUnsignedFlag<T> { public: static const bool Flag; }; \
  const bool IsUnsignedFlag<T>::Flag=true;
#else
#error "Duplicate _UnsignDEF_"
#endif

namespace mysimulator {

  _UnsignDEF_(unsigned long long)
  _UnsignDEF_(unsigned int)
  _UnsignDEF_(unsigned long)
  _UnsignDEF_(unsigned short)
  _UnsignDEF_(unsigned char)

}

#ifdef _UnsignDEF_
#undef _UnsignDEF_
#endif

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsUnsigned
   * @brief the Class to check if the type is \c unsigned
   *
   * Using the generic \c Check class and \c IsUnsignedFlag object to implement
   * checking operation. When the type is not \c unsigned, an error would
   * occur during compiling.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsUnsigned {
    public:
      /** @brief definition of default type trait */
      typedef typename Check<IsUnsignedFlag<T>::Flag>::Type   Type;
  };

}

#endif

