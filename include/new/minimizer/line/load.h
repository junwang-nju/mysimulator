
#ifndef _Minimizer_Line_Load_H_
#define _Minimizer_Line_Load_H_

#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    Error("This kind of LineMinimizer Cannot be loaded!");
  }

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    Error("This kind of LineMinimizer Cannot be loaded!");
  }

}

#include "minimizer/line/tracking/load-specification.h"

#endif

