
#ifndef _Build_Parameter_Monomer_Propagator_Particle_Berendsen_VelVerlet_H_
#define _Build_Parameter_Monomer_Propagator_Particle_Berendsen_VelVerlet_H_

#include "operation/parameter/build-param-monomer-propagator-base.h"
#include "data/name/monomer-propagator-particle-berendsen-vverlet.h"

namespace std {

  template <typename T>
  void BuildParameterMonomerPropagatorPBV(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    assert(MP.size>=monomerPropagatorPBVNumberParameter);
    BuildParameterMonomerPropagatorBase<T>(MP);
    copy(MP[PBV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*MP[IvMassData].value<T>());
  }

}

#endif

