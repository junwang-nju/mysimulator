
#ifndef _Random_MT_SFMT_InputOutput_H_
#define _Random_MT_SFMT_InputOutput_H_

#include "random/mt-sfmt/interface.h"
#include "io/input/interface.h"
#include "io/output/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  OutputBase& operator<<(OutputBase& os, const MT_SFMT<LFac>& G) {
  }

}

#endif

