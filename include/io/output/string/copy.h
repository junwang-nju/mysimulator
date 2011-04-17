
#ifndef _InputOutput_Output_String_Copy_H_
#define _InputOutput_Output_String_Copy_H_

#include "io/output/string/interface.h"

namespace mysimulator {

  void copy(StringOutput& O, const StringOutput& cO) {
    assert(IsValid(cO));
    O.open(cO.buffer.size);
    copy(O.buffer,cO.buffer);
    copy(O.property,cO.property);
    copy(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(cO));
  }

}

#endif

