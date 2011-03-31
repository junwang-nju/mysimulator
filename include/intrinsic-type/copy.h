
#ifndef _Intrinsic_Type_Utility_Copy_H_
#define _Intrinsic_Type_Utility_Copy_H_

#include "intrinsic-type/assign-type.h"

namespace mysimulator {

  template <typename T, typename T1>
  void copy(T& a, const T1& b) {
    typedef typename _Assign<T,T1>::Type  Type;
    a=static_cast<Type>(b);
  }

  void copy(bool& b, const bool& rb) { b=rb; }
  template <typename T>
  void copy(bool& b, const T& i) {
    typedef typename _Assign<bool,T>::Type  Type;
    b=(i==0?false:true);
  }

  template <typename T>
  void copy(void*& ptr, const T* tptr) {
    ptr=reinterpret_cast<void*>(const_cast<T*>(tptr));
  }
  template <typename T>
  void copy(T*& tptr, const void* ptr) {
    tptr=reinterpret_cast<T*>(const_cast<void*>(ptr));
  }
  void copy(void*& ptr, void* const& ptr1) { ptr=const_cast<void*>(ptr1); }
  template <typename T>
  void copy(T*& ptr, const T* tptr) { ptr=const_cast<T*>(tptr); }

}

#endif
