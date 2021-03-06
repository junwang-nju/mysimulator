
#ifndef _Propagator_Subsystem_Parameter_Update_VelocityVerlet_ConstantE_H_
#define _Propagator_Subsystem_Parameter_Update_VelocityVerlet_ConstantE_H_

#include "propagator/subsystem/parameter/vverlet/update.h"
#include "propagator/subsystem/parameter/vverlet/conste/name.h"

namespace mysimulator {

  template <typename T>
  void UpdateSubsysPropagatorConstEVelVerlet(SubsysPropagator<T>& SP) {
    UpdateSubsysPropagatorVelVerlet<T>(SP);
    for(unsigned int i=0;i<SP.Mer.size;++i)
      SP.Mer[i].Update(SP.Mer[i].Data,SP.Data);
  }

}

#endif

