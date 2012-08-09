
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
       */
      static const bool Flag;
  };

  template <typename T>
  const bool IsIntrinsicFlag<T>::Flag=IsNumericFlag<T>::Flag;

  template <>
  class IsIntrinsicFlag<bool> {
    public:
      static const bool Flag;
  };

  const bool IsIntrinsicFlag<bool>::Flag=true;

  template <typename T>
  class IsIntrinsicFlag<T*> {
    public:
      static const bool Flag;
  };

  template <typename T>
  const bool IsIntrinsicFlag<T*>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T>
  class IsIntrinsic {
    public:
      typedef typename Check<IsIntrinsicFlag<T>::Flag>::Type  Type;
  };

}

#endif

