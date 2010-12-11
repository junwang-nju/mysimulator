
#ifndef _Build_Parameter_Monomer_Propagator_Particle_Langevin_VelVerlet_H_
#define _Build_Parameter_Monomer_Propagator_Particle_Langevin_VelVerlet_H_

#include "data/name/monomer-propagator-particle-langevin-vverlet.h"
#include "data/name/subsys-propagator-langevin-vverlet.h"
#include "operation/parameter/build-param-monomer-propagator-base.h"

namespace std {

  template <typename T>
  void BuildParameterMonomerPropagatorPLV(
      monomerPropagator<T>& MP, const Vector<UniqueParameter>& GP) {
    assert(MP.size>=monomerPropagatorPLVNumberParameter);
    BuildParameterMonomerPropagatorBase<T>(MP);
    copy(MP[PLV_HalfTimeStepIvM],
         GP[HalfTimeStep].value<T>()*
         static_cast<UniqueParameter&>(MP[IvMassData]).value<T>());
    copy(MP[PLV_FrictionCoef],
         static_cast<UniqueParameter&>(MP[PLV_HydrodynamicRadius]).value<T>()*
         GP[LV_Viscosity].value<T>());
    copy(MP[PLV_RandomVelocitySize],
         sqroot(static_cast<UniqueParameter&>(MP[PLV_FrictionCoef]).value<T>()*
                GP[LV_TemperatureTimeStep].value<T>())*
         static_cast<UniqueParameter&>(MP[IvMassData]).value<T>());
    T tmd;
    tmd=static_cast<UniqueParameter&>(MP[PLV_HalfTimeStepIvM]).value<T>()*
        static_cast<UniqueParameter&>(MP[PLV_FrictionCoef]).value<T>();
    copy(MP[PLV_FactorBeforeG],1.-tmd);
    copy(MP[PLV_FactorAfterG],1./(1.+tmd));
  }

}

#endif

