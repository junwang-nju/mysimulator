
/**
 * @file type/is-blas-size.h
 * @brief check if the size of object is BLAS compatible
 *
 * BLAS module can only work for the data structure with certain size.
 * This file contains the objects to carry out the related size check.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsBlasSize_H_
#define _Type_IsBlasSize_H_

namespace mysimulator {

  /**
   * @class IsBlasSizeFlag
   * @brief the internal object producing flag of BLAS-related size check
   *
   * It contains a bool flag to indicate the check result. This could be
   * incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsBlasSizeFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating the check result
       *
       * true indicates that size of T is compatible with BLAS modules.
       */
      static const bool Flag;
  };

  /** @var IsBlasSizeFlag::Flag
   * It is implemented as the size comparison with BLAS-compatible types
   * (including double and float)
   */
  template <typename T>
  const bool IsBlasSizeFlag<T>::Flag=
    (sizeof(double)==sizeof(T))||(sizeof(float)==sizeof(T));

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsBlasSize
   * @brief the object checking if the type size is BLAS compatible
   *
   * This object is implemented with Check class. If the size of type is not
   * compatible, the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsBlasSize {
    public:
      /** @typedef Type
       * @brief the definition of default type trait
       */
      typedef typename Check<IsBlasSizeFlag<T>::Flag>::Type   Type;
  };

}

#endif

