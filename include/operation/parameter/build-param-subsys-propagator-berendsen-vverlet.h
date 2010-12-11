
#ifndef _Build_Parameter_Subsystem_Propagator_Berendsen_VelocityVerlet_H_
#define _Build_Parameter_Subsystem_Propagator_Berendsen_VelocityVerlet_H_

#include "data/name/subsys-propagator-berendsen-vverlet.h"
#include "operation/parameter/build-param-subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterSubsysPropagatorBV(subsysPropagator<T>& SP) {
    assert(SP.size>=subsysPropagatorBVNumberParameter);
    typedef
    void (*mBuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    BuildParameterSubsysPropagatorBase<T>(SP);
    copy(SP[BV_TemperatureDOF],
         static_cast<UniqueParameter&>(SP[BV_Temperature]).value<T>()*
         static_cast<UniqueParameter&>(SP[BV_DegreeFreedom]).value<T>());
    copy(SP[BV_HalfTimeStepIvRelaxT],
         static_cast<UniqueParameter&>(SP[TimeStep]).value<T>()/
         static_cast<UniqueParameter&>(SP[BV_RelaxTime]).value<T>());
    copy(SP[BV_IvHalfTimeStepIvRelaxTPlusOne],
         1./
         (static_cast<UniqueParameter&>(SP[BV_HalfTimeStepIvRelaxT]).value<T>()
          +1.));
    copy(SP[BV_TemperatureDOFIvDKineticEnergy],
         static_cast<UniqueParameter&>(SP[BV_TemperatureDOF]).value<T>()/
         static_cast<UniqueParameter&>(SP[BV_DualKineticEnergy]).value<T>());
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mBuildFunc>(SP.merPg[i][monomerPgBuild].ptr)(
          SP.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

}

#endif

