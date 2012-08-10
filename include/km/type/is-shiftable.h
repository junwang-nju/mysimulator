
/** @file type/is-shiftable.h
 * @brief check if the types are compatible with shift operations
 *
 * shift operations are a kind of numeric operations. these operations can only
 * work for some combinations of types. cheks are needed to test the validity
 * of shift operation for the input types. This file implements the related
 * objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_Is_Shiftable_H_
#define _Type_Is_Shiftable_H_

#include "type/is-included.h"

namespace mysimulator {

  /** @class IsShiftableFlag
   * @brief the class to produce flag indicate type validity of 2-element shift operation
   *
   * This class produces a flag indicating if the 2-element shift operation
   * can work for the input types. This is the basic component to evaluate
   * the validity of types for 2-element shift operation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2 the type of data as the displacement to shift.
   */
  template <typename T1, typename T2>
  class IsShiftableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if 2-element shift is valid
       *
       * When the range of the type \c T1 is larger than that of the type
       * \c T2, the second element could be converted to the type \c T1.
       * Thus, the 2-element shift operation is valid. The corresponding
       * flag is set as \c true.
       */
      static const bool Flag;
  };

  /** @var IsShiftableFlag::Flag
   *
   * The default flag is implemented with \c IsIncludedFlag. When the flag
   * is \c true, the 2-element shift operation is valid.
   */
  template <typename T1, typename T2>
  const bool IsShiftableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag;

  /** @class IsNegShiftableFlag
   * @brief the class to produce flag indicate type validity of 2-element negative shift operation
   *
   * This class produces a flag indicating if the 2-element negative shift
   * operation can work for the input types. This is the basic component to
   * evaluate the validity of types for 2-element negative shift operation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2 the type of data as the displacement to shift.
   */
  template <typename T1, typename T2>
  class IsNegShiftableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if 2-element negative shift is valid
       *
       * The substraction operation requires the data cannot be \c unsigned.
       * Therefore, for this flag, an addition condition to check if the
       * type \c T1 is not \c unsigned is included, besides the requirement
       * for 2-element shift operation.
       */
      static const bool Flag;
  };

}

#include "type/is-unsigned.h"
#include "type/data.h"

namespace mysimulator {

  /** @var IsNegShiftableFlag::Flag
   *
   * The default flag is impelemented with \c IsShiftableFlag and
   * \c IsUnsignedFlag. When the flag is \c true, the 2-element negative
   * shift operation is valid.
   */
  template <typename T1, typename T2>
  const bool IsNegShiftableFlag<T1,T2>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&(!IsUnsignedFlag<T1>::Flag);

  /** @class IsShiftable3Flag
   * @brief the class to produce flag indicate type validity of 3-element shift operation
   *
   * This class produces a flag indicating if the 3-element shift
   * operation can work for the input types. This is the basic component to
   * evaluate the validity of types for 3-element shift operation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2,T3 the types of data to calculate the displacement to shift.
   */
  template <typename T1,typename T2,typename T3>
  class IsShiftable3Flag {
    public:
      /** @var Flag
       * @brief the static flag indicating if 3-element shift is valid
       *
       * The requirement for 3-element shift is reduced as two requirements
       * for 2-element shift, namely, the combination of (\c T1, \c T2 ) and
       * (\c T1, \c T3) are both satisfy the requirement for 2-element shift.
       */
      static const bool Flag;
  };

  /** @var IsShiftable3Flag::Flag
   *
   * The default flag is implemented with \c IsShiftableFlag. When
   * the flag is \c true, the 3-element shift operation is valid.
   */
  template <typename T1,typename T2,typename T3>
  const bool IsShiftable3Flag<T1,T2,T3>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&IsShiftableFlag<T1,T3>::Flag;

  /** @class IsShiftable4Flag
   * @brief the class to produce flag indicate type validity of 4-element shift operation
   *
   * This class produces a flag indicating if the 4-element shift
   * operation can work for the input types. This is the basic component to
   * evaluate the validity of types for 4-element shift operation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2,T3,T4 the types of data to calculate the displacement to shift.
   */
  template <typename T1,typename T2,typename T3,typename T4>
  class IsShiftable4Flag {
    public:
      /** @var Flag
       * @brief the static flag indicating if 4-element shift is valid
       *
       * The requirement for 4-element shift is reduced as two requirements
       * for 2-element shift, namely, the combination of (\c T1, \c T2 ) and
       * (\c T1, \c T3) and (\c T1, \c T4 ) are both satisfy the requirement
       * for 2-element shift.
       */
      static const bool Flag;
  };

  /** @var IsShiftable3Flag::Flag
   *
   * The default flag is implemented with \c IsShiftableFlag. When
   * the flag is \c true, the 4-element shift operation is valid.
   */
  template <typename T1,typename T2,typename T3,typename T4>
  const bool IsShiftable4Flag<T1,T2,T3,T4>::Flag=
    IsShiftableFlag<T1,T2>::Flag&&IsShiftableFlag<T1,T3>::Flag&&
    IsShiftableFlag<T1,T4>::Flag;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsShiftable
   * @brief the class checking the validity of 2-element shift operation
   *
   * This class is implemented with \c Check. When the input types
   * match the requirements of 2-element shift operation, a trait type
   * is defined. Otherwise, the trait type is not defined, which would
   * throw an error during compilation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2 the type of data as the displacement to shift.
   */
  template <typename T1, typename T2>
  class IsShiftable {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsShiftableFlag
       */
      typedef typename Check<IsShiftableFlag<T1,T2>::Flag>::Type  Type;
  };

  /** @class IsNegShiftable
   * @brief the class checking the validity of 2-element negative shift operation
   *
   * This class is implemented with \c Check. When the input types
   * match the requirements of 2-element negative shift operation, a trait type
   * is defined. Otherwise, the trait type is not defined, which would
   * throw an error during compilation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2 the type of data as the displacement to shift.
   */
  template <typename T1, typename T2>
  class IsNegShiftable {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsNegShiftableFlag
       */
      typedef typename Check<IsNegShiftableFlag<T1,T2>::Flag>::Type Type;
  };

  /** @class IsShiftable3
   * @brief the class checking the validity of 3-element shift operation
   *
   * This class is implemented with \c Check. When the input types
   * match the requirements of 3-element shift operation, a trait type
   * is defined. Otherwise, the trait type is not defined, which would
   * throw an error during compilation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2,T3 the type of data as the displacement to shift.
   */
  template <typename T1,typename T2,typename T3>
  class IsShiftable3 {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsShiftable3Flag
       */
      typedef typename Check<IsShiftable3Flag<T1,T2,T3>::Flag>::Type  Type;
  };

  /** @class IsShiftable4
   * @brief the class checking the validity of 4-element shift operation
   *
   * This class is implemented with \c Check. When the input types
   * match the requirements of 4-element shift operation, a trait type
   * is defined. Otherwise, the trait type is not defined, which would
   * throw an error during compilation.
   *
   * @tparam T1 the type of data to be shifted
   * @tparam T2,T3,T4 the type of data as the displacement to shift.
   */
  template <typename T1,typename T2,typename T3,typename T4>
  class IsShiftable4 {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsShiftable4Flag
       */
      typedef typename Check<IsShiftable4Flag<T1,T2,T3,T4>::Flag>::Type  Type;
  };

}

#endif

