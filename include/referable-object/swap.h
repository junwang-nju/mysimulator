
#ifndef _Referable_Object_Swap_H_
#define _Referable_Object_Swap_H_

#include "referable-object/interface.h"
#include "generic/exchange.h"

namespace mysimulator {

  template <typename T>
  void swap(Object<T>& Oa, Object<T>& Ob) {
    exchange(Oa.pdata,Ob.pdata);
    exchange(reinterpret_cast<int&>(Oa.flag),reinterpret_cast<int&>(Ob.flag));
  }

}

#endif
