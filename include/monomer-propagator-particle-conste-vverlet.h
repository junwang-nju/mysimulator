
#ifndef _Monomoer_Propagator_Particle_ConstantE_VelocityVerlet_H_
#define _Monomoer_Propagator_Particle_ConstantE_VelocityVerlet_H_

#include "monomer-propagator-parameter-name-particle-conste-vverlet.h"
#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void PEVMove_BeforeG(double* Coor, double* Vel, const double* Grad,
                       const unsigned int dim,
                       const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    shift(Vel,-Prm[PEV_HalfDeltaTIvM].d,Grad,dim);
    shift(Coor,GbPrm[DeltaTime].d,Vel,dim);
  }

  void PEVMove_AfterG(double* Coor, double* Vel, const double* Grad,
                      const unsigned int dim,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    shift(Vel,-Prm[PEV_HalfDeltaTIvM].d,Grad,dim);
  }

  void PEVSynchronize(const Vector<double>& ivMass,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    Prm[PEV_HalfDeltaTIvM]=GbPrm[HalfDeltaTime].d*ivMass[0];
  }

}

#include "monomer-propagator.h"

namespace std {

  void SetAsParticleEV(MonomerPropagator& MP) {
    allocate(MP.Move,NumberMoveParticleEV);
    MP.Move[PEV_BeforeG]=PEVMove_BeforeG;
    MP.Move[PEV_AfterG]=PEVMove_AfterG;
    release(MP.MSet);
    allocate(MP.MParam,NumberParameterParticleEV);
    MP.MSync=PEVSynchronize;
  }

}

#endif

