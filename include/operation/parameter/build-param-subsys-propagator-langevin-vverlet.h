
#ifndef _Build_Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_
#define _Build_Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_

#include "data/propagator/subsys-propagator.h"
#include "operation/parameter/build-param-subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterSubsysPropagatorLV(subsysPropagator<T>& SP) {
    assert(SP.size>=subsysPropagatorLVNumberParameter);
    typedef
    void (*mBuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    BuildParameterSubsysPropagatorBase<T>(SP);
    copy(SP[LV_TemperatureTimeStep],
         static_cast<UniqueParameter&>(SP[LV_Temperature]).value<T>()*
         static_cast<UniqueParameter&>(SP[TimeStep]).value<T>());
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mBuildFunc>(SP.merPg[i][monomerPgBuild].ptr)(
          SP.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

}

#endif

