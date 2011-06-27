
#ifndef _Propagator_Run_H_
#define _Propagator_Run_H_

#include "propagator/md/interface.h"
#include "propagator/base/parameter/common/name.h"
#include "propagator/process/base/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class DBuffer, typename GeomType,
            typename IFType, typename IPType>
  void Run(
      MDPropagator<T,DBuffer,GeomType,IFType,IPType>& P,
      PropagatorProcessBase<MDPropagator<T,DBuffer,GeomType,IFType,IPType> >&
        Proc) {
    Proc(P);
    for(unsigned int i=0;i<P.Data[NumberOutput].u;++i) {
      for(unsigned int k=0;k<P.Data[NumberStepPerOutput].u;++k) P.Step(P);
      P.value(NowTime)+=P.value(OutputInterval);
      Proc(P);
    }
  }

}

#endif

