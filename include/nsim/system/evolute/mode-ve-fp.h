
#ifndef _System_Evolute_Mode_VelVerletConstE_FixPosition_H_
#define _System_Evolute_Mode_VelVerletConstE_FixPosition_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"
#include "system/evaluate/gradient.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeVelVerletCEFP(
      CT<T>& C,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >& SI,
      Array1D<SystemPropagator<T,CT> >& SP,
      const Array1D<Array1D<unsigned int> >& GrpMap) {
    Array1D<unsigned int> V;
    V.Refer(const_cast<Array1D<unsigned int>&>(GrpMap[SystemConstEVelVerlet]));
    for(unsigned int i=0;i<V.Size();++i)
      SP[V[i]]._Propagate(VelVerletConstEBeforeG);
    EvaluateGradient(C,SI);
    for(unsigned int i=0;i<V.Size();++i)
      SP[V[i]]._Propagate(VelVerletConstEAfterG);
    V.Clear();
  }

}

#endif

