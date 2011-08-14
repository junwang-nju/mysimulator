
#ifndef _System_Copy_H_
#define _System_Copy_H_

#include "system/interface.h"

namespace mysimulator {

  template <typename T, typename FT, typename IDT, typename PT, typename GT,
            template <typename> class ST>
  void copy(System<T,FT,IDT,PT,GT,ST>& S, const System<T,FT,IDT,PT,GT,ST>& cS) {
    assert(IsValid(S)&&IsValid(cS));
    copy(S.Func,cS.Func);
    copy(S.ID,cS.ID);
    copy(S.Param,cS.Param);
    copy(S.Geom,cS.Geom);
    copy(S.X,cS.X);
    copy(S.G,cS.G);
    copy(S.Mask,cS.Mask);
    copy(S.UMask,cS.UMask);
    copy(S.Energy,cS.Energy);
  }

}

#endif

