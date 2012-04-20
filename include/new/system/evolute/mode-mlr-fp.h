
#ifndef _System_Evolute_Mode_MinimizerLineRegular_FixPosition_H_
#define _System_Evolute_Mode_MinimizerLineRegular_FixPosition_H_

#include "system/interaction/interface.h"
#include "system/propagate/interface.h"
#include "system/propagate/method-name.h"
#include "system/propagate/minimizer/line/regular/move-name.h"
#include "system/evaluate/both.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SysEvoluteModeFPMLR(
      SCT<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,BT,VT,SCT> >& SI,
      Array1DContent<SysPropagate<T,VT,SCT> >& SE,
      const Array1DContent<Array1D<unsigned int> >& GMap) {
    for(unsigned int i=0;i<GMap[SysMinimizerLineRegular].size;++i)
      SE[GMap[SysMinimizerLineRegular][i]].propagate(MinLineRegularShift);
    GenericEvaluateBoth(SC,SI);
  }

}

#endif

