
#ifndef _Referable_Object_Allocate_H_
#define _Referable_Object_Allocate_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T>
  void allocate(Object<T>& O) {
    release(O);
    O.pdata=new T;
    O.flag=Allocated;
  }

  template <typename T>
  void imprint(Object<T>& O, const Object<T>& cO) {
    allocate(O);
    imprint(O(),cO());
  }

  template <typename T>
  void imprint(Object<T>& O, const T& value) {
    allocate(O);
    imprint(O(),value);
  }

  template <typename T>
  void imprint(T& value, const Object<T>& cO) {
    assert(IsValid(cO));
    imprint(value,cO());
  }

}

#endif

