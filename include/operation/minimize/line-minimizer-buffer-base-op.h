
#ifndef _Line_Minimizer_Buffer_Base_Operation_H_
#define _Line_Minimizer_Buffer_Base_Operation_H_

#include "data/minimizer/line-minimizer-buffer-base.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T>
  void initMinimizerLocation(LineMinimizerBufferBase<IType,SpType,IdType,T>& B,
                             const SpType<T>& Coor,
                             const IdType<unsigned int>& Idx) {
    typedef MinimizerBufferBase<IType,SpType,IdType,T>  MBType;
    initMinimizerLocation(static_cast<MBType&>(B),Coor,Idx);
    imprint(B.RunX,Coor);
    imprint(B.RunG,Coor);  
  }

}

#endif
