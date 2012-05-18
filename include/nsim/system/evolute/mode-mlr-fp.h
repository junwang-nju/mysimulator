
#ifndef _System_Evolute_Mode_MinimizerLineRegular_FixPosition_H_
#define _System_Evolute_Mode_MinimizerLineRegular_FixPosition_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"
#include "system/evaluate/both.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeMinimizerLRFP(
      CT<T>& C,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >& SI,
      Array1D<SystemPropagator<T,CT> >& SP,
      const Array1D<Array1D<unsigned int> >& GrpMap) {
    Array1D<unsigned int> V;
    V.Refer(
        const_cast<Array1D<unsigned int>&>(GrpMap[SystemMinimizerLineRegular]));
    for(unsigned int i=0;i<V.Size();++i)
      SP[V[i]]._Propagate(MinimizerLineRegularShift);
    for(unsigned int i=0;i<SI.Size();++i) ClearFlag(SI[i].Buffer);
    EvaluateBoth(C,SI);
  }

}

#endif

