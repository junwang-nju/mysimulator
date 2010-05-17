
#ifndef _Minimizer_Line_Tracking_H_
#define _Minimizer_Line_Tracking_H_

#include "minimizer-condition.h"
#include "minimizer-line-base.h"
#include <cmath>

namespace std {

  template <typename SpaceDataType, typename ParameterType>
  struct TrackingLineMinimizer
    : public LineMinimizerBase<SpaceDataType,ParameterType> {

    typedef TrackingLineMinimizer<SpaceDataType,ParameterType>  Type;
    typedef LineMinimizerBase<SpaceDataType,ParameterType>  ParentType;

    double *TrackingFac;

    TrackingLineMinimizer() : ParentType(), TrackingFac(NULL) {}
    TrackingLineMinimizer(const Type&) {
      myError("Cannot create from Line Minimizer with Tracking Method");
    }
    Type& operator=(const Type& TLM) { assign(*this,TLM); return *this; }
    ~TrackingLineMinimizer() { release(*this); }

    template <unsigned int CondType>
    int Minimize(const SpaceDataType& Dirc) {
      assert(IsAvailable(*this));
      assert(*(this->MinProject)<=0);
      if(*(this->MinProject)>=-*(this->GradThreshold))  return 2;
      const double mstep=minimalstep(*this,*(this->MinCoor),Dirc);
      double dstep=*(this->SearchScale), step=dstep;
      double c1pj=(*(this->DecreaseFactor))*(*(this->MinProject));
      double c2pj=(*(this->CurvatureFactor))*(*(this->MinProject));
      do {
        GenerateNewLocation(
            *this,*(this->MinCoor),Dirc,step,*(this->RunCoor),
            *(this->RunEnergy),*(this->RunGrad),*(this->RunProject));
        if(Condition<CondType>(*(this->RunEnergy),*(this->RunProject),
                               *(this->MinEnergy),c1pj,c2pj,step)) {
          swap(*(this->MinCoor),*(this->RunCoor));
          swap(*(this->MinGrad),*(this->RunGrad));
          *(this->MinEnergy)=*(this->RunEnergy);
          *(this->MinProject)=*(this->RunProject);
          *(this->MinMove)=step;
          return 1;
        }
        if((dstep>0)&&(*(this->RunProject)>0)) dstep*=-(*TrackingFac);
        else if((dstep<0)&&(*(this->RunProject)<0))  dstep*=-(*TrackingFac);
        step+=dstep;
      } while(fabs(dstep)>mstep);
      return 2;
    }

  };

  template <typename SpaceDataType, typename ParameterType>
  bool IsAvailable(
      const TrackingLineMinimizer<SpaceDataType,ParameterType>& TLM) {
    return IsAvailable(TLM.TrackingFac);
  }

  template <typename SpaceDataType, typename ParameterType>
  void release(TrackingLineMinimizer<SpaceDataType,ParameterType>& TLM) {
    if(TLM.state==Allocated)  safe_delete(TLM.TrackingFac);
    else TLM.TrackingFac=NULL;
    release(static_cast<LineMinimizerBase<SpaceDataType,ParameterType>&>(TLM));
  }

  template <typename SpaceDataType, typename ParameterType>
  void assign(TrackingLineMinimizer<SpaceDataType,ParameterType>& dest,
              const TrackingLineMinimizer<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(dest));
    assert(IsAvailable(src));
    typedef LineMinimizerBase<SpaceDataType,ParameterType> PType;
    assign(static_cast<PType&>(dest),static_cast<const PType&>(src));
    *(dest.TrackingFac)=*(src.TrackingFac);
  }

  template <typename SpaceDataType, typename ParameterType>
  void allocate(TrackingLineMinimizer<SpaceDataType,ParameterType>& TLM) {
    release(TLM);
    TLM.TrackingFac=new double;
    typedef LineMinimizerBase<SpaceDataType,ParameterType> PType;
    allocate(static_cast<PType&>(TLM));
  }

  template <typename SpaceDataType, typename ParameterType>
  void refer(TrackingLineMinimizer<SpaceDataType,ParameterType>& dest,
             const TrackingLineMinimizer<SpaceDataType,ParameterType>& src) {
    assert(IsAvailable(src));
    release(dest);
    dest.TrackingFac=src.TrackingFac;
    typedef LineMinimizerBase<SpaceDataType,ParameterType> PType;
    refer(static_cast<PType&>(dest),static_cast<const PType&>(src));
  }

}

#endif

