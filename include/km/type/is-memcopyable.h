
/**
 * @file type/is-memcopyable.h
 * @brief check if an object can be copied to another with \c memcpy
 *
 * \c memcpy is the classical procedure to copy memory block. however,
 * this operation cannot work for all cases of copy operations. A check
 * is necessary to ensure if \c memcpy can apply to the input type. This
 * file implements the related objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsMemCopyable_H_
#define _Type_IsMemCopyable_H_

#include "type/is-intrinsic.h"

namespace mysimulator {

  /** @class IsMemCopyableFlag
   * @brief the class to produce flag indicating if \c memcpy is appliable
   *
   * This class produces a flag indicating if the \c memcpy operation can
   * be applied to this type of data. This is the basic component to evaluate
   * the applicability of \c memcpy operation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsMemCopyableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if \c memcpy is valid
       *
       * When the data is of intrinsic type, it is possible to implement
       * the block copy with \c memcpy. When the input data is of intrinsic
       * type, the flag is set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };

  /** @var IsMemCopyableFlag::Flag
   *
   * The default flag is implemented with \c IsIntrinsicFlag
   */
  template <typename T>
  const bool IsMemCopyableFlag<T>::Flag=IsIntrinsicFlag<T>::Flag;

  /**
   * @brief the specialization of \c IsMemCopyableFlag for pointer
   *
   * This is a specialization of the class \c IsMemCopyableFlag for pointer
   * type which points to the \c T -type data. Though the pointer is regarded
   * as an intrinsic type, the copy of pointers demands be careful. Therefore,
   * the block copy of pointer is prohibited generally.
   *
   * @tparam T the type of data which is pointed by the pointer
   */
  template <typename T>
  class IsMemCopyableFlag<T*> {
    public:
      /** @var Flag
       * @brief the static flag indicating if \c memcpy is valid
       *
       * this is the flag for the spacialization of class \c IsMemCopyableFlag
       * of pointer type.
       */
      static const bool Flag;
  };

  /** @var IsMemCopyableFlag<T*>::Flag
   *
   * Since the pointer type is prohibited to be copied with \c memcpy,
   * the flag is set as \c false.
   */
  template <typename T>
  const bool IsMemCopyableFlag<T*>::Flag=false;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsMemCopyable
   * @brief the class to check if the \c memcpy operation is applicable
   *
   * This class is implemented with \c Check. When the data of input type
   * could be copied with \c memcpy operation, a trait type would be defined.
   * Otherwise, the trait type would not be defined, which would throw an
   * error during compilation.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsMemCopyable {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsMemCopyableFlag
       */
      typedef typename Check<IsMemCopyableFlag<T>::Flag>::Type  Type;
  };

}

#endif

