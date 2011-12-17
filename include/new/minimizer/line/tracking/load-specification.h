
#ifndef _Minimizer_Line_Tracking_Load_Specification_H_
#define _Minimizer_Line_Tracking_Load_Specification_H_

#include "minimizer/line/load.h"
#include "minimizer/line/common/load.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(LineMinimizer<TrackingMethod,T,IDT,PT,GT,VT,SCT,LCM>& M,
            System<T,IDT,PT,GT,VT,SCT>& S) {
    typedef
    typename LineMinimizer<TrackingMethod,T,IDT,PT,GT,VT,SCT,LCM>::ParentType
    Type;
    load(static_cast<Type&>(M),S);
  }

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  void load(LineMinimizer<TrackingMethod,T,IDT,PT,GT,VT,SCT,LCM>& M,
            Object<System<T,IDT,PT,GT,VT,SCT> >& S) {
    assert(IsValid(S));
    load(M,S());
  }

}

#endif

