
#ifndef _Object_Exchange_H_
#define _Object_Exchange_H_

#include "object/interface.h"
#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void exchange(Object<T>& O1, Object<T>& O2) { exchange(O1(),O2()); }

  template <typename T>
  void exchange(Object<T>& O, T& d) { exchange(O(),d); }

  template <typename T>
  void exchange(T& d, Object<T>& O) { exchange(O,d); }

}

#endif

