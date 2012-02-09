
#ifndef _Dynamics_Bind_H_
#define _Dynamics_Bind_H_

#include "dynamics/interface.h"

namespace mysimulator {

  template <DynamicsModeName DMN,typename T,typename IDT,typename PT,
            typename GT,typename OCT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void bind(Dynamics<DMN,T,VT,OCT>&,System<T,IDT,PT,GT,VT,SCT>&) {
    Error("No Bind for this Dynamics!");
  }

}

#include "dynamics/micro-canonical/vverlet/bind-specification.h"

#endif

