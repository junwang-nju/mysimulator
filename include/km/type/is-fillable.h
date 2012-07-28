
/**
 * @file type/is-fillable.h
 * @brief check if one object can be filled with another
 *
 * To fill a certain type of data, the input should have some requirements
 * based on the input type. to enable the type check during the compilation,
 * some type operations should be employed. this file implements the related
 * objects
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsFillAble_H_
#define _Type_IsFillAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsFillableFlag
   * @brief the class to produce flag related to validity of fill operation
   *
   * This class produces a flag based on the comparisons of two input types.
   * This is the basic component to evaluate the validity of fill operation
   *
   * @tparam T1 the type of data to be filled
   * @tparam T2 the type of data to be used to fill \c T1 -type data
   */
  template <typename T1, typename T2>
  class IsFillableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if fill is valid
       *
       * When \c T1 -type data can be filled with \c T2 -type data, namely
       * \c T1 -type data can be split as several (or one) \c T2 -type data,
       * the fill operation is valid. the corresponding flag would beset as
       * \c true, otherwise \c false.
       */
      static const bool Flag;
  };
  /** @var IsFillableFlag::Flag
   *
   * The default flag is implemeted for two numbers (which are checked 
   * with \c IsNumericFlag). The relation between two types is checked
   * with \c IsIncludedFlag.
   */
  template <typename T1, typename T2> const bool IsFillableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  /**
   * @brief the specialization of \c IsFillableFlag for two \c bool type
   *
   * This is a specialization of \c IsFillableFlag. Here two data are all
   * \c bool type. The fill operation is permitted.
   */
  template <>
  class IsFillableFlag<bool,bool> {
    public:
      /** @var Flag
       * @brief the static flag indicating if fill is valid
       *
       * This is the flag for the specialization with two \c bool types
       */
      static const bool Flag;
  };
  /** @var IsFillableFlag<bool,bool>::Flag
   *
   * Since two types are the same, this matches the requirement of fill
   * operation. Therefore, it is set as \c true.
   */
  const bool IsFillableFlag<bool,bool>::Flag=true;

}

#include "type/is-intrinsic.h"

namespace mysimulator {

  union Unique64Bit;
  /**
   * @brief the specialization of \c IsFillableFlag for Unique64Bit and regular type
   *
   * THis is a specialization of \c IsFillableFlag. This kind of fill
   * is permitted only when the type \c T is not larger than \c Unique64Bit.
   *
   * @tparam T the type of data to be used to fill \c Unique64Bit data
   */
  template <typename T>
  class IsFillableFlag<Unique64Bit,T> {
    public:
      static const bool Flag;
  };
  template <typename T>
  const bool IsFillableFlag<Unique64Bit,T>::Flag=
    IsNumericFlag<T>::Flag&&(sizeof(T)<sizeof(long double));

  union Unique128Bit;
  template <typename T>
  class IsFillableFlag<Unique128Bit,T> {
    public:
      static const bool Flag;
  };
  template <typename T>
  const bool IsFillableFlag<Unique128Bit,T>::Flag=IsNumericFlag<T>::Flag;

  template <>
  class IsFillableFlag<Unique128Bit,Unique64Bit> {
    public:
      static const bool Flag;
  };
  const bool IsFillableFlag<Unique128Bit,Unique64Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class IsFillable {
    public: typedef typename Check<IsFillableFlag<T1,T2>::Flag>::Type   Type;
  };

}

#endif

