
#ifndef _InputOutput_Input_Base_Copy_H_
#define _InputOutput_Input_Base_Copy_H_

#include "io/input/base/interface.h"
#include "io/base/copy.h"

namespace mysimulator {

  void copy(InputBase& I, const InputBase& cI) {
    assert(IsValid(cI));
    typedef InputBase::ParentType Type;
    copy(static_cast<Type&>(I),static_cast<const Type&>(cI));
  }

}

#endif

