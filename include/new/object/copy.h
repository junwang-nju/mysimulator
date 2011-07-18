
#ifndef _Object_Copy_H_
#define _Object_Copy_H_

#include "object/interface.h"
#include "intrinsic-type/copy.h"
#include "intrinsic-type/valid.h"

namespace mysimulator {

  template <typename T, typename cT>
  void copy(Object<T>& O, const Object<cT>& cO) { copy(O(),cO()); }

  template <typename T, typename cT>
  void copy(Object<T>& O, const cT& d) { assert(IsValid(d)); copy(O(),d); }

  template <typename T, typename cT>
  void copy(T& d, const Object<cT>& cO) { assert(IsValid(d)); copy(d,cO()); }

}

#endif

