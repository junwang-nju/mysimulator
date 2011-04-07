
#ifndef _Referable_Object_InputOutput_H_
#define _Referable_Object_InputOutput_H_

#include "referable-object/interface.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& B,const Object<T>& O) {
    assert(IsValid(B));
    return (B<<O());
  }

}

#endif

