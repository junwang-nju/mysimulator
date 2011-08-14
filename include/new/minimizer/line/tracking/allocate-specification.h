
#ifndef _Minimizer_Line_Tracking_Allocate_Specification_H_
#define _Minimizer_Line_Tracking_Allocate_Specification_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/allocate.h"

namespace mysimulator {

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template <typename> class ST>
  void allocate(LineMinimizer<TrackingMethod,T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    typedef
    typename LineMinimizer<TrackingMethod,T,FT,IDT,PT,GT,ST>::ParentType Type;
    allocate(static_cast<Type&>(M),S);
  }

}

#endif

