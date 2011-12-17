
#ifndef _Minimizer_Regular_Load_H_
#define _Minimizer_Regular_Load_H_

#include "minimizer/regular/interface.h"
#include "minimizer/load.h"

namespace mysimulator {

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN, typename T,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename> class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>& M,
            System<T,IDT,PT,GT,Array2D,SCT>& S) {
    typedef typename MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>::ParentType
            Type;
    load(static_cast<Type&>(M),S);
  }

  template <MinimizerMethodName MN, LineMinimizerMethodName LMN, typename T,
            typename IDT,typename PT,typename GT,
            template<typename,template<typename> class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(MinimizerRegular<MN,LMN,T,IDT,PT,GT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,Array2D,SCT> >& S) {
    assert(IsValid(S));
    load(M,S());
  }

}

#endif

