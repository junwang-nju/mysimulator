
#ifndef _InputOutput_Output_File_Copy_H_
#define _InputOutput_Output_File_Copy_H_

#include "io/output/file/interface.h"
#include "io/output/base/copy.h"

namespace mysimulator {

  void copy(FileOutput& F, const FileOutput& cF) {
    assert(IsValid(cF));
    typedef FileOutput::ParentType  Type;
    copy(static_cast<Type&>(F),static_cast<const Type&>(cF));
    F.fptr=cF.fptr;
  }

}

#endif

