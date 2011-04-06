
#ifndef _InputOutput_Base_Copy_H_
#define _InputOutput_Base_Copy_H_

#include "io/base/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  void copy(IOBase& B, const IOBase& cB) {
    for(unsigned int i=0;i<NumberIOState;++i) copy(B.state[i],cB.state[i]);
  }

}

#endif

