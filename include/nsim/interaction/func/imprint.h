
#ifndef _Interaction_Func_Imprint_H_
#define _Interaction_Func_Imprint_H_

#include "interaction/func/interface.h"

namespace mysimulator {

  template <typename GT,typename T>
  void Imprint(InteractionFunc<GT,T>& F,const InteractionFunc<GT,T>& iF) {
    F.Allocate(iF.tag);
  }

}

#endif

