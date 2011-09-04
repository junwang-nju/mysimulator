
#ifndef _Minimizer_Line_Tracking_Specification_H_
#define _Minimizer_Line_Tracking_Specification_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/interface.h"
#include "minimizer/line/condition/interface.h"
#include "object/copy.h"
#include "object/swap.h"

namespace mysimulator {

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template<typename> class ST>
  struct LineMinimizer<TrackingMethod,T,FT,IDT,PT,GT,ST>
    : public LineMinimizerCommon<T,FT,IDT,PT,GT,ST> {

    public:

      typedef LineMinimizer<TrackingMethod,T,FT,IDT,PT,GT,ST> Type;
      typedef LineMinimizerCommon<T,FT,IDT,PT,GT,ST>  ParentType;
      typedef bool (*ConditionFuncType)(const T&,const T&,const T&,const T&,
                                        const T&,const T&);

      static const unsigned int DefaultMaxIterations;

      T TrackingFac;
      ConditionFuncType CondFunc;

      LineMinimizer() : ParentType(), TrackingFac(ValueGolden<T>()),
                        CondFunc(NULL) {}
      ~LineMinimizer() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        TrackingFac=ValueGolden<T>();
        CondFunc=NULL;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (CondFunc!=NULL);
      }

      void SetCondition(const LineMinimizerConditionName& LMCName) {
        switch(LMCName) {
          case Armijo: CondFunc=Condition<T,Armijo>::Check; break;
          case Wolfe: CondFunc=Condition<T,Wolfe>::Check; break;
          case StrongWolfe: CondFunc=Condition<T,StrongWolfe>::Check; break;
          default: Error("Unknown Condition Type!");
        }
      }

      int _Go(const unsigned int& MaxIt=DefaultMaxIterations) {
        assert(isvalid());
        assert(this->Proj<=0);
        if(this->Proj>=-this->GradThreshold)  return 2;
        const T mstep=this->MinimalStep();
        T dstep=this->SearchScale;
        T step=dstep;
        T c1pj=this->DecFac*this->Proj;
        T c2pj=this->CurvFac*this->Proj;
        unsigned int state=0;
        for(unsigned int nite=0;nite<MaxIt;++nite) {
          copy(this->RunX,this->Sys().X);
          shift(this->RunX(),step,this->LineDirc);
          this->RunEnergy=0.;
          fill(this->RunG,cZero);
          Calc(this->Sys().Func,this->RunX(),this->Sys().ID,this->Sys().Param,
               this->Sys().Geom,this->RunEnergy,this->RunG());
          this->RunProj=dot(this->RunG(),this->LineDirc);
          this->GCalcCount++;
          if(CondFunc(this->RunEnergy,this->RunProj,this->Sys().Energy,
                      c1pj,c2pj,step)) {
            Swap(this->Sys().X,this->RunX);
            Swap(this->Sys().G,this->RunG);
            this->Sys().Energy=this->RunEnergy;
            this->Proj=this->RunProj;
            this->Move=step;
            state=1;
            break;
          }
          if(dstep*this->RunProj>0) dstep*=-TrackingFac;
          step+=dstep;
          if(absval(dstep)<mstep) { state=2; break; }
        }
        return state;
      }

      virtual int Go(const unsigned int MaxIt=DefaultMaxIterations) {
        return _Go(MaxIt);
      }

    private:

      LineMinimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template<typename> class ST>
  const unsigned int
  LineMinimizer<TrackingMethod,T,FT,IDT,PT,GT,ST>::DefaultMaxIterations=10000;

}

#endif

