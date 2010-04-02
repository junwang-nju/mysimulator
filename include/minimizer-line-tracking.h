
#ifndef _Minimizer_Line_Tracking_H_
#define _Minimizer_Line_Tracking_H_

#include "minimizer-condition.h"
#include "constant.h"

namespace std {

  template <typename LineMinBase, unsigned int CondType>
  class TrackingLineMinimizer : public LineMinBase {

    public:

      typedef TrackingLineMinimizer<LineMinBase,CondType>   Type;
      typedef LineMinBase   ParentType;
      typedef typename LineMinBase::RunSpaceVecType RunSpaceVecType;

    private:

      double TrackFac;

    public:

      TrackingLineMinimizer() : ParentType(), TrackFac(Gold) {}

      TrackingLineMinimizer(const Type& TLM) {
        myError("Cannot create from line minimizer with tracking method");
      }

      Type& operator=(const Type& TLM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(TLM));
        TrackFac=TLM.TrackFac;
        return *this;
      }

      void SetTrackingFactor(const double tfac) { TrackFac=tfac; }

      int Go(RunSpaceVecType& Dirc) {
        assert(this->MinPrj<=0);
        if(this->MinPrj>=-this->GradThreshold)  return 2;
        const double minstep=this->MinStep(this->MinCoorSeq,Dirc);
        double dstep=this->MinScale, step=dstep;
        double c1pj=this->DecreaseFac*this->MinPrj;
        double c2pj=this->CurvatureFac*this->MinPrj;
        do {
          Propagate(this->MinCoorSeq,Dirc,step,
                    this->RunCoor,this->RunE,this->RunGrad,this->RunPrj);
          if(Condition<CondType>(this->RunE,this->RunPrj,this->MinE,
                                 c1pj,c2pj,step)) {
            this->MinCoorSeq.swap(this->RunCoor);
            this->MinGradSeq.swap(this->RunGrad);
            this->MinE=this->RunE;
            this->MinPrj=this->RunPrj;
            this->MinMove=step;
            return 1;
          }
          if((dstep>0)&&(this->RunPrj>0))       dstep*=-TrackFac;
          else if((dstep<0)&&(this->RunPrj<0))  dstep*=-TrackFac;
          step+=dstep;
        } while(fabs(dstep)>minstep);
        return 2;
      }

  };

}

#endif

