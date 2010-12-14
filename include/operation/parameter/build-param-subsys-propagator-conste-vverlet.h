
#ifndef _Build_Parameter_Subsystem_Propagator_ConstantE_VelocityVerlet_H_
#define _Build_Parameter_Subsystem_Propagator_ConstantE_VelocityVerlet_H_

#include "data/propagator/subsys-propagator.h"
#include "data/name/subsys-propagator-conste-vverlet.h"
#include "operation/parameter/build-param-subsys-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterSubsysPropagatorEV(subsysPropagator<T>& SP) {
    assert(SP.size>=subsysPropagatorEVNumberParameter);
    typedef
    void (*mBuildFunc)(monomerPropagator<T>&,const Vector<UniqueParameter>&);
    BuildParameterSubsysPropagatorBase<T>(SP);
    for(unsigned int i=0;i<SP.merPg.size;++i)
      reinterpret_cast<mBuildFunc>(SP.merPg[i][monomerPgBuild].ptr)(
          SP.merPg[i],static_cast<const Vector<UniqueParameter>&>(SP));
  }

}

#endif

