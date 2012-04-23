
#ifndef _System_Evolute_Mode_VelVerlet_ConstE_H_
#define _System_Evolute_Mode_VelVerlet_ConstE_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"
#include "system/evaluate/gradient.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeVelVerletConstE(
      CT<T>& C,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >& SI,
      Array1D<SystemPropagator<T,CT> > SP,
      const Array1D<Array1D<unsigned int> >&) {
    for(unsigned int i=0;i<SP.Size();++i)
      SP[i]._Propagate(VelVerletConstEBeforeG);
    EvaluateGradient(C,SI);
    for(unsigned int i=0;i<SP.Size();++i)
      SP[i]._Propagate(VelVerletConstEAfterG);
  }

}

#endif

