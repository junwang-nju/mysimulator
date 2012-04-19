
#ifndef _Interaction_Func_Imprint_H_
#define _Interaction_Func_Imprint_H_

#include "interaction/func/allocate.h"

namespace mysimulator {

  template <typename GT,typename T>
  void imprint(InteractionFunc<GT,T>& F, const InteractionFunc<GT,T>& iF) {
    allocate(F,iF.tag);
  }

}

#endif

