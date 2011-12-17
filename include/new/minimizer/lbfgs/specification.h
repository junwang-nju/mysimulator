
#ifndef _Minimizer_LBFGS_Specification_H_
#define _Minimizer_LBFGS_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"

namespace mysimulator {

  template <LineMinimizerMethodName LMN,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT,
            LineMinimizerConditionMethodName LCM>
  struct Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>
      : public LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM> {

    public:

      typedef Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>   Type;
      typedef LineMinimizer<LMN,T,IDT,PT,GT,VT,SCT,LCM>     ParentType;

      static const unsigned int DefaultMaxSteps;

      unsigned int MaxCorrelations;
      Array1D<VT<T> >     dX;
      Array1D<VT<T> >     dG;
      Array1D<T>          alpha;
      Array1D<T>          rho;
      VT<T>               lastX;
      VT<T>               lastG;

      Minimizer() : ParentType(), MaxCorrelations(0U), dX(), dG(), alpha(),
                    rho(), lastX(), lastG() {}
      ~Minimizer() { clearData(); }

      void clearData() {
        release(lastG);
        release(lastX);
        release(rho);
        release(alpha);
        for(unsigned int i=0;i<MaxCorrelations;++i) {
          release(dG[i]);
          release(dX[i]);
        }
        release(dG);
        release(dX);
        MaxCorrelations=0U;
        static_cast<ParentType*>(this)->clearData();
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&
               (MaxCorrelations>0)&&
               IsValid(dX)&&IsValid(dG)&&IsValid(alpha)&&IsValid(rho)&&
               IsValid(lastX)&&IsValid(lastG);
      }

      void SetMaxCorrelations() { MaxCorrelations=6; }
      void SetMaxCorrelations(const unsigned int& MC) { MaxCorrelations=MC; }

      int Go(const unsigned int& MaxSteps=DefaultMaxSteps) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        _load(*this);
        unsigned int ncr=0, point=0, cp;
        T diag,dgdg,dgdx,beta,fnorm,dnorm,tmd,tmd2;
        fnorm=norm(this->MemSys().Content().Gradient());
        if(fnorm<this->GradientThreshold) return 3;
        bool isSteep=true, nextMode;
        unsigned int fg=0, lfg;
        for(unsigned int ns=0;ns<MaxSteps;++ns) {
          if(!isSteep) {
            this->Proj=dot(this->LineDirc(),
                           this->MemSys().Content().Gradient());
            dnorm=norm(this->LineDirc());
            this->Proj/=dnorm;
            isSteep=((this->Proj>0)||(dnorm<this->GradientThreshold));
          }
          if(isSteep) {
            if(fnorm<this->GradientThreshold) {
              fg=4;
              break;
            } else {
              ncr=0;
              copy(diag,iOne);
              copy(this->LineDirc(),this->MemSys().Content().Gradient());
              scale(this->LineDirc(),-diag);
              this->Proj=-fnorm*diag;
              dnorm=fnorm*diag;
            }
          }
          scale(this->LineDirc(),1./dnorm);
          copy(dX[point],this->LineDirc());
          copy(lastX,this->MemSys().Content().X());
          copy(lastG,this->MemSys().Content().Gradient());
          tmd=this->MemSys().Content().Energy();
          lfg=static_cast<ParentType*>(this)->Go();
          ++(this->LineSearchCount);
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
          fnorm=norm(this->MemSys().Content().Gradient());
          if(!isSteep) {
            if(ncr<MaxCorrelations)   ++ncr;
            copy(dG[point],this->MemSys().Content().Gradient());
            shift(dG[point],-cOne,lastG);
            scale(dX[point],this->Move);
            dgdg=normSQ(dG[point]);
            dgdx=dot(dG[point],dX[point]);
            diag=dgdx/dgdg;
            rho[point]=iOne/dgdx;
            ++point;
            if(point>=MaxCorrelations)  point=0;
            copy(this->LineDirc(),this->MemSys().Content().Gradient());
            scale(this->LineDirc(),-cOne);
            cp=point;
            for(unsigned int k=0;k<ncr;++k) {
              cp=(cp==0?ncr-1:cp-1);
              alpha[cp]=rho[cp]*dot(dX[cp],this->LineDirc());
              shift(this->LineDirc(),-alpha[cp],dG[cp]);
            }
            scale(this->LineDirc(),diag);
            for(unsigned int k=0;k<ncr;++k) {
              beta=alpha[cp]-rho[cp]*dot(this->LineDirc(),dG[cp]);
              shift(this->LineDirc(),beta,dX[cp]);
              cp=(cp==ncr-1?0:cp+1);
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
  Minimizer<LBFGS,LMN,T,IDT,PT,GT,VT,SCT,LCM>::DefaultMaxSteps=
      1000;

}

#endif

