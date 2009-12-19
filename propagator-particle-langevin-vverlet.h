
#ifndef _Propagator_Particle_Langevin_VelVerlet_H_
#define _Propagator_Particle_Langevin_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-langevin-vverlet-index.h"
#include "propagator-langevin-vverlet-index.h"
#include "propagator-common-index.h"
#include "random-generator.h"
#include <cmath>

namespace std {

  void PLV_Move_BeforeG(VectorBase<double>& Coordinate,
                        VectorBase<double>& Velocity,
                        const VectorBase<double>& Gradient,
                        FuncParamType& mnPrm,const FuncParamType& gbPrm,
                        const FuncParamType& cgbPrm) {
    Velocity.scaleshift(mnPrm[BasicPLV][FactorBeforeGPLV],
                        -mnPrm[BasicPLV][HfDeltaTIvMPLV],Gradient);
    GaussianRNG *pgrng=
      reinterpret_cast<GaussianRNG*>(static_cast<long long>(
            gbPrm[RandPointerLV][GaussianRNGPointerLV]));
    (*pgrng).FillArray(mnPrm[RandomVelocityPLV]);
    Velocity.shift(mnPrm[BasicPLV][RandomVelocitySizePLV],
                   mnPrm[RandomVelocityPLV]);
    Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],Velocity);
  }

  void PLV_Move_AfterG(VectorBase<double>& Coordinate,
                       VectorBase<double>& Velocity,
                       const VectorBase<double>& Gradient,
                       FuncParamType& mnPrm,const FuncParamType& gbPrm,
                       const FuncParamType& cgbPrm) {
    Velocity.shift(-mnPrm[BasicPLV][HfDeltaTIvMPLV],Gradient);
    GaussianRNG *pgrng=
      reinterpret_cast<GaussianRNG*>(static_cast<long long>(
            gbPrm[RandPointerLV][GaussianRNGPointerLV]));
    (*pgrng).FillArray(mnPrm[RandomVelocityPLV]);
    Velocity.shift(mnPrm[BasicPLV][RandomVelocitySizePLV],
                   mnPrm[RandomVelocityPLV]);
    Velocity.scale(mnPrm[BasicPLV][FactorAfterGPLV]);
  }

  void PLV_AllocParam(FuncParamType& mnPrm, const VectorBase<uint>& SizeInf) {
    mnPrm.allocate(NumberParamPLV);
    varVector<uint> offset(NumberParamPLV),size(NumberParamPLV);
    offset[BasicPLV]=0;      size[BasicPLV]=NumberBasicPLV;
    offset[RandomVelocityPLV]=NumberBasicPLV;
    size[RandomVelocityPLV]=SizeInf[0];
    mnPrm.BuildStructure(offset,size);
  }

  void PLV_Synchronize(const VectorBase<double>& IvMass,
                       const FuncParamType& gbPrm,const FuncParamType& cgbPrm,
                       FuncParamType& mnPrm) {
    mnPrm[BasicPLV][HfDeltaTIvMPLV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    IvMass[0];
    mnPrm[BasicPLV][FrictionCoefPLV]=mnPrm[BasicPLV][HydrodynamicRadiusPLV]*
                                     gbPrm[BasicLV][ViscosityCoefLV];
    mnPrm[BasicPLV][RandomVelocitySizePLV]=
        sqrt(mnPrm[BasicPLV][FrictionCoefPLV]*gbPrm[BasicLV][TempeDeltaTLV])*
        IvMass[0];
    double tmd;
    tmd=mnPrm[BasicPLV][HfDeltaTIvMPLV]*mnPrm[BasicPLV][FrictionCoefPLV];
    mnPrm[BasicPLV][FactorBeforeGPLV]=1.-tmd;
    mnPrm[BasicPLV][FactorAfterGPLV]=1./(1.+tmd);
  }

  void PLV_SetHydrodynamicRadius(FuncParamType& mnPrm,
                                 const double* data, const uint&) {
    mnPrm[BasicPLV][HydrodynamicRadiusPLV]=*data;
  }

  void SetAsPLV(MonomerPropagator& MP) {
    MP.MvFunc.allocate(NumberMoveLV);
    MP.MvFunc[BeforeGLV]=PLV_Move_BeforeG;
    MP.MvFunc[AfterGLV]=PLV_Move_AfterG;
    MP.SetFunc.allocate(NumberSetPLV);
    MP.SetFunc[SetHydrodynamicRadiusPLV]=PLV_SetHydrodynamicRadius;
    MP.Alloc=PLV_AllocParam;
    MP.Sync=PLV_Synchronize;
  }

}

#endif
