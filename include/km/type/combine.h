
/**
 * @file type/combine.h
 * @brief derive the type of result calculated from objects with two other types
 *
 * In some two-member operations, the type of results depends on the input
 * types. How to get the resultant type without manual interference is the
 * purpose of this file. Here we define some classes to get the resultant
 * types with generic programming.
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_Combine_H_
#define _Type_Combine_H_

namespace mysimulator {

  /** @class _LargeType
   * @brief the class to get type which is one-level larger
   *
   * All the types can be aligned in a sequential order based on the
   * their inclusion relation. This class expects to give out the type
   * which is larger than the input type and us closest to the input type.
   * This is the default form. The input type is used to define the
   * \c Type trait.(This would act as an exit for unexpected types which
   * cannnot be operated by \c CombineType)  The detailed relations
   * would be implemented with specializations, since the relation cannot
   * be expressed with simple logic.
   *
   * @tparam T the input type
   */
  template <typename T>
  class _LargeType { public: typedef T Type; };

}

/** @def _LargeDEF_
 * @brief the macro to implement specializations of class \c _LargeType
 *
 * The relation between types cannot determined by logic operation. it needs
 * many specifications for class. This macro omplements the general
 * form of the specialization of class \c _LargeType.
 *
 * @param T the input type for class \c _LargeType
 * @param TL the type to define the trait in class \c _LargeType
 */
#ifndef _LargeDEF_
#define _LargeDEF_(T,TL) \
  template <> class _LargeType<T> { public: typedef TL Type; };
#else
#error "Duplicate _LargeDEF_"
#endif

namespace mysimulator {

  /** @property typedef long double _LargeType<long double>::Type
   * @brief define \c long \c double as the trait \c Type
   *
   * Since \c long \c double is the type with largest range, thus here
   * we use \c long \c double as the present trait
   */
  /**
   * @brief the specialization of \c _LargeType for \c long \c double type
   * 
   * This defines a specialization of \c _LargeType with the input type
   * of \c long \c double
   */
  _LargeDEF_(long double, long double)
  /** @property typedef long double _LargeType<double>::Type
   * @brief define \c long \c double as the trait \c Type
   *
   * \c long \c double has larger range than \c double, and matches the
   * requirement of class \c _LargeType
   */
  /**
   * @brief the specialization of \c _LargeType for \c double type
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c double
   */
  _LargeDEF_(double, long double)
  /** @property typedef double _LargeType<float>::Type
   * @brief define \c double as the trait \c Type
   *
   * \c double has larger range than \c float, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c float type
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c float.
   */
  _LargeDEF_(float, double)
  /** @property typedef float _LargeType<long long>::Type
   * @brief define \c float as the trait \c Type
   *
   * \c float has larger range than \c long \c long, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c long \c long type
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c long \c long.
   */
  _LargeDEF_(long long, float)
  /** @property typedef float _LargeType<unsigned long long>::Type
   * @brief define \c float as the trait \c Type
   *
   * \c float has larger range than \c unsigned \c long \c long, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c unsigned \c long \c long type
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c unsigned \c long \c long
   */
  _LargeDEF_(unsigned long long, float)
  /** @property typedef long long _LargeType<int>::Type
   * @brief define \c long \c long as the trait \c Type
   *
   * \c long \c long has larger range than \c int, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c int
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c int
   */
  _LargeDEF_(int, long long)
  /** @property typedef long long _LargeType<unsigned int>::Type
   * @brief define \c long \c long as the trait \c Type
   *
   * \c long \c long has larger range than \c unsigned \c int, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c unsigned \c int
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c unsigned \c int
   */
  _LargeDEF_(unsigned int, long long)
  /** @property typedef long long _LargeType<long>::Type
   * @brief define \c long \c long as the trait \c Type
   *
   * \c long \c long has larger range than \c long, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c long
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c long
   */
  _LargeDEF_(long, long long)
  /** @property typedef long long _LargeType<unsigned long>::Type
   * @brief define \c long \c long as the trait \c Type
   *
   * \c long \c long has larger range than \c unsigned \c long, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c unsigned \c long
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c unsigned \c long
   */
  _LargeDEF_(unsigned long, long long)
  /** @property typedef int _LargeType<short>::Type
   * @brief define \c int as the trait \c Type
   *
   * \c int has larger range than \c short, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c short
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c short
   */
  _LargeDEF_(short, int)
  /** @property typedef int _LargeType<unsigned short>::Type
   * @brief define \c int as the trait \c Type
   *
   * \c int has larger range than \c unsigned \c short, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c unsigned \c short
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c unsigned \c short
   */
  _LargeDEF_(unsigned short, int)
  /** @property typedef short _LargeType<char>::Type
   * @brief define \c short as the trait \c Type
   *
   * \c short has larger range than \c char, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c char
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c char
   */
  _LargeDEF_(char, short)
  /** @property typedef short _LargeType<unsigned char>::Type
   * @brief define \c short as the trait \c Type
   *
   * \c short has larger range than \c unsigned \c char, and matches the
   * requirement of class \c _LargeType
   */
  /** @brief the specialization of \c _LargeType for \c unsigned \c char
   *
   * This defines a specialization of \c _LargeType with the input type
   * of \c unsigned \c char
   */
  _LargeDEF_(unsigned char, short)

}

#ifdef _LargeDEF_
#undef _LargeDEF_
#endif

#include "type/is-included.h"

namespace mysimulator {

  /** @class _CombineState
   * @brief generate a state based on input types
   *
   * This class is used to generate state based on the input types. This
   * offers a way to compare two types. The resultant state flag could be
   * used to produce the type as the combination of two input types.
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class _CombineState {
    public:
      /** @var State
       * @brief the state flag
       *
       * Since the state has multiple possibilities, it cannot be expressed
       * with \c bool, but use \c int variable
       */
      static const int State;
  };

  /** @var _CombineState::State
   *
   * The state is initialized based on \c IsIncludedFlag. When the range
   * of \c T1 includes the range of \c T2, the state is \c 1. when the range
   * of \c T2 covers that of \c T1, the state is \c -1. For other cases,
   * the state is \c 0.
   */
  template <typename T1, typename T2>
  const int _CombineState<T1,T2>::State=
    (IsIncludedFlag<T1,T2>::Flag?1:
    (IsIncludedFlag<T2,T1>::Flag?-1:0));

  /** @class _CombineProduce
   * @brief select type from input types based on state
   *
   * This class would select a type from two input types based on the
   * state flag. This defines the operation with help of the state information,
   * and implements the process from state to type. For the default class,
   * there are no contents inside.
   *
   * @tparam T1,T2 two input types
   * @tparam state the state flag
   */
  template <typename T1, typename T2, int State>
  class _CombineProduce {};

}

#include "type/check-object.h"

namespace mysimulator {

  /**
   * @brief the specialization of \c _CombineProduce with state of \c 1
   *
   * for the state of \c 1, the first input type is selected to define
   * the trait. To ensure the consistency of input types and state,
   * a check with \c Check object is used (if they are not consistent,
   * a compile error would be thrown out)
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,1> {
    public:
      /** @typedef Type
       * @brief select the type \c T1 as trait Type
       *
       * the state \c 1 indicates that the first type has larger range.
       * Thereofore, the first type \c T1 is used in trait definition.
       */
      typedef T1  Type;
    private:
      /** @typedef StateCheck
       * @brief the check for the consostency between types and state
       *
       * This is implemented with \c Check object, and requires the
       * types match the condition of state \c 1.
       */
      typedef typename Check<_CombineState<T1,T2>::State==1>::Type  StateCheck;
  };

  /**
   * @brief the specialization of \c _CombineProduce with the state \c -1
   *
   * for state of \c -1, the second input type is selected to define the trait.
   * To ensure the consistency of input types and state, a check with \c Check
   * object is used (if they are not consitent, a compile error would be
   * thrown out)
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,-1> {
    public:
      /** @typedef Type
       * @brief select the type \c T2 as trait Type
       *
       * the state \c -1 indicates that the second type has larger range.
       * therefore, the second type \c T2 is used in trait definition.
       */
      typedef T2  Type;
    private:
      /** @typedef StateCheck
       * @brief the check for the consostency between types and state
       *
       * This is implemented with \c Check object, and requires the
       * types match the condition of state \c -1.
       */
      typedef typename Check<_CombineState<T1,T2>::State==-1>::Type  StateCheck;
  };

  /**
   * @brief the specialization of \c _CombineProduce with the state \c 0
   *
   * for state of \c 0, the second input type is selected to define the trait.
   * To ensure the consistency of input types and state, a check with \c Check
   * object is used (if they are not consitent, a compile error would be
   * thrown out)
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,0> {
    public:
      /** @typedef Type
       * @brief select the larger type when input types do not include the other
       *
       * the state \c 0 indicates that two input types cannot include the
       * other. therefore, the larger type of \c T1 (which is implemented with
       * \c _LargeType) is used in trait definition.
       */
      typedef typename _LargeType<T1>::Type Type;
    private:
      /** @typedef StateCheck
       * @brief the check for the consostency between types and state
       *
       * This is implemented with \c Check object, and requires the
       * types match the condition of state \c 0.
       */
      typedef typename Check<_CombineState<T1,T2>::State==0>::Type  StateCheck;
  };

  /** @class CombineType
   * @brief generate type based on input types
   *
   * use the _CombineState, _CombineProduce to produce the type as the result
   * of two input types. This is the interface for public use.
   *
   * @tparam T1,T2 two input types
   */
  template <typename T1, typename T2>
  class CombineType {
    public:
      /** @typedef Type
       * @brief the combine type of input types
       *
       * This is implemented with some internal classes, \c _CombineProduce and
       * \c _CombineState.
       */
      typedef typename _CombineProduce<T1,T2,_CombineState<T1,T2>::State>::Type
              Type;
  };

}

#endif

