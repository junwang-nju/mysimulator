
#ifndef _Minimize_H_
#define _Minimize_H_

#include "data/minimizer/tracking-line-minimizer-buffer.h"
#include "operation/minimize/minimizer-buffer-base-op.h"
#include "operation/minimize/condition.h"

namespace std {

  template <unsigned int CType,
            typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T>
  int Minimize(TrackingLineMinimizerBuffer<IType,SpType,IdType,T>& B,
               const SpType<T>& Dirc) {
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
      ProduceNewLocation(B,B.MinX,Dirc,step,B.RunX,B.RunE(),B.RunG,
                         B.RunPrj());
      if(Condition<CType>(B.RunE(),B.RunPrj(),B.MinEnergy(),c1pj,c2pj,step)) {
        swap(B.MinX,B.RunX);
        swap(B.MinG,B.RunG);
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

#include "data/minimizer/steep-minimizer-buffer.h"

namespace std {

  template <unsigned int CondType,
            typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template <typename,template <typename> class,
                      template <typename> class, typename> class LineMin>
  int Minimize(
        SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& B,
        const unsigned int MaxIter=
          SteepestDescentMinimizerBuffer<IType,SpType,
                                         IdType,T,LineMin>::DefaultMaxIter) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    B.GCalcCount()=0;
    B.LSearchCount()=0;
    T tmd;
    for(unsigned int neval=0;neval<MaxIter;++neval) {
      copy(B.Dirc,B.MinG);
      tmd=norm(B.Dirc);
      if(tmd<B.GradThreshold()) {
        B.LSearchCount()=neval;
        return 3;
      }
      scale(B.Dirc,-1./tmd);
      B.MinProject()=-tmd;
      tmd=B.MinEnergy();
      if(Minimize<CondType>(static_cast<LMType&>(B),B.Dirc)==2) {
        B.LSearchCount()=neval;
        return 1;
      }
      if(2*absval(tmd-B.MinEnergy())<=(tmd+B.MinEnergy())*RelDelta<T>()) {
        B.LSearchCount()=neval;
        return 2;
      }
    }
    B.LSearchCount()=MaxIter;
    return 0;
  }

}

#endif
