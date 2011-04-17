
#ifndef _Random_MT_Standard_Allocate_H_
#define _Random_MT_Standard_Allocate_H_

#include "random/mt-standard/interface.h"

namespace mysimulator {

  void allocate(MT_Standard& G) { G.init(5489UL); }

  void imprint(MT_Standard& G, const MT_Standard& cG) { allocate(G);  }

}

#endif

