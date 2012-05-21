
#ifndef _Minimizer_Line_Tracking_Interface_H_
#define _Minimizer_Line_Tracking_Interface_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/interface.h"
#include "minimizer/line/condition/interface.h"
#include "array/1d/swap.h"

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
      ~LineMinimizer() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid();
      }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        static_cast<ParentType*>(this)->Load(S);
      }

      int Go(unsigned int MaxSteps=DefaultMaxSteps) {
        assert(IsValid());
        assert(this->Proj<=0);
        const T mstep=this->MinimalStep();
        T dstep=this->SearchScale;
        this->Step=dstep;
        T c1pj=this->DecreaseFac*this->Proj;
        T c2pj=this->CurvatureFac*this->Proj;
        unsigned int state=0;
        System<T,IDT,PT,GT,BT,SystemContentWithEGV> *TPSys;
        for(unsigned int nr=0;nr<MaxSteps;++nr) {
          BlasCopy(this->RunSys->Content.X,this->MemSys->Content.X);
          this->RunSys->StepEvolute();
          this->GCalcCount++;
          this->RunProj=
            BlasDot(this->RunSys->Content.EGData.Gradient,this->LineDirc);
          if(Condition<T,LMC>::Check(this->RunSys->Content.EGData.Energy[0],
                                     this->RunProj,
                                     this->MemSys->Content.EGData.Energy[0],
                                     c1pj,c2pj,this->Step)) {
            TPSys=this->MemSys; this->MemSys=this->RunSys; this->RunSys=TPSys;
            this->Proj=this->RunProj;
            this->Move=this->Step;
            state=1;
            break;
          }
          if(dstep*this->RunProj>0)   dstep*=-TrackingFac;
          this->Step+=dstep;
          if(absval(dstep)<mstep) { state=2; break; }
        }
        return state;
      }

  };

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,LineMinimizerConditionMethodName LMC>
  const unsigned int
  LineMinimizer<TrackingMethod,T,IDT,PT,GT,BT,CT,LMC>::DefaultMaxSteps=
      10000;

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT,LineMinimizerConditionMethodName LMC>
  void Clear(LineMinimizer<TrackingMethod,T,IDT,PT,GT,BT,CT,LMC>& M) {
    M.TrackingFac=GoldenValue<T>();
    typedef
    typename LineMinimizer<TrackingMethod,T,IDT,PT,GT,BT,CT,LMC>::ParentType
    Type;
    Clear(static_cast<Type&>(M));
  }

}

#endif

