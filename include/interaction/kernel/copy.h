
#ifndef _Interaction_Kernel_Copy_H_
#define _Interaction_Kernel_Copy_H_

#include "interaction/kernel/interface.h"
#include "interaction/geometry/copy.h"

namespace mysimulator {

  template <typename IT,template<typename> class DB,typename GT,typename T>
  void copy(InteractionKernel<IT,DB,GT,T>& K,
            const InteractionKernel<IT,DB,GT,T>& cK) {
    assert(IsValid(K)&&IsValid(cK));
    copy(K.IF,cK.IF);
    copy(K.IG,cK.IG);
  }

}

#endif

