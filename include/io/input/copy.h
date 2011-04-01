
#ifndef _InputOutput_Input_Base_Copy_H_
#define _InputOutput_Input_Base_Copy_H_

#include "io/input/interface.h"
#include "io/base/copy.h"

namespace mysimulator {

  void copy(InputBase& B, const InputBase& cB) {
    copy(static_cast<IOBase&>(B),static_cast<const IOBase&>(cB));
  }

}

#endif

