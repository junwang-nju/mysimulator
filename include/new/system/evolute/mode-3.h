
#ifndef _System_Evolute_Mode_3_H_
#define _System_Evolute_Mode_3_H_

#include "system/grouping/interface.h"
#include "system/grouping/action/fix-position/move-name.h"
#include "system/grouping/action/minimizer/line/regular/move-name.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SystemEvoluteMode3(SCT<T,VT>& SC, SysInteraction<IDT,PT,GT,T>& SI,
                          Array1D<SysGrouping<T,IDT,PT,GT,VT,SCT> >& SG,
                          const Array1D<Array1D<unsigned int> >& GM) {
    for(unsigned int i=0;i<GM[0].size;++i)
      SG[GM[0][i]].evolute(FixPositionNoMove,SC,SI);
    for(unsigned int i=0;i<GM[1].size;++i)
      SG[GM[1][i]].evolute(MinimizerLineRegularShift,SC,SI);
  }

}

#endif

