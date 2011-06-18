
#ifndef _InputOutput_Output_File_Copy_H_
#define _InputOutput_Output_File_Copy_H_

#include "io/output/interface.h"
#include "io/output/copy.h"

namespace mysimulator {

  void copy(FileOutput& O, const FileOutput& cO) {
    assert(IsValid(cO));
    release(O);
    copy(static_cast<OutputBase&>(O),static_cast<const OutputBase&>(cO));
    O.fptr=cO.fptr;
  }

}

#endif

