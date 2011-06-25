
#ifndef _Minimizer_SteepestDescent_Copy_Specification_H_
#define _Minimizer_SteepestDescent_Copy_Specification_H_

#include "minimizer/steep/specification.h"
#include "minimizer/line/copy.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename KT, template<typename> class VT,
            typename PT, typename T>
  void copy(Minimizer<SteepestDescent,LMN,KT,VT,PT,T>& M,
            const Minimizer<SteepestDescent,LMN,KT,VT,PT,T>& cM) {
    assert(IsValid(M)&&IsValid(cM));
    typedef LineMinimizer<LMN,KT,VT,PT,T>   Type;
    copy(static_cast<Type&>(M),static_cast<const Type&>(cM));
  }

}

#endif

