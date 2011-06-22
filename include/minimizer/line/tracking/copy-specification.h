
#ifndef _Minimizer_Line_Tracking_Copy_Specification_H_
#define _Minimizer_Line_Tracking_Copy_Specification_H_

#include "minimizer/line/tracking/specification.h"
#include "minimizer/line/common/copy.h"
#include "intrinsic-type/copy.h"

namespace mysimulator {

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void copy(LineMinimizer<TrackingMethod,FT,VT,PT,T>& L,
            const LineMinimizer<TrackingMethod,FT,VT,PT,T>& cL) {
    typedef LineMinimizerCommon<FT,VT,PT,T> Type;
    copy(static_cast<Type&>(L),static_cast<const Type&>(cL));
    copy(L.TrackingFac,cL.TrackingFac);
  }

}

#endif

