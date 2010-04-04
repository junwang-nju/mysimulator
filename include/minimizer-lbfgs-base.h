
#ifndef _Minimizer_LBFGS_Base_H_
#define _Minimizer_LBFGS_Base_H_

#include "fix-vector.h"
#include "vector-op.h"

namespace std {

  enum LBFGSDiagType {
    HK0Diag=0,
    ConstDiag
  };

  template <typename LineMinMethod, unsigned int MaxCorr=6U>
  class LBFGSbMinimizerBase : public LineMinMethod {

    public:

      typedef LBFGSbMinimizerBase<LineMinMethod,MaxCorr>    Type;
      typedef LineMinMethod   ParentType;
      typedef typename LineMinMethod::RunSpaceVecType RunSpaceVecType;

      static const unsigned int DefaultMaxIter;

    protected:

      RunSpaceVecType                     Dirc;
      fixVector<RunSpaceVecType,MaxCorr>  dX;
      fixVector<RunSpaceVecType,MaxCorr>  dG;
      fixVector<double,MaxCorr>           alpha;
      fixVector<double,MaxCorr>           rho;
      RunSpaceVecType                     lastX;
      RunSpaceVecType                     lastG;

    public:

      LBFGSbMinimizerBase()
        : ParentType(), Dirc(), dX(), dG(), alpha(), rho(), lastX(), lastG() {}

      LBFGSbMinimizerBase(const Type& LM) {
        myError("Cannot create from LBFGS-b Minimizer Base");
      }

      Type& operator=(const Type& LM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(LM));
        Dirc=LM.Dirc();
        dX=LM.dX;
        dG=LM.dG;
        alpha=LM.alpha;
        rho=LM.rho;
        lastX=LM.lastX;
        lastG=LM.lastG;
        return *this;
      }

      int Go(const unsigned int MaxIter=DefaultMaxIter) {
        unsigned int nCorr;
        double diag, dgdg, dgdx, beta;
        this->MinGCount=0;
        this->MinLineCount=0;
        bool isSteep=true,nextMode;
        int point=0,cp;
        double fnorm,fnorm2,dnorm,tmd;
        fnorm=norm(this->MinGradSeq);
        fnorm2=fnorm*fnorm;
        if(fnorm<this->GradThreshold)   return 3;
        for(unsigned int neval=0;neval<MaxIter;++neval) {
          if(!isSteep) {
            this->MinPrj=dot(Dirc,this->MinGradSeq);
            dnorm=norm(Dirc);
            if((this->MinPrj>0)||(dnorm<this->GradThreshold)) isSteep=true;
          }
          if(isSteep) {
            nCorr=0;
            diag=1.;
            Dirc=this->MinGradSeq;
            Dirc.scale(-diag);
            this->MinPrj=-fnorm2;
            dnorm=fnorm;
            if(dnorm<this->GradThreshold) {
              this->MinLineCount=neval-1;
              return 4;
            }
          }
          Dirc.scale(1./dnorm);
          dX[point]=Dirc;
          lastX=this->MinCoorSeq;
          lastG=this->MinGradSeq;
          nextMode=false;
          tmd=this->MinE;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2) {
            if(isSteep) { this->MinLineCount=neval; return 1; }
            else        { nextMode=true; --neval; }
          }
          if(2*(tmd-this->MinE)<(tmd+this->MinE)*DRelDelta) {
            if(isSteep) { this->MinLineCount=neval; return 2; }
            else        { nextMode=true; --neval; }
          }
          isSteep=nextMode;
          fnorm=norm(this->MinGradSeq);
          fnorm2=fnorm*fnorm;
          if(!isSteep) {
            if(nCorr<MaxCorr)   ++nCorr;
            dG[point]=this->MinGradSeq;
            dG[point].shift(-1.,lastG);
            dX[point].scale(this->MinMove);
            dgdg=normSQ(dG[point]);
            dgdx=dot(dG[point],dX[point]);
            diag=dgdx/dgdg;
            rho[point]=1./dgdx;
            ++point;
            if(point>=static_cast<int>(MaxCorr))  point=0;
            Dirc=this->MinGradSeq;
            Dirc.scale(-1.);
            cp=point;
            for(unsigned int k=0;k<nCorr;++k) {
              --cp;
              if(cp<0)  cp=nCorr-1;
              alpha[cp]=rho[cp]*dot(dX[cp],Dirc);
              Dirc.shift(-alpha[cp],dG[cp]);
            }
            Dirc.scale(diag);
            for(unsigned int k=0;k<nCorr;++k) {
              beta=alpha[cp]-rho[cp]*dot(Dirc,dG[cp]);
              Dirc.shift(beta,dX[cp]);
              ++cp;
              if(cp>=static_cast<int>(nCorr))  cp=0;
            }
          }
        }
        this->MinLineCount=MaxIter;
        return 0;
      }

  };

  template <typename LineMinMethod, unsigned int MaxCorr>
  const unsigned int
  LBFGSbMinimizerBase<LineMinMethod,MaxCorr>::DefaultMaxIter=1000;

}

#endif

