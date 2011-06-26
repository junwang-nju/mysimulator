
#ifndef _Minimizer_Base_Produce_H_
#define _Minimizer_Base_Produce_H_

#include "minimizer/base/interface.h"

namespace mysimulator {

  template <typename KT,template<typename> class VT,typename PT,typename T,
            typename fT>
  void ProduceNew(MinimizerBase<KT,VT,PT,T>& M,
                  const VT<T>& Origin, const VT<T>& Dirc, const fT& step,
                  VT<T>& Dest, T& DestE, VT<T>& DestG, T& DestPrj) {
    assert(IsValid(M));
    copy(Dest,Origin);
    shift(Dest,step,M.MinMask,Dirc);
    M.MinFunc.update();
    DestE=0.;
    fill(DestG,0.);
    Calc(M.MinFunc,Dest,M.MinP,DestE,DestG);
    ++(M.GCalcCount);
    DestPrj=dot(DestG,Dirc);
  }

}

#endif

