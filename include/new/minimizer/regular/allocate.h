
#ifndef _Minimizer_Regular_Allocate_H_
#define _Minimizer_Regular_Allocate_H_

#include "minimizer/regular/interface.h"
#include "minimizer/allocate.h"

namespace mysimulator {

  template <MinimizerName MN, LineMinimizerName LMN, typename T,typename FT,
            typename IDT,typename PT,typename GT>
  void allocate(MinimizerRegular<MN,LMN,T,FT,IDT,PT,GT>& M,
                const System<T,FT,IDT,PT,GT,Array2D>& S) {
    typedef typename MinimizerRegular<MN,LMN,T,FT,IDT,PT,GT>::ParentType Type;
    allocate(static_cast<Type&>(M),S);
  }

}

#endif

