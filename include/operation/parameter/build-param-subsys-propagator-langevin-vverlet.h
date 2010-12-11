
#ifndef _Build_Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_
#define _Build_Parameter_Subsystem_Propagator_Langevin_VelocityVerlet_H_

#include "data/propagator/subsystem-propagator.h"
#include "operation/parameter/build-param-subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterSubSysPropagatorLV(subsysPropagator<T>& SP) {
    assert(SP.size>=subsysPropagatorLVNumberParameter);
    typedef
    void (*mBuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    BuildParameterSubsysPropagatorBase<T>(SP);
    copy(SP[LV_TemperatureTimeStep],
         SP[LV_Temperature].value<T>()*SP[TimeStep].value<T>());
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mBuildFunc>(SP.merPg[i][monomerPgBuild].ptr)(
          P.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

}

#endif

