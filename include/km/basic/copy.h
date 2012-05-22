
#ifndef _Basic_Copy_H_
#define _Basic_Copy_H_

#include "type/is-copyable.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void _Copy(T1& a, const T2& b) {
    typedef typename IsCopyable<T1,T2>::Type CopyCheck;
    a=static_cast<T1>(b);
  }

  template <typename T>
  void _Copy(bool& a, const T& b) {
    typedef typename IsCopyable<bool,T>::Type CopyCheck;
    a=(b==0?false:true);
  }

}

#endif

