
/**
 * @file type/is-blas.h
 * @brief check if the type is BLAS-operatable
 *
 * Only several data types can be operated with BLAS module. This file offers
 * the check of the validity of types.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsBlas_H_
#define _Type_IsBlas_H_

namespace mysimulator {

  /**
   * @class IsBlasableFlag
   * @brief the internal object producing flag of type checking related to BLAS operations
   *
   * It contains a bool flag to indicate the checking result. This could
   * be incorporated into other checking.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsBlasableFlag {
    public:
      /** @brief the static flag indicating the check result
       *
       * true indicates that T is BLAS operatable, otherwise false
       */
      static const bool Flag;
  };

  /** @brief the default flag for IsBlasableFlag which is set as false */
  template <typename T>
  const bool IsBlasableFlag<T>::Flag=false;

  /** @brief the flag for specialized class with double as input type */
  template <> const bool IsBlasableFlag<double>::Flag=true;
  /** @brief the flag for specialized class with float as input type */
  template <> const bool IsBlasableFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsBlasable
   * @brief the object checking if a type is BLAS operatable
   *
   * This object is implemented with Check class. If the type is not char,
   * the trait definition of Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsBlasable {
    public:
      /** @brief the definition of default type trait */
      typedef typename Check<IsBlasableFlag<T>::Flag>::Type   Type;
  };

}

#endif

