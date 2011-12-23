
#ifndef _System_Evolute_Mode_FixPosition_Langevin_VelocityVerlet_H_
#define _System_Evolute_Mode_FixPosition_Langevin_VelocityVerlet_H_

#include "system/interaction/interface.h"
#include "system/propagate/interface.h"
#include "system/propagate/vverlet/langevin/move-name.h"
#include "system/propagate/method-name.h"
#include "system/evaluate/gradient.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SysEvoluteModeFPLgVV(
      SCT<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,VT,SCT> >& SI,
      Array1DContent<SysPropagate<T,VT,SCT> >& SE,
      const Array1DContent<Array1D<unsigned int> >& GMap) {
    for(unsigned int i=0;i<GMap[SysLangevinVelVerlet].size;++i)
      SE[GMap[SysLangevinVelVerlet][i]].propagate(LgVVerletBeforeG);
    GenericEvaluateGradient(SC,SI);
    for(unsigned int i=0;i<GMap[SysLangevinVelVerlet].size;++i)
      SE[GMap[SysLangevinVelVerlet][i]].propagate(LgVVerletAfterG);
  }

}

#endif

