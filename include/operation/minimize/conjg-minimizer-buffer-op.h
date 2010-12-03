
#ifndef _Minimizer_Conjugate_Gradient_Buffer_Operation_H_
#define _Minimizer_Conjugate_Gradient_Buffer_Operation_H_

#include "data/minimizer/conjg-minimizer-buffer.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            typename IdType, typename T,
            template<typename,template<typename>class,
                     typename,typename> class LineMin>
  void initMinimizerLocation(
      ConjugateGradientMinimizerBuffer<IType,SpType,IdType,T,LineMin>& B,
      const SpType<T>& Coor, const IdType& Idx) {
    typedef LineMin<IType,SpType,IdType,T>  LMType;
    initMinimizerLocation(static_cast<LMType&>(B),Coor,Idx);
    imprint(B.Dirc,Coor);
    imprint(B.OldMinG,Coor);
  }

}

#endif
