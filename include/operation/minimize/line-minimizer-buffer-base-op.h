
#ifndef _Line_Minimizer_Buffer_Base_Operation_H_
#define _Line_Minimizer_Buffer_Base_Operation_H_

#include "data/minimizer/line-minimizer-buffer-base.h"
#include "operation/minimize/minimizer-buffer-base-op.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            typename PmType, typename T>
  void initMinimizerLocation(LineMinimizerBufferBase<IType,SpType,PmType,T>& B,
                             const SpType<T>& Coor,
                             const PmType& Pmx) {
    typedef MinimizerBufferBase<IType,SpType,PmType,T>  MBType;
    initMinimizerLocation(static_cast<MBType&>(B),Coor,Pmx);
    imprint(B.RunX,Coor);
    imprint(B.RunG,Coor);  
  }

}

#endif
