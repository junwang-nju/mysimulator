
#ifndef _Random_MT_DSFMT_Copy_H_
#define _Random_MT_DSFMT_Copy_H_

#include "random/mt-dsfmt/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  void copy(MT_dSFMT<LFac>& G, const MT_dSFMT<LFac>& cG) {
    assert(IsValid(G)&&IsValid(cG));
    for(unsigned int i=0;i<MT_dSFMT<LFac>::NStatus;++i)
      copy(G.s[i],cG.s[i]);
    copy(G.idx,cG.idx);
  }

}

#endif

