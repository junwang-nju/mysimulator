
#ifndef _Minimizer_Buffer_Base_Operation_H_
#define _Minimizer_Buffer_Base_Operation_H_

#include "data/minimizer/minimizer-buffer-base.h"
#include "operation/basic/vector-op.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType,typename T>
  void initMinimizerMask(MinimizerBufferBase<IType,SpType,IdType,T>& B,
                         const SpType<unsigned int>& Mask,
                         const SpType<T>& dMask) {
    imprint(B.MinIMask,Mask);
    imprint(B.MinDMask,dMask);
    copy(B.MinIMask,Mask);
    copy(B.MinDMask,dMask);
    B.DOF()=asum(Mask);
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType,typename T>
  void initMinimizerLocation(MinimizerBufferBase<IType,SpType,IdType,T>& B,
                             const SpType<T>& Coor,
                             const IdType<unsigned int>& Idx) {
    imprint(B.MinX,Coor);
    imprint(B.MinG,Coor);
    imprint(B.MinIdx,Idx);
    copy(B.MinX,Coor);
    copy(B.MinIdx,Idx);
    assert(IsAvailable(B.MinProperty));
    CalcInteraction(B.F,Coor,Idx,B.MinEnergy(),B.MinG);
  }

  template <typename IType,template<typename> class SpType,
            template<typename> class IdType,typename T,typename sT>
  void ProduceNewLocation(
      MinimizerBufferBase<IType,SpType,IdType,T>& B,
      const SpType<T>& Origin, const SpType<T>& Dirc, const sT& step,
      SpType<T>& Dest, T& DestY, SpType<T>& DestG, T& DestPrj) {
    copy(Dest,Origin);
    shift(Dest,step,B.MinDMask,Dirc);
    DestY=0.;
    copy(DestG,0.);
    CalcInteraction(B.F,Dest,B.MinIdx,DestY,DestG);
    ++(B.GCalcCount());
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

