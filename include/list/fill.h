
#ifndef _List_Fill_H_
#define _List_Fill_H_

#include "list/interface.h"
#include "vector/fill.h"

namespace mysimulator {

  template <typename T, typename fT>
  void fill(List<T>& L, const fT& value) {
    assert(IsValid(L));
    fill(static_cast<Vector<T>&>(L),value);
  }

}

#endif

