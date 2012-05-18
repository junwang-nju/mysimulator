
#ifndef _Minimizer_Line_Tracking_Interface_H_
#define _Minimizer_Line_Tracking_Interface_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/interface.h"
#include "minimizer/line/condition/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,LineMinimizerConditionMethodName LMC>
  struct LineMinimizer<TrackingMethod,T,IDT,PT,GT,BT,CT,LMC>
      : public LineMinimizerCommon<T,IDT,PT,GT,BT,CT> {

    public:

      typedef LineMinimizer<TrackingMethod,T,IDT,PT,GT,BT,CT,LMC>   Type;
      typedef LineMinimizerCommon<T,IDT,PT,GT,BT,CT>  ParentType;

      static const unsigned int DefaultMaxSteps;

      T TrackingFac;

      LineMinimizer() : ParentType(), TrackingFac(GoldenValue<T>()) {}

  };

}

#endif

