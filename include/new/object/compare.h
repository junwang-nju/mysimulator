
#ifndef _Object_Compare_H_
#define _Object_Compare_H_

#include "object/interface.h"
#include "pointer/compare.h"

namespace mysimulator {

  template <typename T1, typename T2>
  bool IsSame(const Object<T1>& O1, const Object<T2>& O2) {
    return IsSame(static_cast<typename Object<T1>::ParentType&>(O1),
                  static_cast<typename Object<T2>::ParentType&>(O2));
  }

  template <typename T1, typename T2>
  bool IsSame(const Object<T1>& O, const T2& d) {
    return IsSame(static_cast<typename Object<T1>::ParentType&>(O),&d);
  }

  template <typename T1, typename T2>
  bool IsSame(const T1& d, const Object<T2>& O) { return IsSame(O,d); }

}

#include "intrinsic-type/compare.h"

namespace mysimulator {

  template <typename T1, typename T2>
  int compare(const Object<T1>& O1, const Object<T2>& O2) {
    return compare(O1(),O2());
  }

  template <typename T1, typename T2>
  int compare(const Object<T1>& O, const T2& d) { return compare(O(),d); }

  template <typename T1, typename T2>
  int compare(const T1& d, const Object<T2>& O) { return compare(O,d); }

}

#endif

