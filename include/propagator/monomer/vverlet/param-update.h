
#ifndef _Propagator_Monomer_Parameter_VelocityVerlet_Update_H_
#define _Propagator_Monomer_Parameter_VelocityVerlet_Update_H_

#include "propagator/monomer/common/param-update.h"
#include "propagator/monomer/vverlet/param-name.h"

namespace mysimulator {

  template <typename T>
  void UpdateMonomerPropagatorVelVerlet(
      Vector<UniqueParameter64Bit>& MP,
      const Vector<UniqueParameter64Bit>& SP) {
    UpdateMonomerPropagatorCommon<T>(MP,SP);
  }

}

#endif

