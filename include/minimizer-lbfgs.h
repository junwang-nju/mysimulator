
#ifndef _Minimizer_LBFGS_H_
#define _Minimizer_LBFGS_H_

#include "storage-state-name.h"
#include "minimizer-condition.h"
#include "constant.h"

namespace std {

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr=6>
  struct LBFGSMinimizer : public LineMinMethod<SpaceDataType,ParameterType> {

    typedef LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>
            Type;
    typedef LineMinMethod<SpaceDataType,ParameterType> ParentType;

    static const unsigned int DefaultMaxIter;

    SpaceDataType *Dirc;
    SpaceDataType *dX;
    SpaceDataType *dG;
    double *alpha;
    double *rho;
    SpaceDataType *lastX;
    SpaceDataType *lastG;

    LBFGSMinimizer()
      : ParentType(), Dirc(NULL), dX(NULL), dG(NULL), alpha(NULL), rho(NULL),
        lastX(NULL), lastG(NULL) {}
    LBFGSMinimizer(const Type&) {
      myError("Cannot create from LBFGS Minimizer");
    }
    Type& operator=(const Type& LM) { assign(*this,LM); return *this; }
    ~LBFGSMinimizer() { release(*this); }

    template <unsigned int CondType>
    int Minimize(const unsigned int MaxIter=DefaultMaxIter) {
      assert(IsAvailable(*this));
      unsigned int nCorr;
      double diag, dgdg, dgdx, beta;
      *(this->GCalcCount)=0;
      *(this->LineSearchCount)=0;
      bool isSteep=true, nextMode;
      unsigned int point=0, cp;
      double fnorm, fnorm2, dnorm, tmd;
      fnorm=norm(*(this->MinGrad));
      fnorm2=fnorm*fnorm;
      if(fnorm<*(this->GradThreshold))  return 3;
      for(unsigned int neval=0;neval<MaxIter;++neval) {
        if(!isSteep) {
          *(this->MinProject)=dot(*Dirc,*(this->MinGrad));
          dnorm=norm(*Dirc);
          if((*(this->MinProject)>0)||(dnorm<*(this->GradThreshold)))
            isSteep=true;
        }
        if(isSteep) {
          nCorr=0;
          diag=dOne;
          assign(*Dirc,*(this->MinGrad));
          scale(*Dirc,-diag);
          *(this->MinProject)=-fnorm2;
          dnorm=fnorm;
          if(dnorm<*(this->GradThreshold)) {
            *(this->LineSearchCount)=neval-1;
            return 4;
          }
        }
        scale(*Dirc,1./dnorm);
        assign(dX[point],*Dirc);
        assign(*lastX,*(this->MinCoor));
        assign(*lastG,*(this->MinGrad));
        nextMode=false;
        tmd=*(this->MinEnergy);
        if(static_cast<ParentType*>(this)->Minimize<CondType>(*Dirc)==2) {
          if(isSteep) { *(this->LineSearchCount)=neval; return 1; }
          else { nextMode=true; --neval; }
        }
        if(2.*(tmd-*(this->MinEnergy))<(tmd+*(this->MinEnergy))*DRelDelta) {
          if(isSteep) { *(this->LineSearchCount)=neval; return 2; }
          else { nextMode=true; --neval; }
        }
        isSteep=nextMode;
        fnorm=norm(*(this->MinGrad));
        fnorm2=fnorm*fnorm;
        if(!isSteep) {
          if(nCorr<MaxCorr) ++nCorr;
          assign(dG[point],*(this->MinGrad));
          shift(dG[point],-dOne,*lastG);
          scale(dX[point],*(this->MinMove));
          dgdg=normSQ(dG[point]);
          dgdx=dot(dG[point],dX[point]);
          diag=dgdx/dgdg;
          rho[point]=dOne/dgdx;
          ++point;
          if(point>=MaxCorr)  point=0;
          assign(*Dirc,*(this->MinGrad));
          scale(*Dirc,-dOne);
          cp=point;
          for(unsigned int k=0;k<nCorr;++k) {
            cp=(cp==0?nCorr-1:cp-1);
            alpha[cp]=rho[cp]*dot(dX[cp],*Dirc);
            shift(*Dirc,-alpha[cp],dG[cp]);
          }
          scale(*Dirc,diag);
          for(unsigned int k=0;k<nCorr;++k) {
            beta=alpha[cp]-rho[cp]*dot(*Dirc,dG[cp]);
            shift(*Dirc,beta,dX[cp]);
            cp=(cp==nCorr-1?0:cp+1);
          }
        }
      }
      *(this->LineSearchCount)=MaxIter;
      return 0;
    }

  };

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  const unsigned int
  LBFGSMinimizer<SpaceDataType,ParameterType,
                 LineMinMethod,MaxCorr>::DefaultMaxIter=1000;

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  bool IsAvailable(
      const LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>&
            LM) {
    return IsAvailable(LM.Dirc);
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void release(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& LM) {
    if(LM.state==Allocated) {
      safe_delete(LM.Dirc);
      safe_delete_array(LM.dX);
      safe_delete_array(LM.dG);
      safe_delete_array(LM.alpha);
      safe_delete_array(LM.rho);
      safe_delete(LM.lastX);
      safe_delete(LM.lastG);
    } else {
      LM.Dirc=NULL;
      LM.dX=NULL;
      LM.dG=NULL;
      LM.alpha=NULL;
      LM.rho=NULL;
      LM.lastX=NULL;
      LM.lastG=NULL;
    }
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    release(static_cast<PType&>(LM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void assign(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& dest,
      const LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>&
        src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(*(dest.Dirc),*(src.Dirc));
    assign(dest.dX,src.dX,MaxCorr);
    assign(dest.dG,src.dG,MaxCorr);
    assign(dest.alpha,src.alpha,MaxCorr);
    assign(dest.rho,src.rho,MaxCorr);
    assign(*(dest.lastX),*(src.lastX));
    assign(*(dest.lastG),*(src.lastG));
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    assign(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void allocate(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& LM) {
    release(LM);
    LM.Dirc=new SpaceDataType;
    LM.dX=new SpaceDataType[MaxCorr];
    LM.dG=new SpaceDataType[MaxCorr];
    LM.alpha=new double[MaxCorr];
    LM.rho=new double[MaxCorr];
    LM.lastX=new SpaceDataType;
    LM.lastG=new SpaceDataType;
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    allocate(static_cast<PType&>(LM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template <typename,typename> class LineMinMethod,
            unsigned int MaxCorr>
  void refer(
      LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>& dest,
      const LBFGSMinimizer<SpaceDataType,ParameterType,LineMinMethod,MaxCorr>&
        src) {
    assert(IsAvailable(src));
    release(dest);
    dest.Dirc=src.Dirc;
    dest.dX=src.dX;
    dest.dG=src.dG;
    dest.alpha=src.alpha;
    dest.rho=src.rho;
    dest.lastX=src.lastX;
    dest.lastG=src.lastG;
    typedef LineMinMethod<SpaceDataType,ParameterType> PType;
    refer(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

}

#endif

