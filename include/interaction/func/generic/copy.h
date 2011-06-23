
#ifndef _Interaction_Function_Generic_Copy_H_
#define _Interaction_Function_Generic_Copy_H_

#include "interaction/func/generic/interface.h"
#include "list/allocate.h"

namespace mysimulator {

  template <template<typename> class DBuffer,typename GeomType,typename T>
  void copy(InteractionFuncGeneric<DBuffer,GeomType,T>& G,
            const InteractionFuncGeneric<DBuffer,GeomType,T>& cG) {
    assert(IsValid(cG));
    G.tag=cG.tag;
    G.EFunc=cG.EFunc;
    G.GFunc=cG.GFunc;
    G.BFunc=cG.BFunc;
    if(IsValid(cG.tmvec))  imprint(G.tmvec,cG.tmvec);
  }

}

#endif

