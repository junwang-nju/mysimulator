
#ifndef _Dynamics_MicroCanonical_VelVerlet_Interface_H_
#define _Dynamics_MicroCanonical_VelVerlet_Interface_H_

#include "dynamics/interface.h"

namespace mysimulator {

  template <typename T,typename GRNGType>
  struct Dynamics<MicroCanonicalVelVerlet,T,GRNGType>
}

#endif

