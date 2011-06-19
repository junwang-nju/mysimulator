
#ifndef _Interaction_Kernel_Unit_Copy_H_
#define _Interaction_Kernel_Unit_Copy_H_

#include "interaction/kernel/unit/interface.h"
#include "vector/allocate.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  void copy(InteractionKernelUnit<DBuffer,GeomType,T>& KU,
            const InteractionKernelUnit<DBuffer,GeomType,T>& cKU) {
    assert(IsValid(cKU));
    KU.tag=cKU.tag;
    KU.EFunc=cKU.EFunc;
    KU.GFunc=cKU.BFunc;
    KU.BFunc=cKU.BFunc;
    if(IsValid(cKU.tmvec))  imprint(KU.tmvec,cKU.tmvec);
  }

}

#endif

