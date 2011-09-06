
#ifndef _Minimizer_Conjg_Allocate_Specification_H_
#define _Minimizer_COnjg_Allocate_Specification_H_

#include "minimizer/interface.h"
#include "minimizer/line/allocate.h"

namespace mysimulator {

  template <LineMinimizerName LMN, typename T, typename FT, typename IDT,
            typename PT, typename GT, template <typename> class ST>
  void allocate(Minimizer<ConjugateGradient,LMN,T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    typedef
      typename Minimizer<ConjugateGradient,LMN,T,FT,IDT,PT,GT,ST>::ParentType
      Type;
    allocate(static_cast<Type&>(M),S);
    imprint(M.OldMinG,M.Sys().X);
  }

}

#endif

