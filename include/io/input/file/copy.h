
#ifndef _InputOutput_Input_File_Copy_H_
#define _InputOutput_Input_File_Copy_H_

#include "io/input/file/interface.h"
#include "io/input/copy.h"
#include "generic/copy.h"

namespace mysimulator {

  void copy(FileInput& I, const FileInput& cI) {
    release(I);
    copy(static_cast<InputBase&>(I),static_cast<const InputBase&>(cI));
    copy(I.fptr,cI.fptr);
  }

}

#endif

