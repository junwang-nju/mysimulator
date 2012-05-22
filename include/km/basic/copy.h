
#ifndef _Basic_Copy_H_
#define _Basic_Copy_H_

#include "type-check/is-copyable.h"
#include "type-check/is-intrinsic.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Copy(T1& a, const T2& b) {
    typedef typename IsCopyable<T1,T2>::Type CopyCheck;
    typedef typename IsIntrinsic<T1>::Type  IntrinsicCheck1;
    typedef typename IsIntrinsic<T2>::Type  IntrinsicCheck2;
    a=static_cast<T1>(b);
  }

  template <typename T>
  void _Copy(bool& a, const T& b) {
    typedef typename IsCopyable<bool,T>::Type CopyCheck;
    typedef typename IsIntrinsic<T>::Type  IntrinsicCheck;
    a=(b==0?false:true);
  }

}

#endif

