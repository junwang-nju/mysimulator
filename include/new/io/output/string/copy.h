
#ifndef _InputOutput_Output_String_Copy_H_
#define _InputOutput_Output_String_Copy_H_

#include "io/output/string/interface.h"
#include "io/output/base/copy.h"
#include "array/1d/copy.h"

namespace mysimulator {

  void copy(StringOutput& S, const StringOutput& cS) {
    assert(IsValid(cS));
    release(S);
    S.open(cS.buffer.size);
    copy(S.buffer,cS.buffer);
    S.WriteLocation=cS.WriteLocation;
    S.Capacity=cS.Capacity;
    typedef StringOutput::ParentType  Type;
    copy(static_cast<Type&>(S),static_cast<const Type&>(cS));
  }

}

#endif

