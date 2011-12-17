
#ifndef _Minimizer_Line_Tracking_Specification_H_
#define _Minimizer_Line_Tracking_Specification_H_

#include "minimizer/line/interface.h"
#include "minimizer/line/common/interface.h"
#include "minimizer/line/condition/interface.h"
#include "system/sync.h"
#include "object/swap.h"

namespace mysimulator {

  template <typename T,typename IDType,typename ParamType,typename GeomType,
            template<typename> class VecType,
            template<typename,template<typename>class> class SysContentType,
            LineMinimizerConditionMethodName LCM>
  struct
  LineMinimizer<TrackingMethod,T,IDType,ParamType,GeomType,VecType,
                SysContentType,LCM>
      : public 
        LineMinimizerCommon<T,IDType,ParamType,GeomType,VecType,SysContentType>{

    public:

      typedef
      LineMinimizer<TrackingMethod,T,IDType,ParamType,GeomType,VecType,
                    SysContentType,LCM>
      Type;
      typedef
      LineMinimizerCommon<T,IDType,ParamType,GeomType,VecType,SysContentType>
      ParentType;

      static const unsigned int DefaultMaxSteps;

      T TrackingFac;

      LineMinimizer() : ParentType(), TrackingFac(ValueGolden<T>()) {}
      ~LineMinimizer() { clearData(); }

      void clearData() {
        copy(TrackingFac,ValueGolden<T>());
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid();
      }

      int Go(const unsigned int& MaxSteps=DefaultMaxSteps) {
        assert(isvalid());
        assert(this->Proj<=0);
        const T mstep=this->MininalStep();
        T dstep=this->SearchScale;
        this->Step=dstep;
        T c1pj=this->DecreaseFac*this->Proj;
        T c2pj=this->CurvatureFac*this->Proj;
        unsigned int state=0;
        for(unsigned int nit=0;nit<MaxSteps;++nit) {
          copy(this->RunSys().Content().X(),this->MemSys().Content().X());
          this->RunSys().evolute();
          sync(this->RunSys().Content(),this->RunSys().Interaction());
          this->GCalcCount++;
          this->RunProj=dot(this->RunSys().Content().Gradient(),
                            this->LineDirc());
          if(Condition<T,LCM>::Check(this->RunSys().Content().Energy(),
                                     this->RunProj,
                                     this->MemSys().Content().Energy(),
                                     c1pj,c2pj,this->Step)) {
            Swap(this->RunSys,this->MemSys);
            this->Proj=this->RunProj;
            this->Move=this->Step;
            state=1;
            break;
          }
          if(dstep*this->RunProj>0) dstep*=-TrackingFac;
          this->Step+=dstep;
          if(absval(dstep)<mstep) { state=2; break; }
        }
        return state;
      }

  };

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  const unsigned int
  LineMinimizer<TrackingMethod,T,IDT,PT,GT,VT,SCT,LCM>::DefaultMaxSteps=
      10000;

}

#endif

