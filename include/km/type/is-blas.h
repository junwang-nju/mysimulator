
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
      /** @var Flag
       * @brief the static flag indicating the check result
       *
       * \c true indicates that \c T is BLAS operatable, otherwise \c false
       */
      static const bool Flag;
  };

  /** @var IsBlasableFlag::Flag
   * the default flag for IsBlasableFlag which is set as \c false
   */
  template <typename T>
  const bool IsBlasableFlag<T>::Flag=false;

  /**
   * @brief the specialization of class \c IsBlasableFlag for \c double
   *
   * This is a specialization for \c double type. It has the same interface
   * as the default class.
   */
  template <>
  class IsBlasableFlag<double> {
    public:
      /** @var Flag
       * @brief the static flag indicating check flag
       */
      static const bool Flag;
  };

  /** @var IsBlasableFlag<double>::Flag
   * the flag for specialized class \c IsBlasableFlag\<double\> with \c double
   * as input type
   */ 
  template <>
  const bool IsBlasableFlag<double>::Flag=true;

  /**
   * @brief the specialization of class \c IsBlasableFlag for \c flaot
   *
   * This is a specialization for \c float type. It has the same interface
   * as the default class.
   */
  template <>
  class IsBlasableFlag<float> {
    public:
      static const bool Flag;
  };

  /** @var IsBlasableFlag<float>::Flag
   * the flag for specialized class \c IsBlasableFlag\<float\> with \c float
   * as input type
   */
  template <>
  const bool IsBlasableFlag<float>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsBlasable
   * @brief the object checking if a type is \c BLAS operatable
   *
   * This object is implemented with Check class. If the type is not \c char,
   * the trait definition of \c Type would fail.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsBlasable {
    public:
      /** @typedef Type
       * @brief the definition of default type trait
       *
       * It is implemented with \c Check and \c IsBlasableFlag.
       */
      typedef typename Check<IsBlasableFlag<T>::Flag>::Type   Type;
  };

}

#endif

