
#ifndef _Minimizer_SteepestDescent_Base_H_
#define _Minimizer_SteepestDescent_Base_H_

#include "constant.h"

namespace std {

  template <typename LineMinMethod>
  class SteepestDescentMinimizerBase : public LineMinMethod {

    public:

      typedef SteepestDescentMinimizerBase<LineMinMethod>   Type;
      typedef LineMinMethod   ParentType;
      typedef typename LineMinMethod::RunSpaceVecType RunSpaceVecType;
      typedef typename ParentType::ParamType  ParamType;

      static const unsigned int DefaultMaxIter;

    protected:

      RunSpaceVecType Dirc;

    public:

      SteepestDescentMinimizerBase() : ParentType(), Dirc() {}

      SteepestDescentMinimizerBase(const Type& SDM) {
        myError("Cannot create from steepest-descent minimizer");
      }

      Type& operator=(const Type& SDM) {
        static_cast<ParentType*>(this)->operator=(
            static_cast<const ParentType&>(SDM));
        return *this;
      }

      int Go(const unsigned int MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        this->MinLineCount=0;
        double tmd;
        for(unsigned int neval=0;neval<MaxIter;++neval) {
          Dirc=this->MinGradSeq;
          tmd=norm(Dirc);
          if(tmd<this->GradThreshold) { this->MinLineCount=neval; return 3; }
          Dirc.scale(-1./tmd);
          this->MinPrj=-tmd;
          tmd=this->MinE;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2) {
            this->MinLineCount=neval;
            return 1;
          }
          if(2.0*(tmd-this->MinE)<=(tmd+this->MinE)*DRelDelta) {
            this->MinLineCount=neval;
            return 2;
          }
        }
        this->MinLineCount=MaxIter;
        return 0;
      }

  };

  template <typename LineMinMethod>
  const unsigned int
  SteepestDescentMinimizerBase<LineMinMethod>::DefaultMaxIter=10000;

}

#endif

