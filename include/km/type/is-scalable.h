
/** @file type/is-scalable.h
 * @brief check if the types are compatible with scale operation
 *
 * scale operation is a kind of numeric operation. this operation can
 * only some combinations of type. a check is needed to test the validity
 * of scale operation for the input types. This file implements the related
 * objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsScalable_H_
#define _Type_IsScalable_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsScalableFlag
   * @brief the class to produce flag indicating if 2-element scale operation can work for input types
   *
   * This class produces a flag indicating if the 2-element scale operation
   * can work for the input types. This is the basic component to evaluate
   * the validity of type for scale operation.
   *
   * @tparam T1 the type of data to be scaled
   * @tparam T2 the type of data as the scale factor
   */
  template <typename T1, typename T2>
  class IsScalableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if scale is valid
       *
       * When two types are all numbers and the range of the type \c T1
       * covers the range of the type \c T2, the flag is set as \c true.
       */
      static const bool Flag;
  };

  /** @var IsScalableFlag::Flag
   *
   * The default flag is implemented with \c IsNumericFlag and
   * \c IsIncludedFlag. This requires that two types are both numbers
   * and that the range of \c T1 is larger than that of \c T2.
   */
  template <typename T1, typename T2>
  const bool IsScalableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsScalable
   * @brief the class checking if the input types are compatible with scale operation
   *
   * The class is implemented with \c Check. When two types are compatible
   * with scale operation, the trait type would be defined. Otherwise,
   * the trait type would not be defined, which would throw an error
   * during compilation.
   *
   * @tparam T1 the type of data to be scaled
   * @tparam T2 the type of data as the scale factor
   */
  template <typename T1, typename T2>
  class IsScalable {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsScalableFlag.
       */
      typedef typename Check<IsScalableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

