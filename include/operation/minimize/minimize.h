
#ifndef _Minimize_H_
#define _Minimize_H_

#include "data/minimizer/tracking-line-minimizer-buffer.h"

namespace std {

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  void Minimize(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
                const SpType& Dirc) {
    assert(IsAvailable(B));
    assert(IsAvailable(Dirc));
    assert(B.MinProject()<=0);
    if(B.MinProject()>=-B.GradThreshold())  return 2;
    const T mstep=MinimalStep(B,B.MinX,Dirc);
    T dstep=B.SearchScale();
    T step=dstep;
    T c1pj=B.DecFac()*B.MinProject();
    T c2pj=B.CurvFac()*B.MinProject();
    do {
      GenerateNewLocation(B,B.MinX,Dirc,step,B.RunX,B.RunY(),B.RunG,
                          B.RunPrj());
      xxx
    } while(absval(dstep)>mstep);
  }

}

#endif
