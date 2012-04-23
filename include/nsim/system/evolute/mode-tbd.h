
#ifndef _System_Evolute_Mode_ToBeDetermined_H_
#define _System_Evolute_Mode_ToBeDetermined_H_

#include "system/interaction/interface.h"
#include "system/propagator/interface.h"

namespace mysimulator {

  template <typename T,typename IDT,typename PT,typename GT,typename BT,
            template<typename> class CT>
  void SystemEvoluteModeTBD(
      CT<T>& C, Array1D<SystemInteraction<T,IDT,PT,GT,BT,CT> >& SI,
      Array1D<SystemPropagator<T,CT> >& SP,
      const Array1D<Array1D<unsigned int> >&) {
    fprintf(stderr,"No Action For To-Be-Determined Case!\n");
  }

}

#endif

