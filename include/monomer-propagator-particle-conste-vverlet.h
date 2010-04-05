
#ifndef _Monomer_Propagator_Particle_ConstantE_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_ConstantE_VelocityVerlet_H_

#include "monomer-propagator.h"
#include "monomer-propagator-parameter-name-particle-conste-vverlet.h"
#include "propagator-parameter-name-conste-vverlet.h"

namespace std {

  void PEV_MoveBeforeG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.shift(-Param[PEV_HalfDeltaTIvM].d,Gradient);
    Coordinate.shift(GParam[DeltaTime].d,Velocity);
  }

  void PEV_MoveAfterG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.shift(-Param[PEV_HalfDeltaTIvM].d,Gradient);
  }

  void PEV_Allocate(varVector<PropagatorDataElementType>& Prm) {
    Prm.allocate(NumberParamParticleEV);
  }

  void PEV_Synchronize(
      const VectorBase<double>& IvMass,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    Param[PEV_HalfDeltaTIvM].d=GParam[HalfDeltaTime].d*IvMass[0];
  }

  void SetAsParticleEV(MonomerPropagator& MP) {
    MP.Move.allocate(NumberMoveParticleEV);
    MP.Move[PEV_BeforeG]=PEV_MoveBeforeG;
    MP.Move[PEV_AfterG]=PEV_MoveAfterG;
    MP.Alloc=PEV_Allocate;
    MP.Sync=PEV_Synchronize;
  }

}

#endif

