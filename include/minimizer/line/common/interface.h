
#ifndef _Minimizer_Line_Common_Interface_H_
#define _Minimizer_Line_Common_Interface_H_

#include "minimizer/base/interface.h"
#include "intrinsic-type/constant.h"

namespace mysimulator {

  template <typename IFuncType,template<typename> class SpaceVType,
            typename IParamType,typename T>
  struct LineMinimizerCommon
      : public MinimizerBase<IFuncType,SpaceVType,IParamType,T> {

    typedef LineMinimizerCommon<IFuncType,SpaceVType,IParamType,T>   Type;
    typedef MinimizerBase<IFuncType,SpaceVType,IParamType,T>    ParentType;

    SpaceVType<T>   RunX;
    SpaceVType<T>   RunG;
    unsigned int    LineSearchCount;
    T               RunEnergy;
    T               RunProject;
    T               DecreaseFac;
    T               CurvatureFac;
    T               GradThreshold;

    LineMinimizerCommon()
        : ParentType(), RunX(), RunG(), LineSearchCount(0), RunEnergy(0.),
          RunProject(0.), DecreaseFac(1e-4), CurvatureFac(0.4),
          GradThreshold(RelativeDelta<T>()) {}
    LineMinimizerCommon(const Type&) {
      Error("Copier of LineMinimizerCommon Disabled!");
    }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizerCommon Disabled!");
      return *this;
    }
    ~LineMinimizerCommon() { clearData(); }

    void clearData() {
      release(RunX); release(RunG);
      static_cast<ParentType*>(this)->clearData();
    }

  };

  template <typename FT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizerCommon<FT,VT,PT,T>& L) {
    typedef MinimizerBase<FT,VT,PT,T>    Type;
    return IsValid(static_cast<const Type&>(L))&&
           IsValid(L.RunX)&&IsValid(L.RunG);
  }

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizerCommon<FT,VT,PT,T>& L) { L.clearData(); }

}

#endif

