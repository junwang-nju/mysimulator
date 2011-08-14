
#ifndef _Minimizer_Line_Allocate_H_
#define _Minimizer_Line_Allocate_H_

#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMName, typename T,typename FT,typename IDT,
            typename PT,typename GT, template<typename> class ST>
  void allocate(LineMinimizer<LMName,T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    Error("Allocation of This type of LineMinimizer Disabled!");
  }

}

#include "minimizer/line/tracking/allocate-specification.h"

#endif

