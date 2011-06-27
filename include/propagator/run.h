
#ifndef _Propagator_Run_H_
#define _Propagator_Run_H_

#include "propagator/interface.h"
#include "propagator/move/vverlet/step.h"

namespace mysimulator {

  template <typename T, template<typename> class DBuffer, typename GeomType,
            typename IFType, typename IPType>
  void Run(Propagator<T>& P, InteractionKernel<IFType,DBuffer,GeomType>& K,
           const IPType& Prm, PropagatorProcessBase& Proc) {
    typedef
    void
    (*MvType)(Propagator<T>&,InteractionKernel<IFType,DBuffer,GeomType>&,
              const IPType&);
    MvType Mv=reinterpret_cast<MvType>(P.Data[StepFunc].ptr);
    Proc(P);
  }

}

#endif

