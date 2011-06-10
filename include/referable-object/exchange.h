
#ifndef _Referable_Object_Exchange_H_
#define _Referable_Object_Exchange_H_

#include "referable-object/interface.h"
#include "generic/exchange.h"

namespace mysimulator {

  template <typename T>
  void exchange(Object<T>& Oa, Object<T>& Ob) { exchange(Oa(),Ob()); }

}

#endif

