
#ifndef _Random_Box_Muller_Copy_H_
#define _Random_Box_Muller_Copy_H_

#include "random/box-muller/interface.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename UniformRNG>
  void copy(BoxMuller<UniformRNG>& G, const BoxMuller<UniformRNG>& cG) {
    assert(IsValid(G)&&IsValid(cG));
    copy(G.urng,cG.urng);
    copy(G.isSecond,cG.isSecond);
    for(unsigned int i=0;i<3;++i) copy(G.s[i],cG.s[i]);
  }

}

#endif

