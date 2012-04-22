
#ifndef _Interaction_Func_Copy_H_
#define _Interaction_Func_Copy_H_

#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename GT,typename T>
  void Copy(InteractionFunc<GT,T>& F,const InteractionFunc<GT,T>& iF) {
    assert(F.tag==iF.tag);
  }

}

#endif

