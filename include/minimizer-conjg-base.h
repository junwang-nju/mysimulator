
#ifndef _Minimizer_Conjugate_Gradient_Base_H_
#define _Minimizer_Conjugate_Gradient_Base_H_

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
        for(unsigned int neval=0;neval=MaxIter;++neval) {
          if(!isSteep) {
            oldfnorm2=fnorm2;
            fnorm=norm(this->MinGradSeq);
            fnorm2=fnorm*fnorm;
            tmd=dot(this->MinGradSeq,OldMinGrad);
          }
        }
      }

  };

}

#endif

