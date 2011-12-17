
#ifndef _Minimizer_ConjugateGradient_Specification_H_
#define _Minimizer_ConjugateGradient_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  struct Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>
      : public LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM> {

    public:

      typedef Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>   Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM>   ParentType;

      static const unsigned int DefaultMaxSteps;

      VT<T> OldMinG;
      T MaxBeta;

      Minimizer() : ParentType(), OldMinG(), MaxBeta(0) {}
      ~Minimizer() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(OldMinG);
        MaxBeta=0;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(OldMinG)&&(MaxBeta>0.);
      }

      void SetMaxBeta() { copy(MaxBeta,5.); }
      template <typename T1>
      void SetMaxBeta(const T1& MB) { copy(MaxBeta,MB); }

      int Go(const unsigned int& MaxSteps=DefaultMaxSteps) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _load(*this);
        int fg=0, lfg;
        bool isSteep=true;
        bool nextMode;
        T beta=0;
        T fnorm,fnorm2;
        fnorm=norm(this->MemSys().Content().Gradient());
        if(fnorm<this->GradientThreshold) fg=3;
        else {
          fnorm2=fnorm*fnorm;
          T tmd,tmd2,oldfnorm2=1,dnorm=0;
          for(unsigned int ns=0;ns<MaxSteps;++ns) {
            if(!isSteep) {
              tmd=dot(this->MemSys().Content().Gradient(),OldMinG);
              beta=(fnorm2-tmd)/oldfnorm2;
              isSteep=(absval(beta)>MaxBeta);
            }
            if(!isSteep) {
              tmd=beta*dnorm;
              scale(this->LineDirc(),tmd);
              shift(this->LineDirc(),-cOne,
                    this->MemSys().Content().Gradient());
              this->Proj*=tmd;
              dnorm=sqroot(tmd*tmd+fnorm2-2*this->Proj);
              this->Proj-=fnorm2;
              this->Proj/=dnorm;
              isSteep=((this->Proj>0)||(dnorm<this->GradientThreshold));
            }
            if(isSteep) {
              if(fnorm<this->GradientThreshold) {
                fg=4;
                break;
              }
              copy(beta,cZero);
              dnorm=fnorm;
              copy(this->LineDirc(),
                  this->MemSys().Content().Gradient());
              scale(this->LineDirc(),-cOne);
              this->Proj=fnorm;
            }
            tmd=1./dnorm;
            scale(this->LineDirc(),tmd);
            copy(OldMinG,this->MemSys().Content().Gradient());
            tmd=this->MemSys().Content().Energy();
            lfg=static_cast<ParentType*>(this)->Go();
            this->LineSearchCount++;
            nextMode=false;
            if(lfg==2) {
              if(isSteep) {
                fg=1;
                break;
              } else {
                --ns;
                nextMode=true;
              }
            } else if(lfg==0) {
              fg=5;
              break;
            } else {
              tmd2=this->MemSys().Content().Energy();
              if(2*absval(tmd-tmd2)<absval(tmd+tmd2)*RelativeDelta<T>()) {
                if(isSteep) {
                  fg=2;
                  break;
                } else {
                  --ns;
                  nextMode=true;
                }
              }
            }
            isSteep=nextMode;
            oldfnorm2=fnorm2;
            fnorm=norm(this->MemSys().Content().Gradient());
            fnorm2=fnorm*fnorm;
          }
        }
        _write(*this);
        return fg;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  const unsigned int
  Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,VT,SCT,LCM>::DefaultMaxSteps=
      1000;

}

#endif

