
#ifndef _Minimizer_ConjugateGradient_Interface_H_
#define _Minimizer_ConjugateGradient_Interface_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  struct Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>
      : public LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC> {

    public:

      typedef Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>  Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,BT,CT,LMC>  ParentType;

      static const unsigned int DefaultMaxSteps;

      Array2D<T> OldMinG;
      T MaxBeta;

      Minimizer() : ParentType(), OldMinG(), MaxBeta(0) {}
      ~Minimizer() { Clear(*this); }

      bool IsValid() const {
        return static_cast<const ParentType*>(this)->IsValid()&&
               OldMinG.IsValid();
      }

      void Load(System<T,IDT,PT,GT,BT,CT>& S) {
        static_cast<ParentType*>(this)->Load(S);
        Imprint(OldMinG,S.Content.X);
        if(MaxBeta<RelDelta<T>()) SetMaxBeta();
      }

      void SetMaxBeta() { MaxBeta=5.; }
      template <typename T1> void SetMaxBeta(const T1& B) { MaxBeta=B; }

      int Go(unsigned int MaxSteps=DefaultMaxSteps) {
        assert(IsValid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _Load2Mem(*this);
        int fg=0, lfg;
        bool isSteep=true, nextMode;;
        T beta=0;
        T fnorm,fnorm2;
        fnorm=BlasNorm(this->MemSys->Content.EGData.Gradient);
        if(fnorm<this->GradThreshold)   fg=3;
        else {
          fnorm2=fnorm*fnorm;
          T tmd,tmd2,oldfnorm2=1.,dnorm=0;
          for(unsigned int nr=0;nr<MaxSteps;++nr) {
            if(!isSteep) {
              tmd=BlasDot(this->MemSys->Content.EGData.Gradient,OldMinG);
              beta=(fnorm2-tmd)/oldfnorm2;
              isSteep=(absval(beta)>MaxBeta);
            }
            if(!isSteep) {
              tmd=beta*dnorm;
              BlasScale(this->LineDirc,tmd);
              BlasShift(this->LineDirc,
                        -1.,this->MemSys->Content.EGData.Gradient);
              this->Proj*=tmd;
              dnorm=Sqroot(tmd*tmd+fnorm2-2*this->Proj);
              this->Proj-=fnorm2;
              this->Proj/=dnorm;
              isSteep=((this->Proj>0)||(dnorm<this->GradThreshold));
            }
            if(isSteep) {
              if(fnorm<this->GradThreshold) { fg=4; break; }
              beta=0.;
              dnorm=fnorm;
              BlasCopy(this->LineDirc,this->MemSys->Content.EGData.Gradient);
              BlasScale(this->LineDirc,-1.);
              this->Proj=-fnorm;
            }
            tmd=1./dnorm;
            BlasScale(this->LineDirc,tmd);
            BlasCopy(OldMinG,this->MemSys->Content.EGData.Gradient);
            tmd=this->MemSys->Content.EGData.Energy[0];
            lfg=static_cast<ParentType*>(this)->Go();
            this->LineSearchCount++;
            nextMode=false;
            if(lfg==2) {
              if(isSteep) { fg=1; break; }
              else { --nr; nextMode=true; }
            } else if(lfg==0) { fg=5; break; }
            else {
              tmd2=this->MemSys->Content.EGData.Energy[0];
              if(2*absval(tmd-tmd2)<absval(tmd+tmd2)*RelDelta<T>()) {
                if(isSteep) { fg=2; break; }
                else { --nr; nextMode=true; }
              }
            }
            isSteep=nextMode;
            oldfnorm2=fnorm2;
            fnorm=BlasNorm(this->MemSys->Content.EGData.Gradient);
            fnorm2=fnorm*fnorm;
          }
        }
        _Write2Sys(*this);
        return fg;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  const unsigned int
  Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>::DefaultMaxSteps=
      1000;

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,typename BT,template<typename> class CT,
            LineMinimizerConditionMethodName LMC>
  void Clear(Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>& M) {
    Clear(M.OldMinG);
    M.MaxBeta=0;
    typedef
    typename Minimizer<ConjugateGradient,LMN,T,IDT,PT,GT,BT,CT,LMC>::ParentType
    Type;
    Clear(static_cast<Type&>(M));
  }

}

#endif

