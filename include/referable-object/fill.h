
#ifndef _Referable_Object_Fill_H_
#define _Referable_Object_Fill_H_

#include "referable-object/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void fill(Object<T1>& O, const Object<T2>& cO) {
    assert(IsValid(O)&&IsValid(cO));
    fill(O(),cO());
  }

  template <typename T1, typename T2>
  void fill(Object<T1>& O, const T2& ovalue) {
    assert(IsValid(O));
    fill(O(),ovalue);
  }

  template <typename T1, typename T2>
  void fill(T1& ovalue, const Object<T2>& O) {
    assert(IsValid(O));
    fill(ovalue,O());
  }

}

#endif

