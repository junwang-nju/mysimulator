
#ifndef _Object_InputOutput_H_
#define _Object_InputOutput_H_

#include "object/interface.h"
#include "io/output/base/interface.h"

namespace mysimulator {

  template <typename T>
  OutputBase& operator<<(OutputBase& O, const Object<T>& B) {
    assert(IsValid(B)); O<<B(); return O;
  }

}

#include "io/input/base/interface.h"

namespace mysimulator {

  template <typename T>
  InputBase& operator>>(InputBase& I, Object<T>& B) {
    assert(IsValid(B)); I>>B(); return I;
  }

}

#endif

