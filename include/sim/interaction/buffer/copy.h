
#ifndef _Interaction_Buffer_Copy_H_
#define _Interaction_Buffer_Copy_H_

#include "interaction/buffer/interface.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename T>
  void Copy(InteractionBuffer<T>& B,const InteractionBuffer<T>& iB) {
    assert((B.tag==iB.tag)&&(B.dim==iB.dim));
    Copy(B.pre,iB.post);
    Copy(B.post,iB.post);
    Copy(B.tmvec,iB.tmvec);
    B.postUpdate=iB.postUpdate;
  }

}

#endif

