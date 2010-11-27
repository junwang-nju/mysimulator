
#ifndef _Minimizer_Steepest_Descent_Buffer_Operation_H_
#define _Minimizer_Steepest_Descent_Buffer_Operation_H_

#include "data/minimizer/steep-minimizer-buffer.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            template <typename> class IdType, typename T,
            template <typename,template <typename> class,
                      template <typename> class, typename> class LineMin>
  void initMinimizerLocation(
      SteepestDescentMinimizerBuffer<IType,SpType,IdType,T,LineMin>& M,
      const SpType<T>& Coor, const IdType<unsigned int>& Idx) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    initMinimizerLocation(static_cast<LMType&>(M),Coor,Idx);
    imprint(M.Dirc,Coor);
  }

}

#endif
