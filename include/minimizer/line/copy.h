
#ifndef _Minimizer_Line_Copy_H_
#define _Minimizer_Line_Copy_H_

#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LN,typename FT,template<typename> class VT,
            typename PT, typename T>
  void copy(LineMinimizer<LN,FT,VT,PT,T>& L,
            const LineMinimizer<LN,FT,VT,PT,T>& cL) {
    assert(IsValid(L)&&IsValid(cL));
  }

}

#endif

