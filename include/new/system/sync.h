
#ifndef _System_Synchronization_H_
#define _System_Synchronization_H_

#include "system/interaction/interface.h"
#include "interaction/calc.h"
#include "system/content/with-e/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class VecType>
  void sync(SysContentWithE<T,VecType>& S,
            const SysInteraction<IDType,ParamType,GeomType,T>& SI) {
    S.Energy=0;
    Calc(SI.Func(),S.X(),SI.ID(),SI.Param(),SI.Geom(),S.Energy);
  }

}

#include "system/content/with-eg/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class VecType>
  void sync(SysContentWithEG<T,VecType>& S,
            const SysInteraction<IDType,ParamType,GeomType,T>& SI) {
    S.Energy=0;
    fill(S.Gradient,cZero);
    Calc(SI.Func(),S.X(),SI.ID(),SI.Param(),SI.Geom(),S.Energy,S.Gradient());
  }

}

#include "system/content/with-g/interface.h"

namespace mysimulator {

  template <typename T, typename IDType, typename ParamType, typename GeomType,
            template<typename> class VecType>
  void sync(SysContentWithG<T,VecType>& S,
            const SysInteraction<IDType,ParamType,GeomType,T>& SI) {
    fill(S.Gradient,cZero);
    Calc(SI.Func(),S.X(),SI.ID(),SI.Param(),SI.Geom(),S.Gradient());
  }

}

#endif

