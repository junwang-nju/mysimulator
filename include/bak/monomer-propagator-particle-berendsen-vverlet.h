
#ifndef _Monomer_Propagator_Particle_Berendsen_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_Berendsen_VelocityVerlet_H_

#include "monomer-propagator.h"
#include "monomer-propagator-parameter-name-particle-berendsen-vverlet.h"
#include "propagator-parameter-name-berendsen-vverlet.h"

namespace std {

  void PBV_MoveBeforeG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.shift(-Param[PBV_HalfDeltaTIvM].d,Gradient);
    Coordinate.shift(GParam[DeltaTime].d,Velocity);
  }

  void PBV_MoveAfterG(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.shift(-Param[PBV_HalfDeltaTIvM].d,Gradient);
  }

  void PBV_MovePostProcess(
      VectorBase<double>& Coordinate, VectorBase<double>& Velocity,
      const VectorBase<double>& Gradient,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    assert(Coordinate.size()==Velocity.size());
    assert(Coordinate.size()==Gradient.size());
    Velocity.scale(GParam[BV_ScaleFactor].d);
  }

  void PBV_Allocate(varVector<PropagatorDataElementType>& Prm) {
    Prm.allocate(NumberParamParticleBV);
  }

  void PBV_Synchronize(
      const VectorBase<double>& IvMass,
      const VectorBase<PropagatorDataElementType>& GParam,
      VectorBase<PropagatorDataElementType>& Param) {
    Param[PBV_HalfDeltaTIvM]=GParam[HalfDeltaTime].d*IvMass[0];
  }

  void SetAsParticleBV(MonomerPropagator& MP) {
    MP.Move.allocate(NumberMoveParticleBV);
    MP.Move[PBV_BeforeG]=PBV_MoveBeforeG;
    MP.Move[PBV_AfterG]=PBV_MoveAfterG;
    MP.Move[PBV_PostProcess]=PBV_MovePostProcess;
    MP.MSet.clear();
    MP.Alloc=PBV_Allocate;
    MP.Sync=PBV_Synchronize;
  }

}

#endif

