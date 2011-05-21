
#ifndef _Lattice_Enumerate_Square2D_Check_Basic_Allocate_Specification_H_
#define _Lattice_Enumerate_Square2D_Check_Basic_Allocate_Specification_H_

#include "lattice/enumerate/square-2d/check/interface.h"

namespace mysimulator {

  void allocate(
      LatticeEnumSquare2DCheck<LatticeEnumSquare2DCheckMethodBasic>& C) {
    release(C);
  }

}

#endif

