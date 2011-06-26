
#ifndef _Minimizer_LBFGS_Specification_H_
#define _Minimizer_LBFGS_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"
#include "vector/interface.h"

namespace mysimulator {

  template <LineMinimizerName LMinName, typename IKernelType,
            template<typename> class SpaceVType,typename IParamType,typename T>
  struct Minimizer<LBFGS,LMinName,IKernelType,SpaceVType,IParamType,T>
      : public LineMinimizer<LMinName,IKernelType,SpaceVType,IParamType,T> {

    typedef Minimizer<LBFGS,LMinName,IKernelType,SpaceVType,IParamType,T>
            Type;
    typedef LineMinimizer<LMinName,IKernelType,SpaceVType,IParamType,T>
            ParentType;

    static const unsigned int DefaultMaxIterations;

    unsigned int MaxCorrelation;
    Vector<SpaceVType<T> >  dX;
    Vector<SpaceVType<T> >  dG;
    Vector<T>               alpha;
    Vector<T>               rho;
    SpaceVType<T>           lastX;
    SpaceVType<T>           lastG;

    Minimizer() : ParentType(), MaxCorrelation(0), dX(), dG(), alpha(), rho(),
                  lastX(), lastG() {}
    Minimizer(const Type&) { Error("Copier of Minimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Minimizer Disabled!");
      return *this;
    }
    ~Minimizer() { clearData(); }

    void clearData() {
      release(*static_cast<ParentType*>(this));
      MaxCorrelation=0;
      release(dX);
      release(dG);
      release(alpha);
      release(rho);
      release(lastX);
      release(lastG);
    }

    void SetMaxCorrelation() { MaxCorrelation=6; }
    void SetMaxCorrelation(const unsigned int& MCorr) { MaxCorrelation=MCorr; }

    virtual int Go(const unsigned int MaxIt=DefaultMaxIterations) {
      assert(IsValid(*this));
      unsigned int ncorr,point=0,cp;
      T diag,dgdg,dgdx,beta,fnorm,fnorm2,dnorm,tmd;
      bool isSteep=true, nextMode;
      this->GCalcCount=0;
      this->LineSearchCount=0;
      fnorm=norm(this->MinG());
      if(fnorm<this->GradThreshold)   return 3;
      fnorm2=fnorm*fnorm;
      unsigned int f=0, lf;
      for(unsigned int neval=0;neval<MaxIt;++neval) {
        if(!isSteep) {
          this->MinProject=dot(this->LineDirc,this->MinG());
          dnorm=norm(this->LineDirc);
          isSteep=((this->MinProject>0)||(dnorm<this->GradThreshold));
        }
        if(isSteep) {
          ncorr=0;
          copy(diag,iOne);
          copy(this->LineDirc,this->MinG);
          scale(this->LineDirc,-diag);
          this->MinProject=-fnorm2;
          dnorm=fnorm;
          if(dnorm<this->GradThreshold) {
            this->LineSearchCount=neval;
            f=4;
            break;
          }
        }
        scale(this->LineDirc,1./dnorm);
        copy(dX[point],this->LineDirc);
        copy(lastX,this->MinX);
        copy(lastG,this->MinG);
        nextMode=false;
        tmd=this->MinEnergy;
        lf=static_cast<ParentType*>(this)->_Go();
        if(lf==2) {
          if(isSteep) { this->LineSearchCount=neval; f=1; break; }
          --neval;
          nextMode=true;
        } else if(lf==0) { this->LineSearchCount=neval; f=5; break; }
        if(2*absval(tmd-this->MinEnergy)<
           absval(tmd+this->MinEnergy)*RelativeDelta<T>()) {
          if(isSteep) { this->LineSearchCount=neval; f=2; break; }
          --neval;
          nextMode=true;
        }
        isSteep=nextMode;
        fnorm=norm(this->MinG());
        fnorm2=fnorm*fnorm;
        if(!isSteep) {
          if(ncorr<MaxCorrelation)  ++ncorr;
          copy(dG[point],this->MinG);
          shift(dG[point],-iOne,lastG);
          scale(dX[point],this->MinMove);
          dgdg=normSQ(dG[point]);
          dgdx=dot(dG[point],dX[point]);
          diag=dgdx/dgdg;
          rho[point]=iOne/dgdx;
          ++point;
          if(point>=MaxCorrelation)   point=0;
          copy(this->LineDirc,this->MinG);
          scale(this->LineDirc,-iOne);
          cp=point;
          for(unsigned int k=0;k<ncorr;++k) {
            cp=(cp==0?ncorr-1:cp-1);
            alpha[cp]=rho[cp]*dot(dX[cp],this->LineDirc);
            shift(this->LineDirc,-alpha[cp],dG[cp]);
          }
          scale(this->LineDirc,diag);
          for(unsigned int k=0;k<ncorr;++k) {
            beta=alpha[cp]-rho[cp]*dot(this->LineDirc,dG[cp]);
            shift(this->LineDirc,beta,dX[cp]);
            cp=(cp==ncorr-1?0:cp+1);
          }
        }
      }
      if(f==0)  this->LineSearchCount=MaxIt;
      return f;
    }

  };

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  const unsigned int
  Minimizer<LBFGS,LMN,KT,VT,PT,T>::DefaultMaxIterations=1000;

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  bool IsValid(const Minimizer<LBFGS,LMN,KT,VT,PT,T>& M) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    return IsValid(static_cast<const Type&>(M))&&IsValid(M.dX)&&
           IsValid(M.dG)&&IsValid(M.alpha)&&IsValid(M.rho)&&IsValid(M.lastX)&&
           IsValid(M.lastG)&&IsValid(M.MaxCorrelation>0);
  }

  template <LineMinimizerName LMN,typename KT,template<typename> class VT,
            typename PT,typename T>
  void release(Minimizer<LBFGS,LMN,KT,VT,PT,T>& M) { M.clearData(); }

}

#endif

