
#ifndef _Minimizer_Conjugate_Gradient_Base_H_
#define _Minimizer_Conjugate_Gradient_Base_H_

#include "constant.h"
#include "error-proc.h"
#include <cmath>

namespace std {

  template <typename LineMinMethod>
  class ConjugateGradientMinimizerBase : public LineMinMethod {

    public:

      typedef ConjugateGradientMinimizerBase<LineMinMethod>   Type;
      typedef LineMinMethod   ParentType;
      typedef typename LineMinMethod::RunSpaceVecType RunSpaceVecType;

      static const unsigned int DefaultMaxIter;

    protected:

      RunSpaceVecType Dirc;
      RunSpaceVecType OldMinGrad;
      double MaxBeta;

    public:

      ConjugateGradientMinimizerBase()
        : ParentType(), Dirc(), OldMinGrad(), MaxBeta(5.) {}

      ConjugateGradientMinimizerBase(const Type& CGM) {
        myError("Cannot create from minimizer with conjugate gradient");
      }

      Type& operator=(const Type& CGM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(CGM));
        Dirc=CGM.Dirc;
        OldMinGrad=CGM.OldMinGrad;
        MaxBeta=CGM.MaxBeta;
        return *this;
      }

      void SetMaxBetaFactor(const double mb) { MaxBeta=mb; }

      int Go(const unsigned int MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        this->MinLineCount=0;
        bool isSteep=true, nextMode;
        double beta=0.;
        double fnorm, fnorm2;
        fnorm=norm(this->MinGradSeq);
        fnorm2=fnorm*fnorm;
        if(fnorm<this->GradThreshold)   return 3;
        double tmd, oldfnorm2, dnorm;
        for(unsigned int neval=0;neval<MaxIter;++neval) {
          if(!isSteep) {
            oldfnorm2=fnorm2;
            fnorm=norm(this->MinGradSeq);
            fnorm2=fnorm*fnorm;
            tmd=dot(this->MinGradSeq,OldMinGrad);
            beta=(fnorm2-tmd)/oldfnorm2;
            if(fabs(beta)>MaxBeta) {
              beta=0.;
              isSteep=true;
            } else isSteep=false;
          }
          if(!isSteep) {
            tmd=beta*dnorm;
            Dirc.scaleshift(tmd,-1.,this->MinGradSeq);
            this->MinPrj*=tmd;
            dnorm=sqrt(tmd*tmd+fnorm2-2*this->MinPrj);
            this->MinPrj-=fnorm2;
            if((this->MinPrj>0.)||(dnorm<this->GradThreshold)) {
              beta=0.;
              isSteep=true;
            }
          }
          if(isSteep) {
            Dirc=this->MinGradSeq;
            Dirc.scale(-1.);
            this->MinPrj=-fnorm2;
            dnorm=fnorm;
            if(dnorm<this->GradThreshold) {
              this->MinLineCount=neval;
              return 4;
            }
          }
          tmd=1./dnorm;
          Dirc.scale(tmd);
          OldMinGrad=this->MinGradSeq;
          tmd=this->MinE;
          nextMode=false;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2) {
            if(isSteep) { this->MinLineCount=neval; return 1; }
            else        { nextMode=true;  --neval; }
          }
          if(2.*(tmd-this->MinE)<(tmd+this->MinE)*DRelDelta) {
            if(isSteep) { this->MinLineCount=neval; return 2; }
            else        { nextMode=true; --neval; }
          }
          isSteep=nextMode;
        }
        this->MinLineCount=MaxIter;
        return 0;
      }

  };

  template <typename LineMinMethod>
  const unsigned int
  ConjugateGradientMinimizerBase<LineMinMethod>::DefaultMaxIter=1000;
}

#endif

