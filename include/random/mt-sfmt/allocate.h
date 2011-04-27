
#ifndef _Random_MT_SFMT_Allocate_H_
#define _Random_MT_SFMT_Allocate_H_

#include "random/mt-sfmt/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  void allocate(MT_SFMT<LFac>& G) {
    G.init(5489U);
  }

}

#endif

