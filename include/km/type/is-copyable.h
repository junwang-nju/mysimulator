
/**
 * @file type/is-copyable.h
 * @brief check if one object can be copied into another
 *
 * not all types can be copied from one to another in copy operations. to
 * enable the type check during the compilation, some type operations should be
 * empolyed. this file implements the related objects.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_IsCopyAble_H_
#define _Type_IsCopyAble_H_

#include "type/is-included.h"
#include "type/is-numeric.h"

namespace mysimulator {

  /** @class IsCopyableFlag
   * @brief the class to produce a flag related to validity of copy operation
   *
   * This class produces a flag based on the comparison of two input types.
   * This is the basic component to evaluate the validity of copy operation.
   *
   * @tparam T1 the type of data as destination of copy operation
   * @tparam T2 the type of data as source of copy operation
   */
  template <typename T1, typename T2>
  class IsCopyableFlag {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * When \c T1 -type data can accept the \c T2 -type data during copy,
       * the flag is set as \c true, otherwise \c false.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag::Flag
   *
   * The default flag is implemented for two numbers (which is checked with
   * \c IsNumericFlag). The relation between two types of numbers is checked
   * with \c IsIncludedFlag.
   */
  template <typename T1, typename T2> const bool IsCopyableFlag<T1,T2>::Flag=
    IsIncludedFlag<T1,T2>::Flag&&IsNumericFlag<T1>::Flag&&
    IsNumericFlag<T2>::Flag;

  /**
   * @brief the specialization of \c IsCopyableFlag for two same type of pointer
   *
   * This is a specialization of \c IsCopyableFlag. The concerned two types
   * are the same, are the pointers of same data. This type is also permitted.
   *
   * @tparam T the type of data which the pointer points to
   */
  template <typename T>
  class IsCopyableFlag<T*,T*> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is the flag for the specialization with two same pointers.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag<T*,T*>::Flag
   * Since two pointers are the same, these two objects are definitely copiable.
   * so the flag is set as \c true
   */
  template <typename T> const bool IsCopyableFlag<T*,T*>::Flag=true;

  /**
   * @brief the specialization of \c IsCopyableFlag for \c void pointer and regular pointer
   *
   * This is a specialization of \c IsCopyableFlag. The concerned destination
   * type is \c void\*, and the source data is a regular pointer. This
   * kind of copy is also permitted.
   *
   * @tparam T the type of data which is pointed by the regular pointer
   */
  template <typename T>
  class IsCopyableFlag<void*,T*> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is the flag for the specialization with a \c void pointer and
       * a regular pointer.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag<void*,T*>::Flag
   * the \c void pointer can accept any regular pointer. Therefore, it is 
   * set as \c true.
   */
  template <typename T> const bool IsCopyableFlag<void*,T*>::Flag=true;

  /**
   * @brief the specialization of \c IsCopyableFlag for regular pointer and \c void ppointer
   *
   * This is a specialization of \c IsCopyableFlag. The concerend destination
   * type is a regulat pointer, and the source data is a \c void\*. This kind
   * of copy is permitted. In practice, a \c reinterpret_cast conversion
   * would be necessary.
   */
  template <typename T>
  class IsCopyableFlag<T*,void*> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is the flag for the specialization with a regular pointer and
       * a \c void\* pointer.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag<T*,void*>::Flag;
   * \c void pointer can be converted to regular pointer, and the \c void\*
   * can be used to common interface for pointers. Therefore, It is set as
   * \c true
   */
  template <typename T> const bool IsCopyableFlag<T*,void*>::Flag=true;

}

#include "type/is-integer.h"

namespace mysimulator {

  /* the specialization of \c IsCopyableFlag for \c bool and regular type
   *
   * This is a specialization of \c IsCopyableFlag. The concerned copy
   * is from a regular type to a \c bool type. This kind of copy is permitted
   * only for the case from integer data to \c bool type.
   *
   * @tparam T the type of source data in copy operation
   */
  template <typename T>
  class IsCopyableFlag<bool,T> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is the specialization to check the copy from a regular type to
       * a \c bool type.
       */
      static const bool Flag;
  };

  /** @var IsCopyableFlag<bool,T>::Flag
   *
   * Following the basic convention of c language, the integer could be treated
   * as \c bool based on if they are equal to zero. Therefore, this flag is
   * implemented with the check if the regular type of data is integer (using
   * \c IsIntegerFlag.
   */
  template <typename T> const bool IsCopyableFlag<bool,T>::Flag=
    IsIntegerFlag<T>::Flag;

}

#include "type/is-intrinsic.h"

namespace mysimulator {

  union Unique64Bit;

  /**
   * @brief the specialization of \c IsCopyableFlag for copy from regular type to \c Unique64Bit
   *
   * This is a specialization of \c IsCopyableFlag. The concerned destination
   * type is \c Unique64Bit, and the source type is a regular type. This kind
   * of copy is permitted when the input type is compatible with \c Unique64Bit.
   *
   * @tparam T the type of source data in copy operation
   */
  template <typename T>
  class IsCopyableFlag<Unique64Bit,T> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from a regular type ti
       * \c Unique64Bit.
       */
      static const bool Flag;
  };

  /** @var IsCopyableFlag<Unique64Bit,T>::Flag
   *
   * Following the definition of \c Unique64Bit, the input type should
   * be a number and its size should be smaller than \c long \c double
   */
  template <typename T> const bool IsCopyableFlag<Unique64Bit,T>::Flag=
    IsNumericFlag<T>::Flag&&(sizeof(T)<sizeof(long double));

  /**
   * @brief the specialization of \c IsCopyableFlag for copy from \c Unique64Bit to regular type
   *
   * This is a specialization of \c IsCopyableFlag. The concered destination
   * type is a regulat type, and the type of source type is \c Unique64Bit.
   * This kind of copy is permitted when the regular type is compatible with
   * \c Unique64Bit.
   *
   * @tparam T the type of data are destination of copy
   */
  template <typename T>
  class IsCopyableFlag<T,Unique64Bit> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from \c Unique64Bit to
       * a regular type.
       */
      static const bool Flag;
  };

  /** @var IsCopyableFlag<T,Unique64Bit>::Flag
   *
   * Following the definition of \c Unique64Bit, the regular type should be
   * a number and its size should be smaller than \c long \c double.
   */
  template <typename T> const bool IsCopyableFlag<T,Unique64Bit>::Flag=
    IsNumericFlag<T>::Flag&&(sizeof(T)<sizeof(long double));

  union Unique128Bit;

  /**
   * @brief the specialization of \c IsCopyableFlag for copy from regular type to \c Unique128Bit
   *
   * This is a specialization of \c IsCopyableFlag. The concerned destination type
   * is \c Unique128Bit, and the type of source data is a regular type. This kind
   * of copy is permitted when the regular type is compatible with \c Unique128Bit.
   *
   * @tparam T the type of data as source of copy operation
   */
  template <typename T>
  class IsCopyableFlag<Unique128Bit,T> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from regular type to
       * \c Unique128Bit.
       */
      static const bool Flag;
  };

  /** @var IsCopyableFlag<Unique128Bit,T>::Flag
   *
   * Following the definition of \c Unique128Bit, the regular type should be
   * a number.
   */
  template <typename T> const bool IsCopyableFlag<Unique128Bit,T>::Flag=
    IsNumericFlag<T>::Flag;

  /**
   * @brief the specialization of \c IsCopyableFlag for copy from \c Unique64Bit to \c Unique128Bit
   *
   * This is a specialization of \c IsCopyableFlag. The concerned destination type
   * is \c Unique64Bit, and the source type is \c Unique128Bit. This kind of
   * copy is permitted.
   */
  template <>
  class IsCopyableFlag<Unique128Bit,Unique64Bit> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from \c Unique64Bit to
       * \c Unique128Bit.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag<Unique128Bit,Unique64Bit>::Flag
   *
   * Following the definition of \c Unique64Bit and \c Unique128Bit, this
   * copy operation is permitted. Thus the flag is set as \c true.
   */
  const bool IsCopyableFlag<Unique128Bit,Unique64Bit>::Flag=true;

  /**
   * @brief the specialization of \c IsCopyableFlag for copy from \c Unique128Bit to regular type
   *
   * This is a specialization of \c IsCopyableFlag. the concerned destination type
   * is \c Unique128Bit, and the source type is the regular type. This kind of 
   * copy is permitted when the regular type is compatible with \c Unique128Bit.
   *
   * @tparam T the type of data are destination of copy
   */
  template <typename T>
  class IsCopyableFlag<T,Unique128Bit> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from \c Unique128Bit to
       * regular type.
       */
      static const bool Flag;
  };

  /** @var IsCopyableFlag<T,Unique128Bit>::Flag
   *
   * Following the definition of \c Unique128Bit, this copy operation
   * is permitted when the regular type is compatible with \c Unique128Bit.
   */
  template <typename T> const bool IsCopyableFlag<T,Unique128Bit>::Flag=
    IsNumericFlag<T>::Flag;

  /**
   * @brief IsCopyableFlag<Unique64Bit,Unique128Bit>::Flag
   *
   * This is a specialization of \c IsCopyableFlag. the concerned destination type
   * is \c Unique64Bit, anf the source type is \c Unique128Bit. This copy
   * operation is permitted.
   */
  template <>
  class IsCopyableFlag<Unique64Bit,Unique128Bit> {
    public:
      /** @var Flag
       * @brief the static flag indicating if copy is valid
       *
       * This is a specialization to check the copy from \c Unique128Bit to
       * \c Unique64Bit.
       */
      static const bool Flag;
  };
  /** @var IsCopyableFlag<Unique64Bit,Unique128Bit>::Flag
   *
   * Following thr definition of \c Unique64Bit and \c Unique128Bit,
   * this operation is permitted. Thus the flag is set as \c true.
   */
  const bool IsCopyableFlag<Unique64Bit,Unique128Bit>::Flag=true;

}

#include "type/check-object.h"

namespace mysimulator {

  /** @class IsCopyable
   * @brief the class to check if the copy operation is valid
   *
   * This class is implemented with \c Check. When a data of \c T2
   * could be copied to the data of \c T1, a trait type would be
   * defined. Otherwise, the definition of trait would fail during
   * compilation.
   *
   * @tparam T1 the type of destination data
   * @tparam T2 the type of source data
   */
  template <typename T1, typename T2>
  class IsCopyable {
    public:
      /** @typedef Type
       * @brief the definition of the trait type
       *
       * This is implemented with \c Check and \c IsCopyableFlag.
       */
      typedef typename Check<IsCopyableFlag<T1,T2>::Flag>::Type  Type;
  };

}

#endif

