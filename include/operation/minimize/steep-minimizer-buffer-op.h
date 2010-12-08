
#ifndef _Minimizer_Steepest_Descent_Buffer_Operation_H_
#define _Minimizer_Steepest_Descent_Buffer_Operation_H_

#include "data/minimizer/steep-minimizer-buffer.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            typename PmType, typename T,
            template <typename,template <typename> class,
                      typename, typename> class LineMin>
  void initMinimizerLocation(
      SteepestDescentMinimizerBuffer<IType,SpType,PmType,T,LineMin>& M,
      const SpType<T>& Coor, const PmType& Pmx) {
    typedef LineMin<IType,SpType,PmType,T>  LMType;
    initMinimizerLocation(static_cast<LMType&>(M),Coor,Pmx);
    imprint(M.Dirc,Coor);
  }

}

#endif
