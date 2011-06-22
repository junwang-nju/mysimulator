
#ifndef _Minimizer_Base_Copy_H_
#define _Minimizer_Base_Copy_H_

#include "minimizer/base/interface.h"
#include "minimizer/data-base/copy.h"

namespace mysimulator {

  template <typename FT,template<typename> class VT, typename PT, typename T>
  void copy(MinimizerBase<FT,VT,PT,T>& M,const MinimizerBase<FT,VT,PT,T>& cM){
    assert(IsValid(M)&&IsValid(cM));
    copy(M.Data,cM.Data);
  }

}

#endif

