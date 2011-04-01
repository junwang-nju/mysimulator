
#ifndef _Referable_Object_Refer_H_
#define _Referable_Object_Refer_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T>
  void refer(Object<T>& O, const Object<T>& cO) {
    assert(IsValid(cO));
    release(O);
    O.pdata=const_cast<T*>(cO.pdata);
    O.flag=Referred;
  }

  template <typename T>
  void refer(Object<T>& O, const T& ovalue) {
    release(O);
    O.pdata=const_cast<T*>(&ovalue);
    O.flag=Referred;
  }

}

#endif

