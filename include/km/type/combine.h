
/**
 * @file type/combine.h
 * @brief derive the type of result calculated from objects with two other types
 *
 * @author Jun | junwang.nju@gmail.com
 */

#ifndef _Type_Combine_H_
#define _Type_Combine_H_

namespace mysimulator {

  template <typename T>
  class _LargeType {};

}

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

