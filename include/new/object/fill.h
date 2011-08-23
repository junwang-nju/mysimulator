
#ifndef _Object_Fill_H_
#define _Object_Fill_H_

#include "object/interface.h"
#include "intrinsic-type/fill.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void fill(Object<T1>& O, const Object<T2>& fO) { fill(O(),fO()); }

  template <typename T1, typename T2>
  void fill(Object<T1>& O, const T2& d) { fill(O(),d); }

  template <typename T1, typename T2>
  void fill(T1& d, const Object<T2>& O) { fill(d,O()); }

}

#endif

