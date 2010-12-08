
#ifndef _Minimizer_Conjugate_Gradient_Buffer_Operation_H_
#define _Minimizer_Conjugate_Gradient_Buffer_Operation_H_

#include "data/minimizer/conjg-minimizer-buffer.h"

namespace std {

  template <typename IType,template <typename> class SpType,
            typename PmType, typename T,
            template<typename,template<typename>class,
                     typename,typename> class LineMin>
  void initMinimizerLocation(
      ConjugateGradientMinimizerBuffer<IType,SpType,PmType,T,LineMin>& B,
      const SpType<T>& Coor, const PmType& Pmx) {
    typedef LineMin<IType,SpType,PmType,T>  LMType;
    initMinimizerLocation(static_cast<LMType&>(B),Coor,Pmx);
    imprint(B.Dirc,Coor);
    imprint(B.OldMinG,Coor);
  }

}

#endif
