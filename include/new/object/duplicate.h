
#ifndef _Object_Duplicate_H_
#define _Object_Duplicate_H_

#include "object/allocate.h"
#include "object/copy.h"

namespace mysimulator {

  template <typename T>
  void duplicate(Object<T>& O, const Object<T>& cO) {
    assert(IsValid(cO));
    imprint(O,cO);
    copy(O,cO);
  }

  template <typename T>
  void duplicate(Object<T>& O, const T& cO) {
    assert(IsValid(cO));
    imprint(O,cO);
    copy(O,cO);
  }

  template <typename T>
  void duplicate(T& O, const Object<T>& cO) {
    assert(IsValid(cO));
    imprint(O,cO);
    copy(O,cO);
  }

}

#endif

