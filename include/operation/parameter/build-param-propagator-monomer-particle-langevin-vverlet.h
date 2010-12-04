
#ifndef _Build_Parameter_Propagator_Monomer_Particle_Langevin_VelVerlet_H_
#define _Build_Parameter_Propagator_Monomer_Particle_Langevin_VelVerlet_H_

#include "data/name/propagator-type.h"
#include "data/name/monomer-type.h"
#include "operation/parameter/build-param-propagator-monomer-base.h"

namespace std {

  template <typename T>
  void BuildParameterPropagatorMonomerPLV(
      UniqueParameter* P, const UniqueParameter* GP) {
    BuildParameterPropagatorMonomerBase<T>(P);
    copy(P[PLV_HalfDeltaTIvM],
         GP[HalfDeltaTime].value<T>()*P[IvMassData].value<T>());
    copy(P[PLV_FrictionCoef],
         P[PLV_HydrodynamicRadius].value<T>()*GP[LV_Viscosity].value<T>());
    copy(P[PLV_RandomVelocitySize],
         sqroot(P[PLV_FrictionCoef].value<T>()*
                GP[LV_TemperatureDeltaT].value<T>())*
         P[IvMassData].value<T>());
    T tmd;
    tmd=P[PLV_HalfDeltaTIvM].value<T>()*P[PLV_FrictionCoef].value<T>();
    copy(P[PLV_BeforeG],1.-tmd);
    copy(P[PLV_AfterG],1./(1.+tmd));
  }

  template <typename T>
  void BuildParameterPropagatorMonomerPLV(
      Vector<UniqueParameter>& P, const Vector<UniqueParameter>& GP) {
    assert(P.size>=PropagatorMonomerPLVNumberParameter);
    BuildParameterPropagatorMonomerPLV<T>(P.data,GP.data);
  }

  template <typename T>
  void allocatePropagatorMonomerPLVParameter(Vector<UniqueParameter>& P) {
    allocate(P,PropagatorMonomerPLVNumberParameter);
    P[MoveMode].u=Langevin_VelocityVerlet;
    P[MonomerMode].u=ParticleType;
    typedef
    void (*BuildFunc)(UniqueParameter*,const UniqueParameter*);
    P[pBuild].ptr=
      reinterpret_cast<void*>(
      static_cast<BuildFunc>(BuildParameterPropagatorMonomerPLV<T>));
    typedef
    void (*MvFunc)(Vector<T>&,Vector<T>&,const Vector<T>&,const Vector<T>&,
                   const Vector<UniqueParameter>&,
                   const Vector<UniqueParameter>&);
    P[LV_MoveBeforeG].ptr=
      reinterpret_cast<void*>(static_cast<MvFunc>(PLVMove_BeforeG<T>));
    P[LV_MoveAfterG].ptr=
      reinterpret_cast<void*>(static_cast<MvFunc>(PLVMove_AfterG<T>));

  }

}

#endif

