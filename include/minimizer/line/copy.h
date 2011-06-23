
#ifndef _Minimizer_Line_Copy_H_
#define _Minimizer_Line_Copy_H_

#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LN,typename KT,template<typename> class VT,
            typename PT, typename T>
  void copy(LineMinimizer<LN,KT,VT,PT,T>& L,
            const LineMinimizer<LN,KT,VT,PT,T>& cL) {
    Error("Operation Copy for this Object Disabled!");
  }

}

#include "minimizer/line/tracking/copy-specification.h"

#endif

