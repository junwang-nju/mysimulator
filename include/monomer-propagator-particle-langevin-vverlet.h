
#ifndef _Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_

#include "monomer-propagator.h"
#include "monomer-propagator-parameter-name-particle-langevin-vverlet.h"
#include "propagator-parameter-name-berendsen-vverlet.h"
#include "random-generator.h"

namespace std {

  void PLV_MoveBeforeG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.scaleshift(Param[PLV_FactorBeforeG].d,-Param[PLV_HalfDeltaTIvM].d,
                        Gradient);
    GaussianRNG *pgrng;
    pgrng=reinterpret_cast<GaussianRNG*>(GParam[LV_GaussianRNGPointer].vptr);
    typedef VectorBase<double> VecType;
    pgrng->FillArray(
      *reinterpret_cast<VecType*>(Param[PLV_RandomVelocityPointer].vptr));
    Velocity.shift(Param[PLV_RandomVelocitySize].d,
      *reinterpret_cast<VecType*>(Param[PLV_RandomVelocityPointer].vptr));
    Coordinate.shift(GParam[DeltaTime].d,Velocity);
  }

  void PLV_MoveAfterG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    Velocity.shift(-Param[PLV_HalfDeltaTIvM].d,Gradient);
    GaussianRNG *pgrng;
    pgrng=reinterpret_cast<GaussianRNG*>(GParam[LV_GaussianRNGPointer].vptr);
    typedef VectorBase<double> VecType;
    pgrng->FillArray(
      *reinterpret_cast<VecType*>(Param[PLV_RandomVelocityPointer].vptr));
    Velocity.shift(Param[PLV_RandomVelocitySize].d,
      *reinterpret_cast<VecType*>(Param[PLV_RandomVelocityPointer].vptr));
    Velocity.scale(Param[PLV_FactorAfterG].d);
  }

  void PLV_Allocate(varVector<PropagatorDataElementType>& Prm) {
    Prm.allocate(NumberParamParticleLV);
  }

  void PLV_Synchronize(
      const VectorBase<double>& IvMass,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    Param[PLV_HalfDeltaTIvM]=GParam[HalfDeltaTime].d*IvMass[0];
    Param[PLV_FrictionCoef]=Param[PLV_HydrodynamicRadius].d
                            *GParam[LV_ViscosityCoef].d;
    Param[PLV_RandomVelocitySize]=
      sqrt(Param[PLV_FrictionCoef].d*GParam[LV_TemperatureDeltaT].d)*IvMass[0];
    double tmd;
    tmd=Param[PLV_HalfDeltaTIvM].d*Param[PLV_FrictionCoef].d;
    Param[PLV_FactorBeforeG]=1.-tmd;
    Param[PLV_FactorAfterG]=1./(1.+tmd);
  }

  void PLV_SetHydrodynamicRadius(
      VectorBase<PropagatorDataElementType>& Prm, const void* pd) {
    Prm[PLV_HydrodynamicRadius]=*reinterpret_cast<const double*>(pd);
  }

  void PLV_SetRandomVelocityPointer(
      VectorBase<PropagatorDataElementType>& Prm, const void* pd) {
    Prm[PLV_RandomVelocityPointer].vptr=const_cast<void*>(pd);
  }

  void SetAsParticleLV(MonomerPropagator& MP) {
    MP.Move.allocate(NumberMoveParticleLV);
    MP.Move[PLV_BeforeG]=PLV_MoveBeforeG;
    MP.Move[PLV_AfterG]=PLV_MoveAfterG;
    MP.MSet.allocate(NumberSetParticleLV);
    MP.MSet[HydrodynamicRadiusInPLV]=PLV_SetHydrodynamicRadius;
    MP.MSet[RandomVelocityPointerInPLV]=PLV_SetRandomVelocityPointer;
    MP.Alloc=PLV_Allocate;
    MP.Sync=PLV_Synchronize;
  }

}

#endif

