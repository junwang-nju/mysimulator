
#ifndef _Minimize_H_
#define _Minimize_H_

#include "data/minimizer/tracking-line-minimizer-buffer.h"
#include "operation/minimize/minimizer-buffer-base-op.h"
#include "operation/minimize/condition.h"

namespace std {

  template <unsigned int CType,
            typename IType,template<typename> class SpType,
            typename PmType,typename T>
  int Minimize(TrackingLineMinimizerBuffer<IType,SpType,PmType,T>& B,
               const SpType<T>& Dirc) {
    assert(IsAvailable(B));
    assert(IsAvailable(Dirc));
    assert(B.MinProject()<=0);
    if(B.MinProject()>=-B.GradThreshold())  return 2;
    const T mstep=MinimalStep(B,B.MinX,Dirc);
    T dstep=B.SearchScale();
    T step=dstep;
    T c1pj=B.DecFac()*B.MinProject();
    T c2pj=B.CurvFac()*B.MinProject();
    do {
      ProduceNewLocation(B,B.MinX,Dirc,step,B.RunX,B.RunE(),B.RunG,
                         B.RunPrj());
      if(Condition<CType>(B.RunE(),B.RunPrj(),B.MinEnergy(),c1pj,c2pj,step)) {
        swap(B.MinX,B.RunX);
        swap(B.MinG,B.RunG);
        B.MinEnergy()=B.RunE();
        B.MinProject()=B.RunPrj();
        B.MinMove()=step;
        return 1;
      }
      if((dstep>0)&&(B.RunPrj()>0.))  dstep*=-B.TrackingFac();
      else if((dstep<0.)&&(B.RunPrj()<0))   dstep*=-B.TrackingFac();
      step+=dstep;
    } while(absval(dstep)>mstep);
    return 2;
  }

}

#include "data/minimizer/steep-minimizer-buffer.h"

namespace std {

  template <unsigned int CondType,
            typename IType,template <typename> class SpType,
            typename PmType, typename T,
            template <typename,template <typename> class,
                      typename, typename> class LineMin>
  int Minimize(
        SteepestDescentMinimizerBuffer<IType,SpType,PmType,T,LineMin>& B,
        const unsigned int MaxIter=
          SteepestDescentMinimizerBuffer<IType,SpType,
                                         PmType,T,LineMin>::DefaultMaxIter) {
    typedef LineMin<IType,SpType,PmType,T>  LMType;
    B.GCalcCount()=0;
    B.LSearchCount()=0;
    T tmd;
    for(unsigned int neval=0;neval<MaxIter;++neval) {
      copy(B.Dirc,B.MinG);
      tmd=norm(B.Dirc);
      if(tmd<B.GradThreshold()) {
        B.LSearchCount()=neval;
        return 3;
      }
      scale(B.Dirc,-1./tmd);
      B.MinProject()=-tmd;
      tmd=B.MinEnergy();
      if(Minimize<CondType>(static_cast<LMType&>(B),B.Dirc)==2) {
        B.LSearchCount()=neval;
        return 1;
      }
      if(2*absval(tmd-B.MinEnergy())<=(tmd+B.MinEnergy())*RelDelta<T>()) {
        B.LSearchCount()=neval;
        return 2;
      }
    }
    B.LSearchCount()=MaxIter;
    return 0;
  }

}

#include "data/minimizer/conjg-minimizer-buffer.h"

namespace std {

  template <unsigned int CondType,
            typename IType, template <typename> class SpType,
            typename PmType, typename T,
            template <typename,template<typename> class,
                      typename,typename> class LineMin>
  int Minimize(
      ConjugateGradientMinimizerBuffer<IType,SpType,PmType,T,LineMin>& B,
      const unsigned int MaxIter=
          ConjugateGradientMinimizerBuffer<IType,SpType,
                                           PmType,T,LineMin>::DefaultMaxIter) {
    typedef LineMin<IType,SpType,PmType,T>  LMType;
    B.GCalcCount()=0;
    B.LSearchCount()=0;
    bool isSteep=true, nextMode;
    T beta=0.;
    T fnorm,fnorm2;
    fnorm=norm(B.MinG);
    fnorm2=fnorm*fnorm;
    if(fnorm<B.GradThreshold())   return 3;
    T tmd,oldfnorm2,dnorm;
    for(unsigned int neval=0;neval<MaxIter;++neval) {
      if(!isSteep) {
        oldfnorm2=fnorm2;
        fnorm=norm(B.MinG);
        fnorm2=fnorm*fnorm;
        tmd=dot(B.MinG,B.OldMinG);
        beta=(fnorm2-tmd)/oldfnorm2;
        if(absval(beta)>B.MaxBeta()) {
          beta=0.;
          isSteep=true;
        } else isSteep=false;
      }
      if(!isSteep) {
        tmd=beta*dnorm;
        scaleshift(B.Dirc,tmd,-iOne,B.MinG);
        B.MinProject()*=tmd;
        dnorm=sqroot(tmd*tmd+fnorm2-2*B.MinProject());
        B.MinProject()-=fnorm2;
        if((B.MinProject()>0)||(dnorm<B.GradThreshold())) {
          beta=0.;
          isSteep=true;
        }
      }
      if(isSteep) {
        dnorm=fnorm;
        if(dnorm<B.GradThreshold()) {
          B.LSearchCount()=neval-1;
          return 4;
        }
        copy(B.Dirc,B.MinG);
        scale(B.Dirc,-iOne);
        B.MinProject()=-fnorm2;
      }
      tmd=1./dnorm;
      scale(B.Dirc,tmd);
      copy(B.OldMinG,B.MinG);
      tmd=B.MinEnergy();
      nextMode=false;
      if(Minimize<CondType>(static_cast<LMType&>(B),B.Dirc)==2) {
        if(isSteep) {
          B.LSearchCount()=neval;
          return 1;
        } else {
          nextMode=true;
          --neval;
        }
      }
      if(2*absval(tmd-B.MinEnergy())<(tmd+B.MinEnergy())*RelDelta<T>()) {
        if(isSteep) {
          B.LSearchCount()=neval;
          return 2;
        } else {
          nextMode=true;
          --neval;
        }
      }
      isSteep=nextMode;
      fnorm=norm(B.MinG);
      fnorm2=fnorm*fnorm;
    }
    B.LSearchCount()=MaxIter;
    return 0;
  }

}

#include "data/minimizer/lbfgs-minimizer-buffer.h"

namespace std {

  template <unsigned int CondType,
            typename IType, template <typename> class SpType,
            typename PmType, typename T,
            template <typename,template<typename>class,
                      typename,typename> class LMin,
            unsigned int MCorr>
  int Minimize(LBFGSMinimizerBuffer<IType,SpType,PmType,T,LMin,MCorr>& B,
               const unsigned int MaxIter=
                  LBFGSMinimizerBuffer<IType,SpType,
                                       PmType,T,LMin,MCorr>::DefaultMaxIter) {
    assert(IsAvailable(B));
    typedef LMin<IType,SpType,PmType,T>   LMType;
    unsigned int nCorr;
    T diag,dgdg,dgdx,beta;
    B.GCalcCount()=0;
    B.LSearchCount()=0;
    bool isSteep=true, nextMode;
    unsigned int point=0, cp;
    T fnorm,fnorm2,dnorm,tmd;
    fnorm=norm(B.MinG);
    fnorm2=fnorm*fnorm;
    if(fnorm<B.GradThreshold()) return 3;
    for(unsigned int neval=0;neval<MaxIter;++neval) {
      if(!isSteep) {
        B.MinProject()=dot(B.Dirc,B.MinG);
        dnorm=norm(B.Dirc);
        if((B.MinProject()>0)||(dnorm<B.GradThreshold())) isSteep=true;
      }
      if(isSteep) {
        nCorr=0;
        copy(diag,iOne);
        copy(B.Dirc,B.MinG);
        scale(B.Dirc,-diag);
        B.MinProject()=-fnorm2;
        dnorm=fnorm;
        if(dnorm<B.GradThreshold()) {
          B.LSearchCount()=neval;
          return 4;
        }
      }
      scale(B.Dirc,1./dnorm);
      copy(B.dX[point],B.Dirc);
      copy(B.lastX,B.MinX);
      copy(B.lastG,B.MinG);
      nextMode=false;
      tmd=B.MinEnergy();
      if(Minimize<CondType>(static_cast<LMType&>(B),B.Dirc)==2) {
        if(isSteep) {
          B.LSearchCount()=neval;
          return 1;
        } else {
          nextMode=true;
          --neval;
        }
      }
      if(2*absval(tmd-B.MinEnergy())<(tmd+B.MinEnergy())*RelDelta<T>()) {
        if(isSteep) {
          B.LSearchCount()=neval;
          return 2;
        } else {
          nextMode=true;
          --neval;
        }
      }
      isSteep=nextMode;
      fnorm=norm(B.MinG);
      fnorm2=fnorm*fnorm;
      if(!isSteep) {
        if(nCorr<MCorr)   ++nCorr;
        copy(B.dG[point],B.MinG);
        shift(B.dG[point],-iOne,B.lastG);
        scale(B.dX[point],B.MinMove());
        dgdg=normSQ(B.dG[point]);
        dgdx=dot(B.dG[point],B.dX[point]);
        B.rho[point]=iOne/dgdx;
        diag=dgdx*B.rho[point];
        ++point;
        if(point>=MCorr)  point=0;
        copy(B.Dirc,B.MinG);
        scale(B.Dirc,-iOne);
        cp=point;
        for(unsigned int k=0;k<nCorr;++k) {
          cp=(cp==0?nCorr-1:cp-1);
          B.alpha[cp]=B.rho[cp]*dot(B.dX[cp],B.Dirc);
          shift(B.Dirc,-B.alpha[cp],B.dG[cp]);
        }
        scale(B.Dirc,diag);
        for(unsigned int k=0;k<nCorr;++k) {
          beta=B.alpha[cp]-B.rho[cp]*dot(B.Dirc,B.dG[cp]);
          shift(B.Dirc,beta,B.dX[cp]);
          cp=(cp==nCorr-1?0:cp+1);
        }
      }
    }
    B.LSearchCount()=MaxIter;
    return 0;
  }

}

#endif
