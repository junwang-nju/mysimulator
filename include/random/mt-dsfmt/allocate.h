
#ifndef _Random_MT_DSFMT_Allocate_H_
#define _Random_MT_DSFMT_Allocate_H_

#include "random/mt-dsfmt/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  void allocate(MT_dSFMT<LFac>& G) { G.init(5489UL); }

  template <unsigned int LFac>
  void imprint(MT_dSFMT<LFac>& G, const MT_dSFMT<LFac>&) { allocate(G); } 

}

#endif

