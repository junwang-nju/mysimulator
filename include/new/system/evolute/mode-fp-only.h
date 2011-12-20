
#ifndef _System_Evolute_Mode_FixPosition_Only_H_
#define _System_Evolute_Mode_FixPosition_Only_H_

#include "system/interaction/interface.h"
#include "system/propagate/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,
            template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void SysEvoluteModeFPOnly(
      SCT<T,VT>& SC,
      Array1DContent<SysInteraction<T,IDT,PT,GT,VT,SCT> >& SI,
      Array1DContent<SysPropagate<T,VT,SCT> >& SE,
      const Array1DContent<Array1D<unsigned int> >& GMap) {}

}

#endif

