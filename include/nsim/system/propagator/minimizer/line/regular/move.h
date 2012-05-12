
#ifndef _System_Propagator_Minimizer_Line_Regular_Move_H_
#define _System_Propagator_Minimizer_Line_Regular_Move_H_

#include "system/propagator/interface.h"
#include "system/propagator/minimizer/line/regular/parameter-name.h"

namespace mysimulator {

  template <typename T,template<typename> class CT>
  void _MoveMinimizerLineRegularShift(SystemPropagator<T,CT>&) {}

}

#include "system/content/with-egv/interface.h"

namespace mysimulator {

  template <typename T>
  void _MoveMinimizerLineRegularShift(
      SystemPropagator<T,SystemContentWithEGV>& P) {
    assert(P.IsValid());
    T step=*Pointer<T>(P.Param[MinimizerLineRegularPtrStep]);
    for(unsigned int i=0;i<P.GrpContent.Size();++i)
      BlasShift(P.GrpContent[i].X,step,P.GrpContent[i].Velocity);
  }

  template <typename T,template<typename> class CT>
  void MoveMinimizerLineRegularShift(SystemPropagator<T,CT>& P) {
    _MoveMinimizerLineRegularShift(P);
  }

}

#endif

