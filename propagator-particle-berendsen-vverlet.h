
#ifndef _Propagator_Particle_Berendsen_VelVerlet_H_
#define _Propagator_Particle_Berendsen_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-berendsen-vverlet-index.h"
#include "propagator-berendsen-vverlet-index.h"
#include "propagator-common-index.h"

namespace std {

  void PBV_Move_BeforeG(Property& nProp, ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],nProp.Gradient);
    nProp.Coordinate.shift(cgbPrm[BasicCommon][DeltaTime],nProp.Velocity);
  }

  void PBV_Move_AfterG(Property& nProp, ParamPackType& mnPrm,
                       const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm) {
    nProp.Velocity.shift(-mnPrm[BasicPBV][HfDeltaTIvMPBV],nProp.Gradient);
  }

  void PBV_Move_PostProcess(Property& nProp, ParamPackType& mnPrm,
                            const ParamPackType& gbPrm,
                            const ParamPackType& cgbPrm) {
    nProp.Velocity.scale(gbPrm[BasicBV][ScaleFacBV]);
  }

  void PBV_AllocParam(ParamPackType& mnPrm, const Property& nProp) {
    mnPrm.allocate(NumberParamPBV);
    mnPrm[BasicPBV].allocate(NumberBasicPBV);
  }

  void PBV_Synchronize(const Property& nProp, const ParamPackType& gbPrm,
                       const ParamPackType& cgbPrm, ParamPackType& mnPrm) {
    mnPrm[BasicPBV][HfDeltaTIvMPBV]=cgbPrm[BasicCommon][HalfDeltaTime]*
                                    nProp.IMass[0];
  }

  void SetAsPBV(MonomerPropagator& MP) {
    MP.MvFunc.allocate(NumberMoveBV);
    MP.MvFunc[BeforeGBV]=PBV_Move_BeforeG;
    MP.MvFunc[AfterGBV]=PBV_Move_AfterG;
    MP.MvFunc[PostProcessBV]=PBV_Move_PostProcess;
    MP.SetFunc.allocate(NumberSetPBV);
    MP.Alloc=PBV_AllocParam;
    MP.Sync=PBV_Synchronize;
  }

}

#endif

