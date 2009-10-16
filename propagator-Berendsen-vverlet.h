
#ifndef _Propagator_Berendsen_VelVerlet_H_
#define _Propagator_Berendsen_VelVerlet_H_

#include "propagator-particle-Berendsen-vverlet.h"
#include "interaction-4listset.h"

namespace std {

  template <typename DistEvalObj, typename GeomType>
  void SetAs_BerendsenVelVerlet(
      const varVector<Property>& PropSet,
      varVector<MonomerPropagatorFormat<DistEvalObj,GeomType> >& MvSet) {
    uint n=PropSet.size(), mType;
    MvSet.allocate(n);
    for(uint i=0;i<n;++i) {
      mType=PropSet[i].MonomerType;
      if(mType==Particle)
        SetAs_ParticleBerendsenVelVerlet(MvSet[i]);
      else if(mType>NumberTypes) myError("Unknown monomer type!");
    }
  }

}

#endif
