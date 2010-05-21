
#ifndef _Monomer_Propagator_Particle_Berendsen_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_Berendsen_VelocityVerlet_H_

#include "monomer-propagator-parameter-name-particle-berendsen-vverlet.h"
#include "unique-parameter.h"
#include "vector.h"

namespace std {

  void PBVMove_BeforeG(double* Coor, double* Vel, const double* Grad,
                       const unsigned int dim,
                       const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    shift(Vel,-Prm[PBV_HalfDeltaTIvM].d,Grad,dim);
    shift(Coor,GbPrm[DeltaTime].d,Vel,dim);
  }

  void PBVMove_AfterG(double* Coor, double* Vel, const double* Grad,
                      unsigned int dim,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    shift(Vel,-Prm[PBV_HalfDeltaTIvM].d,Grad,dim);
  }

  void PBVMove_PreProcess(double* Coor, double* Vel, const double* Grad,
                          const unsigned int dim,
                          const UniqueParameter* GbPrm, UniqueParameter* Prm){
    scale(Vel,GbPrm[BV_BScaleFactor].d,dim);
  }

  void PBVMove_PostProcess(double* Coor, double* Vel, const double* Grad,
                           const unsigned int dim,
                           const UniqueParameter* GbPrm, UniqueParameter* Prm){
    scale(Vel,GbPrm[BV_AScaleFactor].d,dim);
  }

  void PBVSynchronize(const Vector<double>& ivMass,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    Prm[PBV_HalfDeltaTIvM]=GbPrm[HalfDeltaTime].d*ivMass[0];
  }

}

#include "monomer-propagator.h"

namespace std {

  void SetAsParticleBV(MonomerPropagator& MP) {
    allocate(MP.Move,NumberMoveParticleBV);
    MP.Move[PBV_PreProcess]=PBVMove_PreProcess;
    MP.Move[PBV_BeforeG]=PBVMove_BeforeG;
    MP.Move[PBV_AfterG]=PBVMove_AfterG;
    MP.Move[PBV_PostProcess]=PBVMove_PostProcess;
    release(MP.MSet);
    allocate(MP.MParam,NumberParameterParticleBV);
    MP.MSync=PBVSynchronize;
  }

}

#endif

