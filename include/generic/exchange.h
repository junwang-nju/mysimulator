
#ifndef _Generic_Exchange_H_
#define _Generic_Exchange_H_

#include "intrinsic-type/exchange.h"

namespace mysimulator {

  template <typename T>
  void exchange(T*& p1, T*& p2) {
    exchange(reinterpret_cast<void*&>(p1),reinterpret_cast<void*&>(p2));
  }

}

#endif

