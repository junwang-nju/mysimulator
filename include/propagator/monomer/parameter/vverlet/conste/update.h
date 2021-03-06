
#ifndef _Propagator_Monomer_Parameter_VelocityVerlet_ConstantE_Update_H_
#define _Propagator_Monomer_Parameter_VelocityVerlet_ConstantE_Update_H_

#include "propagator/monomer/parameter/vverlet/update.h"
#include "propagator/monomer/parameter/vverlet/conste/name.h"

namespace mysimulator {

  template <typename T>
  void UpdateMonomerPropagatorConstEVelVerlet(
      Vector<UniqueParameter64Bit>& MP,const Vector<UniqueParameter64Bit>& SP){
    UpdateMonomerPropagatorVelVerlet<T>(MP,SP);
  }

}

#endif

