
#ifndef _Random_MT_DSFMT_Allocate_H_
#define _Random_MT_DSFMT_Allocate_H_

#include "random/mt-dsfmt/interface.h"
#include "vector/allocate.h" 

namespace mysimulator {

  template <unsigned int LFac>
  void allocate(MT_dSFMT<LFac>& G) {
    release(G);
    allocate(G.s,MT_dSFMT<LFac>::NStatus);
    G.idx=1;
    G.init(5489UL);
  }

}

#endif

