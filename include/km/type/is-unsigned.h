
/**
 * @file is-unsigned.h
 * @brief The Class to check unsigned data type
 *
 * Some operations can only apply for the unsigned data. This class is used
 * to check if the data type is unsigned. It is implemented by enumerating
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
   * @brief the Object checking if the type is unsigned
   *
   * This class contains a static flag to indicate checking result, so that it
   * works for all types and can be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsUnsignedFlag {
    public:
      /** @brief the static flag indicating if T is unsigned or not */
      static const bool Flag;
  };

  /** @brief the default flag for IsUnsignedFlag is set as false */
  template <typename T> const bool IsUnsignedFlag<T>::Flag=false;

}

#ifndef _UnsignDEF_
/** @brief static flags for specialized IsUnsignedFlag object
 *
 * The specialized case, the flag is set as true. The specialized cases
 * include unsigned long long, unsigned int, unsigned long, unsigned short,
 * and unsigned char.
 */
#define _UnsignDEF_(T)  template <> const bool IsUnsignedFlag<T>::Flag=true;
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
   * @brief the Class to check if the type is unsigned
   *
   * Using the generic Check class and IsUnsignedFlag object to implement
   * checking operation. When the type is not unsigned, an error would
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

