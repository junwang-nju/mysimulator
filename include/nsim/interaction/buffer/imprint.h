
#ifndef _Interaction_Buffer_Imprint_H_
#define _Interaction_Buffer_Imprint_H_

#include "interaction/buffer/interface.h"

namespace mysimulator {

  template <typename T>
  void Imprint(InteractionBuffer<T>& B,const InteractionBuffer<T>& iB) {
    B.Allocate(iB.tag,iB.dim);
  }

}

#endif

