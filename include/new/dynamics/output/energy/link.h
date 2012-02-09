
#ifndef _Dynamics_Output_Energy_Link_H_
#define _Dynamics_Output_Energy_Link_H_

#include "dynamics/output/energy/interface.h"
#include "dynamics/output/energy/data/link.h"

namespace mysimulator {

  template <typename OST,typename T,typename IDT,typename PT,
            typename GT,template<typename> class VT,
            template<typename,template<typename>class> class SCT>
  void link(DynamicsOutputEnergy<OST,T,IDT,PT,GT,VT,SCT>& O,
             System<T,IDT,PT,GT,VT,SCT>& S) {
    link(O.EnergyData,S);
  }

}

#endif

