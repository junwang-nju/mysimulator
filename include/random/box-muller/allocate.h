
#ifndef _Random_Box_Muller_Allocate_H_
#define _Random_Box_Muller_Allocate_H_

#include "random/box-muller/interface.h"

namespace mysimulator {

  template <typename UniformRNG>
  void allocate(BoxMuller<UniformRNG>& G) {
    release(G);
    allocate(G.urng);
    G.isSecond=true;
  }

  template <typename UniformRNG>
  void imprint(BoxMuller<UniformRNG>& G, const BoxMuller<UniformRNG>&) {
    allocate(G);
  }

}

#endif

