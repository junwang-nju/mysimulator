
#ifndef _Minimizer_ConjugateGradient_Specification_H_
#define _Minimizer_ConjugateGradient_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMinName, typename T, typename FT,typename IDT,
            typename PT,typename GT,template <typename> class ST>
  struct Minimizer<ConjugateGradient,LMinName,T,FT,IDT,PT,GT,ST>
    : public LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST> {

    public:

      typedef Minimizer<ConjugateGradient,LMinName,T,FT,IDT,PT,GT,ST> Type;
      typedef LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST>     ParentType;

      static const unsigned int DefaultMaxIterations;

      ST<T> OldMinG;
      T MaxBeta;

      Minimizer() : ParentType(), OldMinG(), MaxBeta() {}
      ~Minimizer() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        release(OldMinG);
        MaxBeta=0.;
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               IsValid(OldMinG)&&(MaxBeta>0.);
      }

      void SetMaxBeta() { copy(MaxBeta,5); }
      template <typename T1>
      void SetMaxBeta(const T1& MB) { copy(MaxBeta,MB); }

      virtual int Go(const unsigned int& MaxIt=DefaultMaxIterations) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        bool isSteep=true;
        bool nxMode;
        T beta=0;
        T fnorm,fnorm2;
        fnorm=norm(this->Sys().G());
        if(fnorm<this->GradThreshold) return 3;
        fnorm2=fnorm*fnorm;
        T tmd,oldfnorm2=1,dnorm=0;
        int f=0, lf;
        for(unsigned int neval=0;neval<MaxIt;++neval) {
          if(!isSteep) {
            tmd=dot(this->Sys().G(),this->OldMinG);
            beta=(fnorm2-tmd)/oldfnorm2;
            isSteep=(absval(beta)>MaxBeta);
          }
          if(!isSteep) {
            tmd=beta*dnorm;
            scale(this->LineDirc,tmd);
            shift(this->LineDirc,-cOne,this->Sys().G());
            this->Proj*=tmd;
            dnorm=sqroot(tmd*tmd+fnorm2-2*this->Proj);
            this->Proj-=fnorm2;
            this->Proj/=dnorm;
            isSteep=((this->Proj>0)||(dnorm<this->GradThreshold));
          }
          if(isSteep) {
            if(fnorm<this->GradThreshold) {
              this->LineSearchCount=neval-1;
              f=4;
              break;
            }
            copy(beta,cZero);
            dnorm=fnorm;
            copy(this->LineDirc,this->Sys().G);
            scale(this->LineDirc,-cOne);
            this->Proj=-fnorm;
          }
          tmd=1./dnorm;
          scale(this->LineDirc,tmd);
          copy(this->OldMinG,this->Sys().G);
          tmd=this->Sys().Energy;
          lf=static_cast<ParentType*>(this)->_Go();
          nxMode=false;
          if(lf==2) {
            if(isSteep) { this->LineSearchCount=neval; f=1; break; }
            --neval;
            nxMode=true;
          } else if(lf==0) { this->LineSearchCount=neval; f=5; break; }
          if(2*absval(tmd-this->Sys().Energy)<
             absval(tmd+this->Sys().Energy)*RelativeDelta<T>()) {
            if(isSteep) { this->LineSearchCount=neval; f=2; break; }
            --neval;
            nxMode=true;
          }
          isSteep=nxMode;
          oldfnorm2=fnorm2;
          fnorm=norm(this->Sys().G());
          fnorm2=fnorm*fnorm;
        }
        if(f==0)  this->LineSearchCount=MaxIt;
        return f;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerName LMN, typename T, typename FT,typename IDT,
            typename PT,typename GT,template <typename> class ST>
  const unsigned int
  Minimizer<ConjugateGradient,LMN,T,FT,IDT,PT,GT,ST>::DefaultMaxIterations
  =1000;

}

#endif

