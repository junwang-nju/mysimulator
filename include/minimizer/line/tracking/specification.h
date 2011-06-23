
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

    static const unsigned int DefaultMaxIterations;

    T TrackingFac;

    LineMinimizer() : ParentType(), TrackingFac(GoldenValue<T>()) {}
    LineMinimizer(const Type&) { Error("Copier of LineMinimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizer Disabled!");
      return *this;
    }
    ~LineMinimizer() { clearData(); }

    void clearData() { static_cast<ParentType*>(this)->.clearData(); }

    virtual int Go(const unsigned int MaxIt=DefaultMaxIterations) {
      assert(IsValid(*this));
      assert(MinProject<=0);
      if(MinProject>=-GradThreshold)  return 2;
      const T mstep=MinimalStep();
      T dstep=SearchScale;
      T step=dstep;
      T c1pj=DecreaseFac*MinProject;
      T c2pj=CurvatureFac*MinProject;
      unsigned int state=0;
      for(unsigned int niter=0;niter<MaxIt;++niter) {
        ProduceNewPosition();
        /// add RunCondi, modify MinXRunX,MinG,RUnG as Object
        if(RunCondition(RunEnergy,RunProject,MinEnergy,c1pj,c2pj,step)) {
          swap(MinX,RunX);
          swap(MinG,RunG);
          MinEnergy=RunEnergy;
          MinProject=RunProject;
          MinMove=step;
          state=1;
        }
        if(dstep*RunProject>0)   dstep*=-TrackingFac;
        step+=dstep;
        if(absval(dstep)<mstep) { state=2; break; }
      }
      return state;
    }

  };

  template <typename FT,template<typename> class VT,typename PT,typename T>
  const unsigned int
  LineMinimizer<TrackingMethod,FT,VT,PT,T>::DefaultMaxIterations=10000;

  template <typename FT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizer<TrackingMethod,FT,VT,PT,T>& L) {
    typedef LineMinimizerCommon<FT,VT,PT,T>   Type;
    return IsValid(static_cast<const Type&>(L));
  }

  template <typename FT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizer<TrackingMethod,FT,VT,PT,T>& L) { L.clearData(); }

}

#endif

