
#ifndef _InputOutput_Input_File_Copy_H_
#define _InputOutput_Input_File_Copy_H_

#include "io/input/file/interface.h"
#include "io/input/base/copy.h"

namespace mysimulator {

  void copy(FileInput& I, const FileInput& cI) {
    assert(IsValid(cI));
    release(I);
    typedef FileInput::ParentType   Type;
    copy(static_cast<Type&>(I),static_cast<const Type&>(cI));
    I.fptr=cI.fptr;
  }

}

#endif

