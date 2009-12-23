
#ifndef _Minimizer_Steepest_Descent_H_
#define _Minimizer_Steepest_Descent_H_

#include "minimizer-line-base.h"

namespace std {

  template <typename SpaceType, typename ParameterType,
            template <typename,typename,uint>
            class LineBase=BacktrackingLineMinimizer,
            uint CondType=StrongWolfe>
  class SteepestDescentMinimizerBase
    : public LineBase<SpaceType,ParameterType,CondType> {

    public:
      typedef SteepestDescentMinimizerBase<SpaceType,ParameterType,LineBase,
                                           CondType>      Type;
      typedef LineBase<SpaceType,ParameterType,CondType>  ParentType;

      static const uint DefaultMaxIter;

    private:
      SpaceType Dirc;

    public:
      SteepestDescentMinimizerBase() : ParentType(), Dirc() {}
      int Go(const uint& MaxIter=DefaultMaxIter) {
        this->MinGCount=0;
        uint MinStatus=0;
        double tmd;
        for(uint nEval=0;nEval<MaxIter;++nEval) {
          Dirc=this->MinGrad;
          tmd=norm(Dirc);
          if(tmd<this->GradThreshold) return 3;
          Dirc*=-1./tmd;
          this->MinPrj=-tmd;
          tmd=this->MinY;
          if(static_cast<ParentType*>(this)->Go(Dirc)==2)       return 1;
          if(2.0*(tmd-this->MinY)<=(tmd+this->MinY)*DRelDelta)  return 2;
        }
        return 0;
      }

  };

  template <typename SpaceType, typename ParameterType,
            template <typename,typename,uint> class LineBase, uint CondType>
  const uint SteepestDescentMinimizerBase<SpaceType,ParameterType,
                                          LineBase,CondType>::DefaultMaxIter
      =10000;
}

#endif

