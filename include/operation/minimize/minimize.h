
#ifndef _Minimize_H_
#define _Minimize_H_

#include "data/minimizer/tracking-line-minimizer-buffer.h"

namespace std {

  template <typename IType,typename SpType,typename IdType,typename T>
  void Minimize(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
                const SpType& Dirc) {
    assert(IsAvailable(B));
    assert(IsAvailable(Dirc));
    assert(B.MinProject()<=0);
    if(B.MinProject()>=-B.GradThreshold())  return 2;
    const double mstep=MinimalStep(xxxx);
  }

}

#endif
