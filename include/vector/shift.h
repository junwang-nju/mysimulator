
#ifndef _Vector_Shift_H_
#define _Vector_Shift_H_

#include "vector/interface.h"

namespace mysimulator {

  template <typename T, typename fT, typename sT>
  void shift(Vector<T>& v, const fT& d, const Vector<sT>& sv) {
    assert(IsValid(v)&&IsValid(sv));
    unsigned int n=(v.size<sv.size?v.size:sv.size);
    T* p=v();
    sT* sp=const_cast<sT*>(sv());
    T* pend=p+n;
    for(;p!=pend;)  shift(*(p++),d,*(sp++));
  }

}

#endif

