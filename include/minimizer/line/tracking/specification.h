
#ifndef _Minimizer_Line_Tracking_Specification_H_
#define _Minimizer_Line_Tracking_Specification_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/interface.h"

namespace mysimulator {

  template <typename IFuncType,template<typename> class SpaceVType,
            typename IParamType,typename T>
  struct LineMinimizer<TrackingMethod,IFuncType,SpaceVType,IParamType,T>
      : public LineMinimizerCommon<IFuncType,SpaceVType,IParamType,T> {

    typedef LineMinimizer<TrackingMethod,IFuncType,SpaceVType,IParamType,T>
            Type;
    typedef LineMinimizerCommon<IFuncType,SpaceVType,IParamType,T>
            ParentType;

    T TrackingFac;

    LineMinimizer() : ParentType(), TrackingFac(GoldenValue<T>()) {}
    LineMinimizer(const Type&) { Error("Copier of LineMinimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizer Disabled!");
      return *this;
    }
    ~LineMinimizer() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->.clearData(); }

  };

  template <typename FT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizer<TrackingMethod,FT,VT,PT,T>& L) {
    typedef LineMinimizerCommon<FT,VT,PT,T>   Type;
    return IsValid(static_cast<const Type&>(L));
  }

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizer<TrackingMethod,FT,VT,PT,T>& L) { L.clearData(); }

}

#endif

