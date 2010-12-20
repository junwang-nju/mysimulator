
#ifndef _Minimizer_Buffer_Base_Operation_H_
#define _Minimizer_Buffer_Base_Operation_H_

#include "data/minimizer/minimizer-buffer-base.h"
#include "operation/basic/vector-op.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            typename PmType,typename T>
  void initMinimizerMask(MinimizerBufferBase<IType,SpType,PmType,T>& B,
                         const SpType<unsigned int>& Mask,
                         const SpType<T>& dMask) {
    imprint(B.MinIMask,Mask);
    imprint(B.MinDMask,dMask);
    copy(B.MinIMask,Mask);
    copy(B.MinDMask,dMask);
    B.DOF()=asum(Mask);
  }

  template <typename IType,template <typename> class SpType,
            typename PmType,typename T>
  void initMinimizerLocation(MinimizerBufferBase<IType,SpType,PmType,T>& B,
                             const SpType<T>& Coor,
                             const PmType& Pmx) {
    imprint(B.MinX,Coor);
    imprint(B.MinG,Coor);
    imprint(B.MinParam,Pmx);
    copy(B.MinX,Coor);
    copy(B.MinParam,Pmx);
    assert(IsAvailable(B.MinProperty));
    CalcInteraction(B.F,Coor,Pmx,B.MinEnergy(),B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            typename PmType,typename T,typename sT>
  void ProduceNewLocation(
      MinimizerBufferBase<IType,SpType,PmType,T>& B,
      const SpType<T>& Origin, const SpType<T>& Dirc, const sT& step,
      SpType<T>& Dest, T& DestY, SpType<T>& DestG, T& DestPrj) {
    copy(Dest,Origin);
    shift(Dest,step,B.MinDMask,Dirc);
    B.F.B.renew();
    DestY=0.;
    copy(DestG,0.);
    CalcInteraction(B.F,Dest,B.MinParam,DestY,DestG);
    ++(B.GCalcCount());
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

