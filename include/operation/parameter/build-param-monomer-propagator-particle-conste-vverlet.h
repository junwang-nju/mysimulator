
#ifndef _Build_Parameter_Monomer_Propagator_Particle_ConstantE_VelVerlet_H_
#define _Build_Parameter_Monomer_Propagator_Particle_ConstantE_VelVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/monomer-propagator-particle-conste-vverlet.h"
#include "operation/parameter/build-param-monomer-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterMonomerPropagatorPEV(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    assert(MP.size>=monomerPropagatorPEVNumberParameter);
    BuildParameterMonomerPropagatorBase<T>(MP);
    copy(MP[PEV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*MP[IvMassData].value<T>());
  }

}

#endif
