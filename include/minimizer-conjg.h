
#ifndef _Minimizer_Conjugate_Gradient_H_
#define _Minimizer_Conjugate_Gradient_H_

#include "util.h"
#include "storage-state-name.h"
#include "constant.h"
#include "minimizer-condition.h"
#include <cmath>

namespace std {

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  struct ConjugateGradientMinimizer
    : public LineMinMethod<SpaceDataType,ParameterType> {

    typedef
      ConjugateGradientMinimizer<SpaceDataType,ParameterType,LineMinMethod>
      Type;
    typedef LineMinMethod<SpaceDataType,ParameterType>  ParentType;

    static const unsigned int DefaultMaxIter;

    SpaceDataType *Dirc;
    SpaceDataType *OldMinGrad;
    double *MaxBeta;

    ConjugateGradientMinimizer()
      : ParentType(), Dirc(NULL), OldMinGrad(NULL), MaxBeta(NULL) {}
    ConjugateGradientMinimizer(const Type&) {
      myError("Cannot create from Conjugate-Gradient Minimizer");
    }
    Type& operator=(const Type& CM) { assign(*this,CM); return *this; }
    ~ConjugateGradientMinimizer() { release(*this); }

    template <unsigned int CondType>
    int Minimize(const unsigned int MaxIter=DefaultMaxIter) {
      *(this->GCalcCount)=0;
      *(this->LineSearchCount)=0;
      bool isSteep=true, nextMode;
      double beta=0.;
      double fnorm, fnorm2;
      fnorm=norm(*(this->MinGrad));
      fnorm2=fnorm*fnorm;
      if(fnorm<*(this->GradThreshold))  return 3;
      double tmd,oldfnorm2,dnorm;
      for(unsigned int neval=0;neval<MaxIter;++neval) {
        if(!isSteep) {
          oldfnorm2=fnorm2;
          fnorm=norm(*(this->MinGrad));
          fnorm2=fnorm*fnorm;
          tmd=dot(*(this->MinGrad),*OldMinGrad);
          beta=(fnorm2-tmd)/oldfnorm2;
          if(fabs(beta)>*MaxBeta) {
            beta=0.;
            isSteep=true;
          } else isSteep=false;
        }
        if(!isSteep) {
          tmd=beta*dnorm;
          scaleshift(*Dirc,tmd,-dOne,*(this->MinGrad));
          *(this->MinProject)*=tmd;
          dnorm=sqrt(tmd*tmd+fnorm2-2*(*(this->MinProject)));
          *(this->MinProject)-=fnorm2;
          if((*(this->MinProject)>0)||(dnorm<*(this->GradThreshold))) {
            beta=0.;
            isSteep=true;
          }
        }
        if(isSteep) {
          dnorm=fnorm;
          if(dnorm<*(this->GradThreshold)) {
            *(this->LineSearchCount)=neval-1;
            return 4;
          }
          assign(*Dirc,*(this->MinGrad));
          scale(*Dirc,-dOne);
          *(this->MinProject)=-fnorm2;
        }
        tmd=1./dnorm;
        scale(*Dirc,tmd);
        assign(*OldMinGrad,*(this->MinGrad));
        tmd=*(this->MinEnergy);
        nextMode=false;
        if(static_cast<ParentType*>(this)->Minimize<CondType>(*Dirc)==2) {
          if(isSteep) { *(this->LineSearchCount)=neval; return 1; }
          else { nextMode=true; --neval; }
        }
        if(2*(tmd-*(this->MinEnergy))<(tmd+*(this->MinEnergy))*DRelDelta) {
          if(isSteep) { *(this->LineSearchCount)=neval; return 2; }
          else { nextMode=true; --neval; }
        }
        isSteep=nextMode;
        fnorm=norm(*(this->MinGrad));
        fnorm2=fnorm*fnorm;
      }
      *(this->LineSearchCount)=MaxIter;
      return 0;
    }

  };

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  const unsigned int
  ConjugateGradientMinimizer<SpaceDataType,ParameterType,
                             LineMinMethod>::DefaultMaxIter=1000;

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  bool IsAvailable(
      const ConjugateGradientMinimizer<SpaceDataType,ParameterType,
                                       LineMinMethod>& CM) {
    return IsAvailable(CM.Dirc);
  }

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  void release(
      ConjugateGradientMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
      CM) {
    if(CM.state==Allocated) {
      safe_delete(CM.Dirc);
      safe_delete(CM.OldMinGrad);
      safe_delete(CM.MaxBeta);
    } else {
      CM.Dirc=NULL;
      CM.OldMinGrad=NULL;
      CM.MaxBeta=NULL;
    }
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    release(static_cast<PType&>(CM));
  }

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  void assign(
      ConjugateGradientMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
        dest,
      const ConjugateGradientMinimizer<SpaceDataType,ParameterType,
                                       LineMinMethod>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    assign(*(dest.Dirc),*(src.Dirc));
    assign(*(dest.OldMinGrad),*(src.OldMinGrad));
    *(dest.MaxBeta)=*(src.MaxBeta);
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    assign(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  void allocate(
      ConjugateGradientMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
        CM) {
    release(CM);
    CM.Dirc=new SpaceDataType;
    CM.OldMinGrad=new SpaceDataType;
    CM.MaxBeta=new double;
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    allocate(static_cast<PType&>(CM));
    *(CM.MaxBeta)=5.0;
  }

  template <typename SpaceDataType, typename ParameterType,
            template<typename,typename> class LineMinMethod>
  void refer(
      ConjugateGradientMinimizer<SpaceDataType,ParameterType,LineMinMethod>&
        dest,
      const ConjugateGradientMinimizer<SpaceDataType,ParameterType,
                                       LineMinMethod>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.Dirc=src.Dirc;
    dest.OldMinGrad=src.OldMinGrad;
    dest.MaxBeta=src.MaxBeta;
    typedef LineMinMethod<SpaceDataType,ParameterType>  PType;
    refer(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

}

#endif

