
#ifndef _System_Evolute_Mode_1_H_
#define _System_Evolute_Mode_1_H_

#include "system/grouping/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename>class VT,
            template<typename,template<typename>class> class SCT>
  void SystemEvoluteMode1(SCT<T,VT>& SC, SysInteraction<IDT,PT,GT,T>& SI,
                          Array1D<SysGrouping<T,IDT,PT,GT,VT,SCT> >& SG,
                          const Array1D<Array1D<unsigned int> >& GM) {}

}

#endif

