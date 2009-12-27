
#ifndef _Minimizer_Line_Tracking_H_
#define _Minimizer_Line_Tracking_H_

namespace std {

  template <typename LineMinBase, uint CondType=StrongWolfe>
  class TrackingLineMinimizer : public LineMinBase {
    public:
      typedef TrackingLineMinimizer<LineMinBase,CondType>     Type;
      typedef LineMinBase                                     ParentType;
      typedef typename LineMinBase::RunSpaceType              RunSpaceType;

    private:
      double TrackFac;

    public:
      TrackingLineMinimizer() : ParentType(), TrackFac(Gold) {}
      void SetTrackingFactor(const double& bfac) { TrackFac=bfac; }
      int Go(RunSpaceType& Dirc) {
        assert(this->MinPrj<=0);
        if(this->MinPrj>=-this->GradThreshold)  return 2;
        const double minstep=MinStep(this->MinCoor,Dirc);
        double dstep=this->MinScale,step=dstep;
        double c1pj=this->DecreaseFac*this->MinPrj;
        double c2pj=this->CurvatureFac*this->MinPrj;
        do {
          Propagate(this->MinCoor,Dirc,step,
                    this->RunCoor,this->RunY,this->RunGrad,this->RunPrj);
          if(Condition<CondType>(this->RunY,this->RunPrj,this->MinY,
                                 c1pj,c2pj,step)) {
            swap(this->MinCoor,this->RunCoor);
            this->MinY=this->RunY;
            swap(this->MinGrad,this->RunGrad);
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

