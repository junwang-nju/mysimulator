
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

  void PLV_Move_BeforeG(Property& nProp, ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.scaleshift(mnPrm[BasicPLV][FactorBeforeGPLV],
                              -mnPrm[BasicPLV][HfDeltaTIvMPLV],nProp.Gradient);
    GaussianRNG *pgrng=
      reinterpret_cast<GaussianRNG*>(static_cast<long long>(
            gbPrm[RandPointerLV][GaussianRNGPointerLV]));
    (*pgrng).FillArray(mnPrm[RandomVelocityPLV]);
    nProp.Velocity.shift(mnPrm[BasicPLV][RandomVelocitySizePLV],
                         mnPrm[RandomVelocityPLV]);
    nProp.Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],nProp.Velocity);
  }

  void PLV_Move_AfterG(Property& nProp, ParamPackType& mnPrm,
                       const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPLV][HfDeltaTIvMPLV],nProp.Gradient);
    GaussianRNG *pgrng=
      reinterpret_cast<GaussianRNG*>(static_cast<long long>(
            gbPrm[RandPointerLV][GaussianRNGPointerLV]));
    (*pgrng).FillArray(mnPrm[RandomVelocityPLV]);
    nProp.Velocity.shift(mnPrm[BasicPLV][RandomVelocitySizePLV],
                         mnPrm[RandomVelocityPLV]);
    nProp.Velocity.scale(mnPrm[BasicPLV][FactorAfterGPLV]);
  }

  void PLV_AllocParam(ParamPackType& mnPrm, const Property& nProp) {
    mnPrm.allocate(NumberParamPLV);
    mnPrm[BasicPLV].allocate(NumberBasicPLV);
    mnPrm[RandomVelocityPLV].allocate(nProp.Gradient.size());
  }

  void PLV_Synchronize(const Property& nProp, const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm, ParamPackType& mnPrm) {
    mnPrm[BasicPLV][HfDeltaTIvMPLV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    nProp.IMass[0];
    mnPrm[BasicPLV][FrictionCoefPLV]=mnPrm[BasicPLV][HydrodynamicRadiusPLV]*
                                     gbPrm[BasicLV][ViscosityCoefLV];
    mnPrm[BasicPLV][RandomVelocitySizePLV]=
        sqrt(mnPrm[BasicPLV][FrictionCoefPLV]*gbPrm[BasicLV][TempeDeltaTLV])*
        nProp.IMass[0];
    double tmd;
    tmd=mnPrm[BasicPLV][HfDeltaTIvMPLV]*mnPrm[BasicPLV][FrictionCoefPLV];
    mnPrm[BasicPLV][FactorBeforeGPLV]=1.-tmd;
    mnPrm[BasicPLV][FactorAfterGPLV]=1./(1.+tmd);
  }

  void PLV_SetHydrodynamicRadius(ParamPackType& mnPrm,
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
