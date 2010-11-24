
#ifndef _Minimize_H_
#define _Minimize_H_

#include "data/minimizer/tracking-line-minimizer-buffer.h"

namespace std {

  template <unsigned int CType,
            typename IType,template<typename> class SpType,
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
      GenerateNewLocation(B,B.MinX,Dirc,step,B.RunX,B.RunE(),B.RunG,
                          B.RunPrj());
      if(Condition<CType>(B.RunE(),B.RunPrj(),B.MinEnergy(),c1pj,c2pj,step)) {
        swap(B.MinX,B.RunX);
        swap(B.MinG,B.MinG);
        B.MinEnergy()=B.RunE();
        B.MinProject()=B.RunPrj();
        B.MinMove()=step;
        return 1;
      }
      if((dstep>0)&&(B.RunPrj()>0.))  dstep*=-B.TrackingFac();
      else if((dstep<0.)&&(B.RunPrj()<0))   dstep*=-B.TrackingFac();
      step+=dstep;
    } while(absval(dstep)>mstep);
    return 2;
  }

}

#endif
