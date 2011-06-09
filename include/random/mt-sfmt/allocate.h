
#ifndef _Random_MT_SFMT_Allocate_H_
#define _Random_MT_SFMT_Allocate_H_

#include "random/mt-sfmt/interface.h"

namespace mysimulator {

  template <unsigned int LFac>
  void allocate(MT_SFMT<LFac>& G) { G.init(5489U); }

  template <unsigned int LFac>
  void imprint(MT_SFMT<LFac>& G, const MT_SFMT<LFac>&) { allocate(G); }

}

#endif

