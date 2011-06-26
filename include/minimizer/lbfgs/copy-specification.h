
#ifndef _Minimizer_LBFGS_Copy_Specification_H_
#define _Minimizer_LBFGS_Copy_Specification_H_

#include "minimizer/lbfgs/specification.h"
#include "vector/copy.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void copy(Minimizer<LBFGS,LMN,KT,VT,PT,T>& M,
            const Minimizer<LBFGS,LMN,KT,VT,PT,T>& cM) {
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    copy(static_cast<Type&>(M),static_cast<const Type&>(cM));
    copy(M.dX,cM.dX);
    copy(M.dG,cM.dG);
    copy(M.alpha,cM.alpha);
    copy(M.rho,cM.rho);
    copy(M.lastX,cM.lastX);
    copy(M.lastG,cM.lastG);
  }

}

#endif

