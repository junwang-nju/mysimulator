
#ifndef _Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_
#define _Monomer_Propagator_Particle_Langevin_VelocityVerlet_H_

#include "monomer-propagator-parameter-name-particle-langevin-vverlet.h"
#include "unique-parameter.h"
#include "random-generator.h"

namespace std {

  void PLVMove_BeforeG(double* Coor, double* Vel, const double* Grad,
                       const unsigned int dim,
                       const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    scaleshift(Vel,Prm[PLV_FactorBeforeG].d,-Prm[PLV_HalfDeltaTIvM].d,Grad,dim);
    GaussianRNG *pgng;
    pgng=reinterpret_cast<GaussianRNG*>(GbPrm[LV_GaussianRNGPointer].ptr);
    double* rv;
    rv=reinterpret_cast<double*>(Prm[PLV_RandomVelocityPointer].ptr);
    fillarray(*pgng,rv,dim);
    shift(Vel,Prm[PLV_RandomVelocitySize].d,rv,dim);
    shift(Coor,GbPrm[DeltaTime].d,Vel,dim);
  }

  void PLVMove_AfterG(double* Coor, double* Vel, const double* Grad,
                      const unsigned int dim,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    shift(Vel,-Prm[PLV_HalfDeltaTIvM].d,Grad,dim);
    GaussianRNG *pgng;
    pgng=reinterpret_cast<GaussianRNG*>(GbPrm[LV_GaussianRNGPointer].ptr);
    double *rv;
    rv=reinterpret_cast<double*>(Prm[PLV_RandomVelocityPointer].ptr);
    fillarray(*pgng,rv,dim);
    shift(Vel,Prm[PLV_RandomVelocitySize].d,rv,dim);
    scale(Vel,Prm[PLV_FactorAfterG].d,dim);
  }

  void PLVSet_HydrodynamicRadius(UniqueParameter* Prm, const void* pd) {
    Prm[PLV_HydrodynamicRadius]=*reinterpret_cast<const double*>(pd);
  }

  void PLVSet_RandomVelocityPointer(UniqueParameter* Prm, const void* pp) {
    Prm[PLV_RandomVelocityPointer].ptr=const_cast<void*>(pp);
  }

  void PLVSynchronize(const Vector<double>& ivMass,
                      const UniqueParameter* GbPrm, UniqueParameter* Prm) {
    Prm[PLV_HalfDeltaTIvM]=GbPrm[HalfDeltaTime].d*ivMass[0];
    Prm[PLV_FrictionCoef]=Prm[PLV_HydrodynamicRadius].d*GbPrm[LV_Viscosity].d;
    Prm[PLV_RandomVelocitySize]=sqrt(Prm[PLV_FrictionCoef].d*
                                     GbPrm[LV_TemperatureDeltaT].d)*ivMass[0];
    double tmd;
    tmd=Prm[PLV_HalfDeltaTIvM].d*Prm[PLV_FrictionCoef].d;
    Prm[PLV_FactorBeforeG]=1.-tmd;
    Prm[PLV_FactorAfterG]=1./(1.+tmd);
  }

}

#include "monomer-propagator.h"

namespace std {

  void SetAsParticleLV(MonomerPropagator& MP) {
    allocate(MP.Move,NumberMoveParticleLV);
    MP.Move[PLV_BeforeG]=PLVMove_BeforeG;
    MP.Move[PLV_AfterG]=PLVMove_AfterG;
    allocate(MP.MSet,NumberSetParticleLV);
    MP.MSet[HydrodynamicRadiusPLV]=PLVSet_HydrodynamicRadius;
    MP.MSet[RandomVelocityPointerPLV]=PLVSet_RandomVelocityPointer;
    allocate(MP.MParam,NumberParameterParticleLV);
    MP.MSync=PLVSynchronize;
  }
}

#endif

