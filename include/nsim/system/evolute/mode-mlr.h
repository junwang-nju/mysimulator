
#ifndef _System_Evolute_Mode_Minimizer_LineRegular_H_
#define _System_Evolute_Mode_Minimizer_LineRegular_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"
#include "system/evaluate/both.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeMinimizerLineRegular(
      CT<T>& C,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >& SI,
      Array1D<SystemPropagator<T,CT> >& SP,
      const Array1D<Array1D<unsigned int> >&) {
    for(unsigned int i=0;i<SP.Size();++i)
      SP[i]._Propagate(MinimizerLineRegularShift);
    EvaluateBoth(C,SI);
  }

}

#endif

