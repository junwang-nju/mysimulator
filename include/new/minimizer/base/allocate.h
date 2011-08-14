
#ifndef _Minimizer_Base_Allocate_H_
#define _Minimizer_Base_Allocate_H_

#include "minimizer/base/interface.h"
#include "object/refer.h"

namespace mysimulator {

  template <typename T, typename FT, typename IDT, typename PT, typename GT,
            template <typename> class ST>
  void allocate(MinimizerBase<T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    assert(IsValid(S));
    release(M);
    refer(M.Sys,S);
  }

}

#endif

