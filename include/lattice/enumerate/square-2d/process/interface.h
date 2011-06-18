
#ifndef _Lattice_Enumerate_Square2D_Process_Base_Interface_H_
#define _Lattice_Enumerate_Square2D_Process_Base_Interface_H_

#include "lattice/enumerate/square-2d/run-data/interface.h"

namespace mysimulator {

  template <unsigned int L>
  struct LatticeEnumSquare2DProcessBase {

    virtual void operator()(const LatticeEnumSquare2DRunData<L>&)=0;

  };

}

#endif

