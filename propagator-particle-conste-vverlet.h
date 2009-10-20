
#ifndef _Propagator_Particle_ConstE_VelVerlet_H_
#define _Propagator_Particle_ConstE_VelVerlet_H_

#include "property.h"
#include "monomer-propagator.h"
#include "propagator-particle-conste-vverlet-index.h"
#include "propagator-conste-vverlet-index.h"
#include "propagator-common-index.h"
#include "propagator-op.h"

namespace std {

  void PEV_Move_BeforeG(Property& nProp, const ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],nProp.Gradient);
    nProp.Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],nProp.Velocity);
  }

  void PEV_Move_AfterG(Property& nProp, const ParamPackType& mnPrm,
                       const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPEV][HfDeltaTIvMPEV],nProp.Gradient);
  }

  void PEV_AllocParam(ParamPackType& mnPrm, const Property& Prop) {
    PropagatorParamAllocate(mnPrm,static_cast<uint>(NumberParamPEV));
    PropagatorParamAllocate(mnPrm[BasicPEV],
                            static_cast<uint>(NumberBasicPEV));
  }

  void PEV_Synchronize(const Property& nProp, const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm, ParamPackType& mnPrm) {
    mnPrm[BasicPEV][HfDeltaTIvMPEV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    nProp.ivMass[0];
  }

  void SetAsPEV(MonomerPropagator& MP) {
    PropagatorParamAllocate(MP.MvFunc,static_cast<uint>(NumberMoveEV));
    MP.MvFunc[BeforeGEV]=PEV_Move_BeforeG;
    MP.MvFunc[AfterGEV]=PEV_Move_AfterG;
    PropagatorParamAllocate(MP.SetFunc,static_cast<uint>(NumberSetPEV));
    MP.Alloc=PEV_AllocParam;
    MP.Sync=PEV_Synchronize;
  }

}

#endif
