
#ifndef _Random_MT_DSFMT_Copy_H_
#define _Random_MT_DSFMT_Copy_H_

#include "random/mt-dsfmt/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  void copy(MT_dSFMT<LFac>& G, const MT_dSFMT<LFac>& cG) {
    assert(IsValid(G)&&IsValid(cG));
    copy(G.s,cG.s);
    copy(G.idx,cG.idx);
  }

}

#endif

