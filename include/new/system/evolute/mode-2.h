
#ifndef _System_Evolute_Mode_2_H_
#define _System_Evolute_Mode_2_H_

#include "system/grouping/interface.h"
#include "system/grouping/action/minimizer/line/regular/move-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SystemEvoluteMode2(SCT<T,VT>& SC, SysInteraction<IDT,PT,GT,T>& SI,
                          Array1D<SysGrouping<T,IDT,PT,GT,VT,SCT> >& SG,
                          const Array1D<Array1D<unsigned int> >& GM) {
    for(unsigned int i=0;i<SG.size;++i)
      SG[i].evolute(MinimizerLineRegularShift,SC,SI);
  }

}

#endif

