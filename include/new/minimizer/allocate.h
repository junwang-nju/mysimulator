
#ifndef _Minimizer_Allocate_H_
#define _Minimizer_Allocate_H_

#include "minimizer/interface.h"

namespace mysimulator {

  template <MinimizerName MN, LineMinimizerName LMN, typename T,typename FT,
            typename IDT,typename PT,typename GT,template<typename> class ST>
  void allocate(Minimizer<MN,LMN,T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    Error("Unknown Minimizer Type!");
  }

}

#include "minimizer/steep/allocate-specification.h"

#endif

