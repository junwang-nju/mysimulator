
#ifndef _Random_MT_SFMT_Copy_H_
#define _Random_MT_SFMT_Copy_H_

#include "random/mt-sfmt/interface.h"
#include "unique-parameter/128bit/copy.h"

namespace mysimulator {

  template <unsigned int LFac>
  void copy(MT_SFMT<LFac>& G, const MT_SFMT<LFac>& cG) {
    assert(IsValid(G)&&IsValid(cG));
    copy(G.s,cG.s);
    copy(G.idx,cG.idx);
  }

}

#endif

