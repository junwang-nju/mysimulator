
#ifndef _Dynamics_Algorithm_VelocityVerlet_Data_Link_H_
#define _Dynamics_Algorithm_VelocityVerlet_Data_Link_H_

#include "dynamics/vverlet/data/interface.h"
#include "system/propagate/interface.h"

namespace mysimulator {

  template <typename T, template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void _link(DynamicsVVerletData<T,VT>& D, SysPropagate<T,VT,SCT>& SE,
             const VT<T>& X) {
    assert(IsValid(D)&&IsValid(SE)&&IsValid(X));
    Unique64Bit *P=SE.Param.start;
  }

}

#endif

