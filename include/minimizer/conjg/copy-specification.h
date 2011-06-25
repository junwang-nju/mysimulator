
#ifndef _Minimizer_ConjugateGradient_Copy_Specification_H_
#define _Minimizer_ConjugateGradient_Copy_Specification_H_

#include "minimizer/conjg/specification.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void copy(Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>& M,
            const Minimizer<ConjugateGradient,LMN,KT,VT,PT,T>& cM) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    copy(static_cast<Type&>(M),static_cast<const Type&>(cM));
    copy(M.OldMinG,cM.OldMinG);
    copy(M.MaxBeta,cM.MaxBeta);
  }

}

#endif

