
#ifndef _Referable_Object_Compare_H_
#define _Referable_Object_Compare_H_

#include "referable-object/interface.h"
#include "intrinsic-type/compare.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSameObject(const Object<T1>& O1, const Object<T2>& O2) {
    return false;
  }

  template <typename T>
  bool IsSameObject(const Object<T>& O1, const Object<T>& O2) {
    return O1.pdata==O2.pdata;
  }

  template <typename T>
  bool IsSameObject(const Object<T>& O, const T& value) {
    return O.pdata==&value;
  }

  template <typename T>
  bool IsSameObject(const T& value, const Object<T>& O) {
    return O.pdata==&value;
  }

  template <typename T1, typename T2>
  int compare(const Object<T1>& O1, const Object<T2>& O2) {
    return compare(O1(),O2());
  }

  template <typename T>
  int compare(const Object<T>& O, const T& value){ return compare(O(),value); }

  template <typename T>
  int compare(const T& value, const Object<T>& O){ return compare(value,O()); }

}

#endif

