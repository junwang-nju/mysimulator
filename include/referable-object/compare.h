
#ifndef _Referable_Object_Compare_H_
#define _Referable_Object_Compare_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameObject(const Object<T1>& O1, const Object<T2>& O2) {
    return false;
  }

  template <typename T>
  bool IsSameObject(const Object<T>& O1, const Object<T>& O2) {
    return O1.pdata==O2.pdata;
  }

}

#endif

