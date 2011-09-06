
#ifndef _Minimizer_LBFGS_Specification_H_
#define _Minimizer_LBFGS_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"
#include "array/1d/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMinName, typename T,typename FT,typename IDT,
            typename PT,typename GT,template<typename> class ST>
  struct Minimizer<LBFGS,LMinName,T,FT,IDT,PT,GT,ST>
      : public LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST> {

    public:

      typedef Minimizer<LBFGS,LMinName,T,FT,IDT,PT,GT,ST>   Type;
      typedef LineMinimizer<LMinName,T,FT,IDT,PT,GT,ST>     ParentType;

      static const unsigned int DefaultMaxIterations;

      unsigned int MaxCorrelation;
      Array1D<ST<T> >   dX;
      Array1D<ST<T> >   dG;
      Array1D<T>        alpha;
      Array1D<T>        rho;
      ST<T>             lastX;
      ST<T>             lastG;

      Minimizer() : ParentType(),dX(),dG(),alpha(),rho(),lastX(),lastG() {}
      ~Minimizer() { clearData(); }

      void clearData() {
        static_cast<ParentType*>(this)->clearData();
        MaxCorrelation=0;
        release(lastG);
        release(lastX);
        release(rho);
        release(alpha);
        release(dG);
        release(dX);
      }
      bool isvalid() const {
        return static_cast<const ParentType*>(this)->isvalid()&&IsValid(dX)&&
               IsValid(dG)&&IsValid(alpha)&&IsValid(rho)&&IsValid(lastX)&&
               IsValid(lastG);
      }

      void SetMaxCorrelation() { MaxCorrelation=6; }
      void SetMaxCorrelation(const unsigned int& MC) { MaxCorrelation=MC; }

      virtual int Go(const unsigned int& MaxIt=DefaultMaxIterations) {
        assert(isvalid());
        this->GCalcCount=0;
        this->LineSearchCount=0;
        unsigned int ncr,point,cp;
        point=0;
        T diag,dgdg,dgdx,beta,fnorm,dnorm,tmd;
        fnorm=norm(this->Sys().G());
        if(fnorm<this->GradThreshold)   return 3;
        bool isSteep,nxMode;
        isSteep=true;
        unsigned int f=0, lf;
        for(unsigned int neval=0;neval<MaxIt;++neval) {
          if(!isSteep) {
            this->Proj=dot(this->LineDirc,this->Sys().G());
            dnorm=norm(this->LineDirc);
            this->Proj/=dnorm;
            isSteep=((this->Proj>0)||(dnorm<this->GradThreshold));
          }
          if(isSteep) {
            if(fnorm<this->GradThreshold) {
              this->LineSearchCount=neval;
              f=4;
              break;
            }
            ncr=0;
            copy(diag,iOne);
            copy(this->LineDirc,this->Sys().G);
            scale(this->LineDirc,-diag);
            this->Proj=-fnorm*diag;
            dnorm=fnorm*diag;
          }
          scale(this->LineDirc,1./dnorm);
          copy(dX[point],this->LineDirc);
          copy(lastX,this->Sys().X);
          copy(lastG,this->Sys().G);
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
          fnorm=norm(this->Sys().G());
          if(!isSteep) {
            if(ncr<MaxCorrelation)  ++ncr;
            copy(dG[point],this->Sys().G);
            shift(dG[point],-cOne,lastG);
            scale(dX[point],this->Move);
            dgdg=normSQ(dG[point]);
            dgdx=dot(dG[point],dX[point]);
            diag=dgdx/dgdg;
            rho[point]=iOne/dgdx;
            ++point;
            if(point>=MaxCorrelation) point=0;
            copy(this->LineDirc,this->Sys().G);
            scale(this->LineDirc,-cOne);
            cp=point;
            for(unsigned int k=0;k<ncr;++k) {
              cp=(cp==0?ncr-1:cp-1);
              alpha[cp]=rho[cp]*dot(dX[cp],this->LineDirc);
              shift(this->LineDirc,-alpha[cp],dG[cp]);
            }
            scale(this->LineDirc,diag);
            for(unsigned int k=0;k<ncr;++k) {
              beta=alpha[cp]-rho[cp]*dot(this->LineDirc,dG[cp]);
              shift(this->LineDirc,beta,dX[cp]);
              cp=(cp==ncr-1?0:cp+1);
            }
          }
        }
        if(f==0)  this->LineSearchCount=MaxIt;
        return f;
      }

    private:

      Minimizer(const Type&) {}
      Type& operator=(const Type&) { return *this; }

  };

  template <LineMinimizerName LMN, typename T,typename FT,typename IDT,
            typename PT,typename GT,template<typename> class ST>
  const unsigned int
  Minimizer<LBFGS,LMN,T,FT,IDT,PT,GT,ST>::DefaultMaxIterations=1000;

}

#endif

