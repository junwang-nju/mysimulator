
#ifndef _Minimizer_Copy_H_
#define _Minimizer_Copy_H_

#include "minimizer/interface.h"

namespace mysimulator {

  template <MinimizerName MN, LineMinimizerName LMN, typename KT,
            template<typename> class VT, typename PT, typename T>
  void copy(Minimizer<MN,LMN,KT,VT,PT,T>& M,
            const Minimizer<MN,LMN,KT,VT,PT,T>& cM) {
    Error("Operation Copy for this Object Disabled!");
  }

}

#include "minimizer/steep/copy-specification.h"

#endif

