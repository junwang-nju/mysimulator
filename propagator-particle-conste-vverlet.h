
#ifndef _Propagator_Particle_ConstE_VelVerlet_H_
#define _Propagator_Particle_ConstE_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-conste-vverlet-index.h"
#include "propagator-conste-vverlet-index.h"
#include "propagator-common-index.h"

namespace std {

  void PEV_Move_BeforeG(Property& nProp, ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],nProp.Gradient);
    nProp.Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],nProp.Velocity);
  }

  void PEV_Move_AfterG(Property& nProp, ParamPackType& mnPrm,
                       const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],nProp.Gradient);
  }

  void PEV_AllocParam(ParamPackType& mnPrm, const Property& Prop) {
    mnPrm.allocate(NumberParamPEV);
    mnPrm[BasicPEV].allocate(NumberBasicPEV);
  }

  void PEV_Synchronize(const Property& nProp, const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm, ParamPackType& mnPrm) {
    mnPrm[BasicPEV][HfDeltaTIvMPEV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    nProp.ivMass[0];
  }

  void SetAsPEV(MonomerPropagator& MP) {
    MP.MvFunc.allocate(NumberMoveEV);
    MP.MvFunc[BeforeGEV]=PEV_Move_BeforeG;
    MP.MvFunc[AfterGEV]=PEV_Move_AfterG;
    MP.SetFunc.allocate(NumberSetPEV);
    MP.Alloc=PEV_AllocParam;
    MP.Sync=PEV_Synchronize;
  }

}

#endif
