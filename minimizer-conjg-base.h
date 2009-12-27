
#ifndef _Minimizer_Conjugate_Gradient_H_
#define _Minimizer_Conjugate_Gradient_H_

namespace std {
  
  template <typename LineMinMethod>
  class ConjugateGradientMinimizerBase : public LineMinMethod {
    public:
      typedef ConjugateGradientMinimizerBase<LineMinMethod>     Type;
      typedef LineMinMethod                                     ParentType;
      typedef typename LineMinMethod::RunSpaceType              RunSpaceType;
      
      static const uint DefaultMaxIter;
      
    protected:
      RunSpaceType Dirc;
      RunSpaceType OldMinGrad;
      double MaxBeta;
      
    public:
      ConjugateGradientMinimizerBase()
        : ParentType(), Dirc(), OldMinGrad(), MaxBeta(5.) {}
      void SetMaxBetaFactor(const double& mb) { MaxBeta=mb; }
      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        bool isSteep=true,nextMode;
        double beta=0.;
        double fnorm,fnorm2;
        fnorm=norm(this->MinGrad);
        fnorm2=fnorm*fnorm;
        if(fnorm<this->GradThreshold)  return 3;
        double tmd,oldfnorm2;
        for(uint neval=0;neval<MaxIter;++neval)
        {
          if(!isSteep) {
            oldfnorm2=fnorm2;
            fnorm=norm(this->MinGrad);
            fnorm2=fnorm*fnorm;
            tmd=dot(this->MinGrad,OldMinGrad);
            beta=(fnorm2-tmd)/oldfnorm2;
            if(fabs(beta)>MaxBeta) {
              beta=0.;
              isSteep=true;
            } else  isSteep=false;
          }
          if(!isSteep) {
            Dirc.scaleshift(beta,-1.,this->MinGrad);
            this->MinPrj*=beta;
            tmd=sqrt(beta*beta+fnorm2-2*this->MinPrj);
            this->MinPrj-=fnorm2;
            if((this->MinPrj>0.)||(tmd<this->GradThreshold)) {
              beta=0.;
              isSteep=true;
            }
          }
          if(isSteep) {
            Dirc=this->MinGrad;
            Dirc*=-1.;
            this->MinPrj=-fnorm2;
            tmd=fnorm;
            if(tmd<this->GradThreshold)   return 4;
          }
          tmd=1./tmd;
          Dirc*=tmd;
          this->MinPrj*=tmd;
          OldMinGrad=this->MinGrad;
          tmd=this->MinY;
          nextMode=false;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2) {
            if(isSteep)   return 1;
            else          { nextMode=true; --neval; }
          }
          if(2.0*(tmd-this->MinY)<=(tmd+this->Y)*DRelDelta) {
            if(isSteep)   return 2;
            else          { nextMode=true; --neval; }
          }
          isSteep=nextMode;
        }
        return 0;
      }
      
  };
  
  template <typename LineMinMethod>
  const uint ConjugateGradientMinimizerBase<LineMinMethod>::DefaultMaxIter
      =1000;

}

#endif
