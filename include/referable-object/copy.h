
#ifndef _Referable_Object_Copy_H_
#define _Referable_Object_Copy_H_

#include "referable-object/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename T1, typename T2>
  void copy(Object<T1>& O, const Object<T2>& cO) { copy(O(),cO()); }

  template <typename T1, typename T2>
  void copy(Object<T1>& O, const T2& ovalue) { copy(O(),ovalue); }

  template <typename T1, typename T2>
  void copy(T1& ovalue, const Object<T2>& O) { copy(ovalue,O()); }

}

#include "referable-object/refer.h"

namespace mysimulator {

  template <typename T>
  void copy(Object<T>& O, const T& value, const ObjectStateName& flag) {
    if(flag==Allocated) {
      allocate(O);
      imprint(O,value);
      copy(O,value);
    } else if(flag==Referred) refer(O,value);
    else Error("Improper State Type in Object copy!");
  }

}

#endif

