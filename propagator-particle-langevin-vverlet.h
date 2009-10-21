
#ifndef _Propagator_Particle_Langevin_VelVerlet_H_
#define _Propagator_Particle_Langevin_VelVerlet_H_

#include "particle.h"
#include "monomer-propagator.h"
#include "propagator-particle-langevin-vverlet-index.h"
#include "propagator-langevin-vverlet-index.h"
#include "propagator-common-index.h"
#include "propagator-op.h"

namespace std {

  void PLV_Move_BeforeG(Property& nProp, const ParamPackType& mnPrm,
                        const ParamPackType& gbPrm,
                        const ParamPackType& cgbPrm) {
    nProp.Velocity.scaleshift(mnPrm[BasicPLV][FactorBeforeGPLV],
                              -mnPrm[BasicPLV][HfDeltaTIvMPLV],nProp.Gradient);
  }

}

#endif
