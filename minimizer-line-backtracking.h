
#ifndef _Minimizer_Line_BackTracking_H_
#define _Minimizer_Line_BackTracking_H_

namespace std {

  template <typename LineMinBase, uint CondType=StrongWolfe>
  class BacktrackingLineMinimizer : public LineMinBase {
    public:
      typedef BacktrackingLineMinimizer<LineMinBase,CondType> Type;
      typedef LineMinBase                                     ParentType;
      typedef typename LineMinBase::SpaceType                 SpaceType;

    private:
      double BacktrackFac;

    public:
      BacktrackingLineMinimizer() : ParentType(), BacktrackFac(Gold) {}
      void SetBacktrackingFactor(const double& bfac) { BacktrackFac=bfac; }
      int Go(SpaceType& Dirc) {
        assert(this->MinPrj<=0);
        if(this->MinPrj>=-this->GradThreshold)  return 2;
        const double minstep=MinStep(this->MinCoor,Dirc);
        double step=this->MinScale;
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
          step*=BacktrackFac;
        } while(step>minstep);
        return 2;
      }
  };

}

#endif

