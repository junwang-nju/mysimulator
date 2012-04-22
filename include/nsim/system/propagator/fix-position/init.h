
#ifndef _System_Propagator_FixPosition_Init_H_
#define _System_Propagator_FixPosition_Init_H_

#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void _InitFixPosition(SystemPropagator<T,CT>&) {}

}

#ifndef _INIT
#define _INIT(CT) \
  template <typename T> \
  void _InitFixPosition(SystemPropagator<T,CT>& P) { \
    for(unsigned int i=0;i<GrpContent.Size();++i) \
      Fill(P.GrpContent[i].Velocity,0.); \
  }
#else
#error "Duplicate Definition for Macro _INIT"
#endif

#include "system/content/with-v/interface.h"
#include "system/content/with-ev/interface.h"
#include "system/content/with-egv/interface.h"

namespace mysimulator {

  _INIT(SystemContentWithV)
  _INIT(SystemContentWithEV)
  _INIT(SystemContentWithEGV)

}

#ifdef _INIT
#undef _INIT
#endif

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void InitFixPosition(SystemPropagator<T,CT>& P) { _InitFixPosition(P); }

}

#endif

