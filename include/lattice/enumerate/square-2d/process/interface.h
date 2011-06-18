
#ifndef _Lattice_Enumerate_Square2D_Process_Base_Interface_H_
#define _Lattice_Enumerate_Square2D_Process_Base_Interface_H_

#include "lattice/enumerate/square-2d/run-data/interface.h"

namespace mysimulator {

  template <typename T>
  struct LatticeEnumSquare2DProcessBase {
    void operator()(const LatticeEnumSquare2DRunData<L>&)=0;
  };

}

#endif

