
#ifndef _Referable_Object_Mirror_H_
#define _Referable_Object_Mirror_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T>
  void mirror(Object<T>& O, const Object<T>& cO) {
    O.pdata=cO.pdata;
    O.flag=cO.flag;
  }

}

#endif

