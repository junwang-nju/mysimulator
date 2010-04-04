
#ifndef _Minimizer_LBFGS_Base_H_
#define _Minimizer_LBFGS_Base_H_

#include "fix-vector.h"
#include "var-vector.h"

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

      fixVector<RunSpaceVecType,MaxCorr>  dX;
      fixVector<RunSpaceVecType,MaxCorr>  dG;
      fixVector<double,MaxCorr>           alpha;
      fixVector<double,MaxCorr>           rho;
      RunSpaceVecType                     lastX;
      RunSpaceVecType                     lastG;
      unsigned int                        nCorr;
      double                              diag;
      double                              dgdg;
      double                              dgdx;
      double                              beta;

    public:

      LBFGSbMinimizerBase()
        : ParentType(),dX(), dG(), alpha(), rho(), lastX(), lastG(), 
          nCorr(0), diag(0.), dgdg(0.), dgdx(0.), beta(0.) {}

      LBFGSbMinimizerBase(const Type& LM) {
        myError("Cannot create from LBFGS-b Minimizer Base");
      }

      Type& operator=(const Type& LM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(LM));
        dX=LM.dX;
        dG=LM.dG;
        alpha=LM.alpha;
        rho=LM.rho;
        lastX=LM.lastX;
        lastG=LM.lastG;
        nCorr=LM.nCorr;
        diag=LM.diag;
        dgdg=LM.dgdg;
        dgdx=LM.dgdx;
        beta=LM.beta;
        return *this;
      }

      int Go(const unsigned int MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        this->MinLineCount=0;
        int point=0;
        diag=1.;
        this->Dirc=this->MinGradSeq;
        this->Dirc.scale(-diag.);
        dX[point]=this->Dirc;
        this->MinLineCount=MaxIter;
        return 0;
      }

  };

  template <typename LineMinMethod, unsigned int MaxCorr=6U>
  const unsigned int
  LBFGSbMinimizerBase<LineMinMethod,MaxCorr>::DefaultMaxIter=1000;

}

#endif

