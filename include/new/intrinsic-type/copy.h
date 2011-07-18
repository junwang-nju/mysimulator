
#ifndef _Intrisic_Type_Copy_H_
#define _Intrisic_Type_Copy_H_

#include "intrinsic-type/reflection/dual.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(T& d, const cT& cd) {
    typedef typename _Dual<T,cT>::AssignType Type;
    d=static_cast<const Type&>(cd);
  }

  void copy(bool& b, const bool& cb) { b=cb; }

  template <typename T>
  void copy(bool& b, const T& d) {
    typedef typename _Dual<bool,T>::AssignType Type;
    b=(d==0?false:true);
  }

  template <typename T, typename cT>
  void copy(T*& p, const cT* const& cp) {
    typedef typename _Dual<T*,cT*>::AssignType Type;
    p=reinterpret_cast<Type>(const_cast<cT* const&>(cp));
  }

}

#endif

