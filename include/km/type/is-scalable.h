
/** @file type/is-scalable.h
 * @brief check if the types are compatible with scale operation
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsScalable_H_
#define _Type_IsScalable_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsScalableFlag
   */
  template <typename T1, typename T2>
  class IsScalableFlag {
    public:
      /** @var Flag
       */
      static const bool Flag;
  };

  /** @var IsScalableFlag::Flag
   */
  template <typename T1, typename T2>
  const bool IsScalableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsScalable
   */
  template <typename T1, typename T2>
  class IsScalable {
    public:
      /** @typedef Type
       */
      typedef typename Check<IsScalableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

