
#ifndef _System_Evolute_Mode_ConstE_VelocityVerlet_Particle_H_
#define _System_Evolute_Mode_ConstE_VelocityVerlet_Particle_H_

#include "system/interaction/interface.h"
#include "system/propagate/interface.h"
#include "system/propagate/constE-vverlet-particle/move-name.h"
#include "system/evaluate/gradient.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SysEvoluteModeCEVPOnly(
      SCT<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,VT,SCT> >& SI,
      Array1DContent<SysPropagate<T,VT,SCT> >& SE,
      const Array1DContent<Array1D<unsigned int> >& GMap) {
    for(unsigned int i=0;i<SE.size;++i)
      SE[i].propagate(CEVVerletParticleBeforeG);
    GenericEvaluateGradient(SC,SI);
    for(unsigned int i=0;i<SE.size;++i)
      SE[i].propagate(CEVVerletParticleAfterG);
  }

}

#endif

