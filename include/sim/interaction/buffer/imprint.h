
#ifndef _Interaction_Buffer_Imprint_H_
#define _Interaction_Buffer_Imprint_H_

#include "interaction/buffer/allocate.h"

namespace mysimulator {

  template <typename T>
  void imprint(InteractionBuffer<T>& B, const InteractionBuffer<T>& iB) {
    allocate(B,iB.tag,iB.dim);
  }

}

#endif

