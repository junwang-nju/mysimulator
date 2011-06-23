
#ifndef _Interaction_Parameter_Unit_Copy_H_
#define _Interaction_Parameter_Unit_Copy_H_

#include "interaction/parameter/unit/interface.h"
#include "unique-parameter/64bit/copy.h"
#include "vector/copy.h"

namespace mysimulator {

  void copy(InteractionParameterUnit& P, const InteractionParameterUnit& cP) {
    assert(IsValid(P)&&IsValid(cP));
    assert(P.tag==cP.tag);
    copy(P.prm,cP.prm);
    copy(P.idx,cP.idx);
  }

}

#endif

