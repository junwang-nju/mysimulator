
#ifndef _Minimizer_Steep_Load_Specification_H_
#define _Minimizer_Steep_Load_Specification_H_

#include "minimizer/steep/specification.h"
#include "minimizer/line/load.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    typedef
    typename Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>::ParentType
    Type;
    load(static_cast<Type&>(M),S);
  }

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    assert(IsValid(S));
    load(M,S());
  }

}

#endif

