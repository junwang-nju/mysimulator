
#ifndef _Minimizer_Load_H_
#define _Minimizer_Load_H_

#include "minimizer/interface.h"

namespace mysimulator {

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<MN,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    Error("This Minimizer Cannot be Loaded!");
  }

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN,
            typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<MN,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    Error("This Minimizer Cannot be Loaded!");
  }

}

#include "minimizer/steep/load-specification.h"
#include "minimizer/conjg/load-specification.h"
#include "minimizer/lbfgs/load-specification.h"

#endif

