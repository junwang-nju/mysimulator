
#ifndef _Minimizer_ConjugateGradient_Specification_H_
#define _Minimizer_ConjugateGradient_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/interface.h"
#include "intrinsic-type/abs-value.h"
#include "intrinsic-type/sqroot.h"
#include <iostream>

namespace mysimulator {

  template <LineMinimizerName LMinName, typename IKernelType,
            template<typename> class SpaceVType,typename IParamType,typename T>
  struct Minimizer<ConjugateGradient,LMinName,IKernelType,SpaceVType,
                   IParamType,T>
      : public LineMinimizer<LMinName,IKernelType,SpaceVType,IParamType,T> {

    typedef IKernelType IKType;
    typedef IParamType  IPType;
    typedef Minimizer<ConjugateGradient,LMinName,IKType,SpaceVType,IPType,T>
            Type;
    typedef LineMinimizer<LMinName,IKType,SpaceVType,IPType,T>  ParentType;

    static const unsigned int DefaultMaxIterations;

    SpaceVType<T> OldMinG;
    T MaxBeta;

    Minimizer() : ParentType(), OldMinG(), MaxBeta(0) {}
    Minimizer(const Type&) { Error("Copier of Minimizer Disabled!"); }
    Type& operator=(const Type&) {
      Error("Operator= for Minimizer Disabled!");
      return *this;
    }
    ~Minimizer() { clearData(); }

    void clearData() {
      static_cast<ParentType*>(this)->clearData();
      release(OldMinG);
      MaxBeta=0;
    }

    void SetMaxBeta() { copy(MaxBeta,5); }
    void SetMaxBeta(const T& MB) { copy(MaxBeta,MB); }

    virtual int Go(const unsigned int MaxIt=DefaultMaxIterations) {
      assert(IsValid(*this));
      this->GCalcCount=0;
      this->LineSearchCount=0;
      bool isSteep=true;
      bool nextMode;
      T beta=0,fnorm,fnorm2;
      fnorm=norm(this->MinG());
      if(fnorm<this->GradThreshold) { return 3; }
      fnorm2=fnorm*fnorm;
      T tmd,oldfnorm2=1,dnorm=0;
      int f=0,lf;
      for(unsigned int neval=0;neval<MaxIt;++neval) {
        if(!isSteep) {
          oldfnorm2=fnorm2;
          fnorm=norm(this->MinG());
          fnorm2=fnorm*fnorm;
          tmd=dot(this->MinG(),this->OldMinG);
          beta=(fnorm2-tmd)/oldfnorm2;
          isSteep=(absval(beta)>MaxBeta);
        }
        if(!isSteep) {
          tmd=beta*dnorm;
          scaleshift(this->LineDirc,tmd,-iOne,this->MinG());
          this->MinProject*=tmd;
          dnorm=sqroot(tmd*tmd+fnorm2-2*this->MinProject);
          this->MinProject-=fnorm2;
          isSteep=((this->MinProject>0)||(dnorm<this->GradThreshold)); 
        }
        if(isSteep) {
          copy(beta,0);
          dnorm=fnorm;
          if(dnorm<this->GradThreshold) {
            this->LineSearchCount=neval-1;
            f=4;
            break;
          }
          copy(this->LineDirc,this->MinG);
          scale(this->LineDirc,-iOne);
          this->MinProject=-fnorm2;
        }
        tmd=1./dnorm;
        scale(this->LineDirc,tmd);
        copy(this->OldMinG,this->MinG);
        tmd=this->MinEnergy;
        nextMode=false;
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
      }
      if(f==0)  this->LineSearchCount=MaxIt;
      return f;
    }

  };

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  const unsigned int
  Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>::DefaultMaxIterations=1000;

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  bool IsValid(const Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>& M) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    return IsValid(static_cast<const Type&>(M))&&IsValid(M.OldMinG)&&
           (M.MaxBeta>0);
  }

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void release(Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>& M){ M.clearData(); }

}

#endif

