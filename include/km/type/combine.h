
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
   * This is the default form. There are no contents. The detailed relations
   * would be implemented with specializations, since the relation cannot
   * be expressed with simple logic.
   *
   * @tparam T the input type
   */
  template <typename T>
  class _LargeType {};

}

/** @def _LargeDEF_
 * @brief the macro to implement specializations of class \c _LargeType
 */
#ifndef _LargeDEF_
#define _LargeDEF_(T,TL) template <> class _LargeType<T> { typedef TL Type; };
#else
#error "Duplicate _LargeDEF_"
#endif

namespace mysimulator {

  _LargeDEF_(long double, long double)
  _LargeDEF_(double, long double)
  _LargeDEF_(float, double)
  _LargeDEF_(long long, float)
  _LargeDEF_(unsigned long long, float)
  _LargeDEF_(int, long long)
  _LargeDEF_(unsigned int, long long)
  _LargeDEF_(long, long long)
  _LargeDEF_(unsigned long, long long)
  _LargeDEF_(short, int)
  _LargeDEF_(unsigned short, int)
  _LargeDEF_(char, short)
  _LargeDEF_(unsigned char, short)

}

#ifdef _LargeDEF_
#undef _LargeDEF_
#endif

#include "type/is-included.h"

namespace mysimulator {

  template <typename T1, typename T2>
  class _CombineState { public: static const int State; };

  template <typename T1, typename T2>
  const int _CombineState<T1,T2>::State=
    (IsIncludedFlag<T1,T2>::Flag?1:
    (IsIncludedFlag<T2,T1>::Flag?-1:0));

  template <typename T1, typename T2, int State>
  class _CombineProduce {};

  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,1> {  public: typedef T1  Type; };

  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,-1> { public: typedef T2  Type; };

  template <typename T1, typename T2>
  class _CombineProduce<T1,T2,0> {
    public: typedef typename _LargeType<T1>::Type Type;
  };

  template <typename T1, typename T2>
  class CombineType {
    public:
      typedef typename _CombineProduce<T1,T2,_CombineState<T1,T2>::State>::Type
              Type;
  };

}

#endif

