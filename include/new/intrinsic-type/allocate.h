
#ifndef _Intrinsic_Type_Allocate_H_
#define _Intrinsic_Type_Allocate_H_

#include "intrinsic-type/reflection/single.h"

namespace mysimulator {

  template <typename T>
  void allocate(T&) { typedef typename _Single<T>::Type Type; }

  template <typename T>
  void allocate(T* &p) { p=new T; }

  template <typename T>
  void allocate(T* &p, const unsigned int& n) { p=new T[n]; }

  template <typename T>
  void imprint(T&,const T&) { typedef typename _Single<T>::Type Type; }

}

#endif

