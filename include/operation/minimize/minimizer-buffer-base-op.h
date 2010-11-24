
#ifndef _Minimizer_Buffer_Base_Operation_H_
#define _Minimizer_Buffer_Base_Operation_H_

#include "data/minimizer/minimizer-buffer-base.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType,typename T>
  void initMinimizerMask(MinimizerBufferBase<IType,SpType,IdType,T>& B,
                         const SpType<unsigned int>& Mask) {
    copy(B.MinIMask,Mask);
    copy(B.MinDMask,Mask);
    B.DOF()=asum(Mask);
  }

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType,typename T>
  void initMinimizerLocation(MinimizerBufferBase<IType,SpType,IdType,T>& B,
                             const SpType<T>& Coor,
                             const IdType<unsigned int>& Idx) {
    imprint(B.MinX,Coor);
    imprint(B.MinG,Coor);
    copy(B.MinX,Coor);
    assert(IsAvailable(B.MinProperty));
    CalcInteraction(B.F,Coor,Idx,B.MinEnergy(),B.MinG);
  }

}

#endif
