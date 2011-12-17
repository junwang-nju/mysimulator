
#ifndef _Minimizer_Steep_Specification_H_
#define _Minimizer_Steep_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  struct Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>
      : public LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM> {

    public:

      typedef Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>   Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM> ParentType;

      static const unsigned int DefaultMaxSteps;

      Minimizer() : ParentType() {}
      ~Minimizer() { clearData(); }

      void clearData() { static_cast<ParentType*>(this)->clearData(); }
      bool isvalid() const { return static_cast<ParentType*>(this)->isvalid(); }

      int Go(const unsigned int& MaxSteps=DefaultMaxSteps) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _load(*this);
        T tmd,tmd2;
        int fg=0, lfg;
        for(unsigned int ns=0;ns<MaxSteps;++ns) {
          copy(this->LineDirc(),this->MemSys().Content().Gradient());
          tmd=norm(this->LineDirc());
          if(tmd<this->GradientThreshold) {
            fg=3;
            break;
          }
          scale(this->LineDirc(),-1./tmd);
          this->Proj=-tmd;
          tmd=this->MemSys().Content().Energy();
          lfg=static_cast<ParentType*>(this)->Go();
          this->LineSearchCount++;
          if(lfg==2) {
            fg=1;
            break;
          } else if(lfg==0) {
            fg=4;
            break;
          } else {
            tmd2=this->MemSys().Content().Energy();
            if(2*absval(tmd-tmd2)<=absval(tmd+tmd2)*RelativeDelta<T>()) {
              fg=2;
              break;
            }
          }
        }
        _write(*this);
        return fg;
      }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  const unsigned int
  Minimizer<SteepestDescent,LMN,T,IDT,PT,GT,VT,SCT,LCM>::DefaultMaxSteps=
      10000;

}

#endif

