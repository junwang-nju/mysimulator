
#ifndef _Interaction_Parameter_Unit_Allocate_H_
#define _Interaction_Parameter_Unit_Allocate_H_

#include "interaction/parameter/unit/interface.h"
#include "interaction/func/component/list.h"
#include "interaction/func/component/method/index-size.h"
#include "interaction/parameter/size.h"
#include "vector/allocate.h"
#include <cstdarg>

namespace mysimulator {

  void allocate(InteractionParameterUnit& P,
                const InteractionFunctionName& itag, ...) {
    release(P);
    P.tag=itag;
    int idsize=InteractionMethodIdxSize[MethodMap[itag]];
    if(idsize>0) {
      allocate(P.idx,idsize);
    }
    unsigned int pmsize=InteractionParameterSize[itag];
    allocate(P.prm,pmsize);
  }

  void imprint(InteractionParameterUnit& P,const InteractionParameterUnit& cP) {
    allocate(P,cP.tag);
  }

}

#endif

