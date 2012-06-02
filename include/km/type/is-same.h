
/**
 * @file type/is-same.h
 * @brief checking if two objects are of same type
 *
 * Some operations require that two objects are of same type (such as BLAS
 * operations). This file offers objects to carry out the related check.
 */

#ifndef _Type_IsSame_H_
#define _Type_IsSame_H_

namespace mysimulator {

  /**
   * @class IsTypeSameFlag
   * @brief the internal object producing flag of same-type checking
   *
   * It contains a static bool flag to indicate the checking result. This
   * could be incorporated into other checking.
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class IsTypeSameFlag {
    public:
      /** @brief the static flag indicating the checking result
       *
       * true indicates that T1 and T2 are the same, otherwise false
       */
      static const bool Flag;
  };

  /** @brief the default flag for IsTypeSameFlag which is set as false */
  template <typename T1, typename T2>
  const bool IsTypeSameFlag<T1,T2>::Flag=false;

  /**
   * @brief specialization of class IsTypeSameFlag for two same types
   *
   * This class is specialized when two types are the same. The result is
   * clearly different from default condition, so that the specialization
   * is necessary.
   *
   * @tparam T the input type
   */
  template <typename T>
  class IsTypeSameFlag<T,T> {
    public:
      /** @brief the static flag indicating checking result for specialized class */
      static const bool Flag;
  };

  /** @brief the flag for specialized class with two same input types */
  template <typename T>
  const bool IsTypeSameFlag<T,T>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @class IsTypeSame
   * @brief the object chaecking if two types are of same type
   *
   * This object is implemented with Check class. Is two types are not
   * same, the trait definition of Type would fail.
   *
   * @tparam T1,T2 the input types
   */
  template <typename T1, typename T2>
  class IsTypeSame {
    public:
      /** @brief the definition of default type trait */
      typedef typename Check<IsTypeSameFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

