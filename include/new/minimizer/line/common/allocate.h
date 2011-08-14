
#ifndef _Minimizer_Line_Common_Allocate_H_
#define _Minimizer_Line_Common_Allocate_H_

#include "minimizer/line/common/interface.h"
#include "minimizer/base/allocate.h"

namespace mysimulator {

  template <typename T,typename FT,typename IDT,typename PT,typename GT,
            template<typename> class ST>
  void allocate(LineMinimizerCommon<T,FT,IDT,PT,GT,ST>& M,
                const System<T,FT,IDT,PT,GT,ST>& S) {
    assert(IsValid(S));
    release(M);
    typedef typename LineMinimizerCommon<T,FT,IDT,PT,GT,ST>::ParentType  Type;
    allocate(static_cast<Type&>(M),S);
    imprint(M.RunX,M.Sys().X);
    imprint(M.RunG,M.Sys().X);
    imprint(M.LineDirc,M.Sys().X);
  }

}

#endif

