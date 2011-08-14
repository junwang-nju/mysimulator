
#ifndef _Interaction_Func_Copy_H_
#define _Interaction_Func_Copy_H_

#include "interaction/func/allocate.h"
#include "array/2d/copy.h"

namespace mysimulator {

  template <typename GeomType, typename T>
  void copy(InteractionFunc<GeomType,T>& F,
            const InteractionFunc<GeomType,T>& cF) {
    imprint(F,cF);
    copy(F.tmvec,cF.tmvec);
  }

}

#endif

