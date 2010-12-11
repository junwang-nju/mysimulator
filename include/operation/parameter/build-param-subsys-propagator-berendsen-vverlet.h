
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
         SP[BV_Temperature].value<T>()*SP[BV_DegreeFreedom].value<T>());
    copy(SP[BV_HalfDeltaTIvRelaxT],
         SP[TimeStep].value<T>()/SP[BV_RelaxTime].value<T>());
    copy(SP[BV_IvHalfDeltaTIvRelaxTPlusOne],
         1./(SP[BV_HalfDeltaTIvRelaxT].value<T>()+1.));
    copy(SP[BV_TemperatureDOFIvDKineticEnergy],
         SP[BV_TemperatureDOF].value<T>()/SP[BV_DualKineticEnergy].value<T>());
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mBuildFunc>(P.merPg[i][monomerPgBuild].ptr)(
          P.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

}

#endif

