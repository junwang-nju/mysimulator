
#ifndef _Propagator_Particle_Berendsen_VelVerlet_H_
#define _Propagator_Particle_Berendsen_VelVerlet_H_

#include "property.h"
#include "monomer-propagator.h"
#include "propagator-particle-berendsen-vverlet-index.h"
#include "propagator-berendsen-vverlet-index.h"
#include "propagator-common-index.h"
#include "propagator-op.h"

namespace std {

  void PBV_Move_BeforeG(Property& nProp, const ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],nProp.Gradient);
    nProp.Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],nProp.Velocity);
  }

  void PBV_Move_AfterG(Property& nProp, const ParamPackType& mnPrm,
                       const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],nProp.Gradient);
  }

  void PBV_Move_PostProcess(Property& nProp, const ParamPackType& mnPrm,
                            const ParamPackType& gbPrm,
                            const ParamPackType& cgbPrm) {
    nProp.Velocity.scale(gbPrm[BasicBV][ScaleFacBV]);
  }

  void PBV_AllocParam(ParamPackType& mnPrm, const Property& nProp) {
    PropagatorParamAllocate(mnPrm,static_cast<uint>(NumberParamPBV));
    PropagatorParamAllocate(mnPrm[BasicPBV],
                            static_cast<uint>(NumberBasicPBV));
  }

  void PBV_Synchronize(const Property& nProp, const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm, ParamPackType& mnPrm) {
    mnPrm[BasicPBV][HfDeltaTIvMPBV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    nProp.ivMass[0];
  }

  void SetAsPBV(MonomerPropagator& MP) {
    PropagatorParamAllocate(MP.MvFunc,static_cast<uint>(NumberMoveBV));
    MP.MvFunc[BeforeGBV]=PBV_Move_BeforeG;
    MP.MvFunc[AfterGBV]=PBV_Move_AfterG;
    MP.MvFunc[PostProcessBV]=PBV_Move_PostProcess;
    PropagatorParamAllocate(MP.SetFunc,static_cast<uint>(NumberSetPBV));
    MP.Alloc=PBV_AllocParam;
    MP.Sync=PBV_Synchronize;
  }

}

#endif

