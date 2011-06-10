
#ifndef _Referable_Object_InputOutput_H_
#define _Referable_Object_InputOutput_H_

#include "referable-object/interface.h"
#include "io/output/interface.h"
#include "io/input/interface.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& B,const Object<T>& O) {
    assert(IsValid(B));
    return (B<<O());
  }

  template <typename T>
  InputBase& operator>>(InputBase& B, Object<T>& O) {
    assert(IsValid(B));
    return (B>>O());
  }

}

#endif

