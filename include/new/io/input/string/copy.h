
#ifndef _InputOutput_Input_String_Copy_H_
#define _InputOutput_Input_String_Copy_H_

#include "io/input/string/interface.h"
#include "io/input/base/copy.h"

namespace mysimulator {

  void copy(StringInput& I, const StringInput& cI) {
    assert(IsValid(cI));
    release(I);
    I.open(cI.buffer.size);
    typedef StringInput::ParentType   Type;
    copy(static_cast<Type&>(I),static_cast<const Type&>(cI));
    copy(I.buffer,cI.buffer);
    I.ReadLocation=cI.ReadLocation;
    I.Capacity=cI.Capacity;
  }

}

#endif

