
#ifndef _System_Evolute_Mode_FixPosition_H_
#define _System_Evolute_Mode_FixPosition_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"

namespace mysimulator  {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeFixPosition(
      CT<T>&,Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >&,
      Array1D<SystemPropagator<T,CT> >&,
      const Array1D<Array1D<unsigned int> >&) {}

}

#endif

