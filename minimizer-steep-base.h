
#ifndef _Minimizer_Steepest_Descent_H_
#define _Minimizer_Steepest_Descent_H_

#include "minimizer-line-base.h"

namespace std {

  template <typename LineMinMethod>
  class SteepestDescentMinimizerBase : public LineMinMethod {

    public:
      typedef SteepestDescentMinimizerBase<LineMinMethod>       Type;
      typedef LineMinMethod                                     ParentType;
      typedef typename LineMinMethod::RunSpaceType              RunSpaceType;

      static const uint DefaultMaxIter;

    protected:
      RunSpaceType Dirc;

    public:
      SteepestDescentMinimizerBase() : ParentType(), Dirc() {}
      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        this->MinLineCount=0;
        double tmd;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          Dirc=this->MinGrad;
          tmd=norm(Dirc);
          if(tmd<this->GradThreshold) { this->MinLineCount=nEval; return 3; }
          Dirc*=-1./tmd;
          this->MinPrj=-tmd;
          tmd=this->MinY;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2)       {
            this->MinLineCount=nEval;
            return 1;
          }
          if(2.0*(tmd-this->MinY)<=(tmd+this->MinY)*DRelDelta)  {
            this->MinLineCount=nEval;
            return 2;
          }
        }
        this->MinLineCount=MaxIter;
        return 0;
      }

  };

  template <typename LineMinMethod>
  const uint SteepestDescentMinimizerBase<LineMinMethod>::DefaultMaxIter
      =10000;
}

#endif

