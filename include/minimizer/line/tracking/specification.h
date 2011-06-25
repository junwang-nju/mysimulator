
#ifndef _Minimizer_Line_Tracking_Specification_H_
#define _Minimizer_Line_Tracking_Specification_H_

#include "minimizer/line/interface.h"
#include "minimizer/base/produce.h"
#include "minimizer/line/common/interface.h"
#include "minimizer/line/condition/name.h"
#include "minimizer/line/condition/evaluate.h"
#include "referable-object/swap.h"

namespace mysimulator {

  template <typename IKernelType,template<typename> class SpaceVType,
            typename IParamType,typename T>
  struct LineMinimizer<TrackingMethod,IKernelType,SpaceVType,IParamType,T>
      : public LineMinimizerCommon<IKernelType,SpaceVType,IParamType,T> {

    typedef LineMinimizer<TrackingMethod,IKernelType,SpaceVType,IParamType,T>
            Type;
    typedef LineMinimizerCommon<IKernelType,SpaceVType,IParamType,T>
            ParentType;
    typedef MinimizerBase<IKernelType,SpaceVType,IParamType,T> BaseType;
    typedef bool (*ConditionFuncType)(const T&,const T&,const T&,const T&,
                                      const T&,const T&);

    static const unsigned int DefaultMaxIterations;

    T TrackingFac;
    ConditionFuncType Condition;

    LineMinimizer()
        : ParentType(), TrackingFac(GoldenValue<T>()), Condition(NULL) {}
    LineMinimizer(const Type&) { Error("Copier of LineMinimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for LineMinimizer Disabled!");
      return *this;
    }
    ~LineMinimizer() { clearData(); }

    void clearData() {
      static_cast<ParentType*>(this)->clearData();
      Condition=NULL;
    }

    int _Go(const unsigned int MaxIt=DefaultMaxIterations) {
      assert(IsValid(*this));
      assert(this->MinProject<=0);
      if(this->MinProject>=-this->GradThreshold)  return 2;
      const T mstep=this->MinimalStep();
      T dstep=this->SearchScale;
      T step=dstep;
      T c1pj=this->DecreaseFac*this->MinProject;
      T c2pj=this->CurvatureFac*this->MinProject;
      unsigned int state=0;
      for(unsigned int niter=0;niter<MaxIt;++niter) {
        ProduceNew(static_cast<BaseType&>(*this),this->MinX(),this->LineDirc,
                   step,this->RunX(),this->RunEnergy,this->RunG(),
                   this->RunProject);
        if(Condition(this->RunEnergy,this->RunProject,this->MinEnergy,
                     c1pj,c2pj,step)) {
          swap(this->MinX,this->RunX);
          swap(this->MinG,this->RunG);
          this->MinEnergy=this->RunEnergy;
          this->MinProject=this->RunProject;
          this->MinMove=step;
          state=1;
          break;
        }
        if(dstep*this->RunProject>0)   dstep*=-TrackingFac;
        step+=dstep;
        if(absval(dstep)<mstep) { state=2; break; }
      }
      return state;
    }

    virtual int Go(const unsigned int MaxIt) { return _Go(MaxIt); }

    void SetCondition(const LineMinimizerConditionName& CName) {
      switch(CName) {
        case Armijo:  Condition=ArmijoCondition<T>; break;
        case Wolfe:   Condition=WolfeCondition<T>;  break;
        case StrongWolfe: Condition=StrongWolfeCondition<T>;  break;
        default:  Error("Unknow Name for Line search Condition!");
      }
    }

  };

  template <typename KT,template<typename> class VT,typename PT,typename T>
  const unsigned int
  LineMinimizer<TrackingMethod,KT,VT,PT,T>::DefaultMaxIterations=10000;

  template <typename KT,template<typename> class VT,typename PT,typename T>
  bool IsValid(const LineMinimizer<TrackingMethod,KT,VT,PT,T>& L) {
    typedef LineMinimizerCommon<KT,VT,PT,T>   Type;
    return IsValid(static_cast<const Type&>(L))&&IsValid(L.Condition);
  }

  template <typename KT,template<typename> class VT,typename PT,typename T>
  void release(LineMinimizer<TrackingMethod,KT,VT,PT,T>& L) { L.clearData(); }

}

#endif

